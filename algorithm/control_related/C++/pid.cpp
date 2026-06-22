#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> struct BoundParam {
  T max_integral;
  T min_integral;
  T max_err_rate;
  T max_err;
  T min_err;
  T max_cmd;
  T min_cmd;
};
template <typename T> class PID {
private:
  T _kp, _ki, _kd;
  T _pre_err;
  T _integral;
  T _ts;
  T _max_integral;
  T _min_integral;
  T _max_err_rate;
  T _max_err;
  T _min_err;
  T _max_cmd;
  T _min_cmd;

public:
  PID(T kp, T ki, T kd, T ts)
      : _kp(kp), _ki(ki), _kd(kd), _ts(ts), _pre_err(0.0), _integral(0.0) {}

  void Init(const BoundParam &param) {
    _integral = 0.0;
    _pre_err = 0.0;
    _max_integral = param.max_integral;
    _min_integral = param.min_integral;
    _max_err_rate = param.max_err_rate;
    _max_err = param.max_err;
    _min_err = param.min_err;
    _max_cmd = param.max_cmd;
    _min_cmd = param.min_cmd;
  }

  void Reset(T err) {
    _integral = 0.0;
    _pre_err = err;
  }

  T Clamp(T val, T min_val, T max_val) {
    if (max_val < min_val) {
      swap(max_val, min_val);
    }
    return min(max(val, min_val), max_val);
  }

  T ComputeCommand(double ref, double cur) {
    T err = ref - cur;
    err = Clamp(err, _min_err, _max_err);
    T u_p = _kp * err;
    _integral += err * _ts;
    _integral = Clamp(_integral, _min_integral, _max_integral);
    T u_i = _ki * _integral;
    T err_rate = (err - _pre_err) / _ts;
    err_rate = Clamp(err_rate, -_max_err_rate, _max_err_rate);
    T u_d = _kd * err_rate;
    _pre_err = err;
    T cmd = u_p + u_i + u_d;
    err_rate = Clamp(cmd, _min_cmd, _max_cmd);
    return cmd;
  }
};

int main() {
  int step = 100;
  double ts = 0.05;
  double kp = 1.0;
  double ki = 0.1;
  double kd = 0.05;
  BoundParam<double> param;
  param.max_integral = 1.0;
  param.min_integral = -1.0;
  param.max_err_rate = 0.2;
  param.max_err = 1.0;
  param.min_err = -1.0;
  param.max_cmd = 1.0;
  param.min_cmd = -1.0;
  PID<double> pid_controller(kp, ki, kd, ts);
  pid_controller.Init(param);
  double ref = 1.0;
  double cur = 0.0;

  for (int i = 0; i < step; i++) {
    double output = pid_controller.ComputeCommand(ref, cur);
    cur = cur + output * ts;
    cout << "Control output: " << output << " cur: " << cur;
  }
  return 0;
}

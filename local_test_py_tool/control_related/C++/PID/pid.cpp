#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class PID {
private:
  double _kp, _ki, _kd;
  double _pre_err;
  double _integral;
  double _ts;

public:
  PID(double kp, double ki, double kd, double ts)
      : _kp(kp), _ki(ki), _kd(kd), _ts(ts), _pre_err(0.0), _integral(0.0) {}

  double ComputeCommand(double ref, double cur) {
    double err = ref - cur;
    double u_p = _kp * err;
    _integral += err * _ts;
    double u_i = _ki * _integral;
    double u_d = _kd * (err - _pre_err) / _ts;
    _pre_err = err;
    return u_p + u_i + u_d;
  }
};

int main() {
  int step = 100;
  double ts = 0.05;
  double kp = 1.0;
  double ki = 0.1;
  double kd = 0.05;
  PID pid_controller(kp, ki, kd, ts);

  double ref = 1.0;
  double cur = 0.0;

  for (int i = 0; i < step; i++) {
    double output = pid_controller.ComputeCommand(ref, cur);
    cur = cur + output * ts;
    cout << "Control output: " << output << " cur: " << cur;
  }
  return 0;
}

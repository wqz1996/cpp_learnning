#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class IIR {
private:
  deque<double> _y;
  deque<double> _x;
  vector<double> _numerators;
  vector<double> _denominators;

  IIR(vector<double> &numerator, vector<double> &denominator)
      : _numerators(numerator), _denominators(denominator),
        _x(numerator.size(), 0.0), _y(denominator.size(), 0.0) {}
  double FIR(double x) {
    _x.pop_back();
    _x.push_front(x);
    double sum = 0.0;
    for (int i = 0; i < _numerators.size(); i++) {
      sum += _numerators[i] * _x[i];
    }
    _y.pop_back();
    for (int i = 1; i < _denominators.size(); i++) {
      sum -= _denominators[i] * _y[i - 1];
    }
    if (_denominators.front() > 1e-16) {
      sum /= _denominators.front();
    }
    _y.push_front(sum);
    return sum;
  }

public:
};

int main() {

  double start = 0;
  double total_time = 50.0;                              // 总时间
  double sample_frequency = 20.0;                        // 采样频率 Hz
  int signalLength = int(total_time * sample_frequency); // 信号长度
  double frequency = 0.1;                                // 正弦波频率
  double fix_noise_frequency = 1.0;
  default_random_engine generator;
  normal_distribution<double> distribution(
      0.0, 0.1); // 均值为0，标准差为0.1的正态分布

  // 生成带噪声的正弦信号
  vector<double> inputSignal(signalLength);
  vector<double> noise(signalLength);
  vector<double> time_line(signalLength);
  vector<double> fix_frequency_noise(signalLength);

  for (int i = 0; i < signalLength; ++i) {
    time_line[i] = start + i / sample_frequency;
    fix_frequency_noise[i] = sin(2 * M_PI * fix_noise_frequency * time_line[i]);
    noise[i] = distribution(generator);
    inputSignal[i] = sin(2 * M_PI * frequency * time_line[i]) +
                     fix_frequency_noise[i] + noise[i]; // 生成正弦波并添加噪声
  }

  // order = 7  # 滤波器阶数
  // cutoff_frequency = 0.5  # 截止频率
  // sample_frequency = 20.0  # 采样频率
  vector<double> numerators = {
      1.3134081241807374e-08, 9.193856869265162e-08,  2.7581570607795486e-07,
      4.596928434632581e-07,  4.596928434632581e-07,  2.7581570607795486e-07,
      9.193856869265162e-08,  1.3134081241807374e-08,
  };
  vector<double> denominators = {
      1.0,
      -6.2941925133051475,
      17.011136374292853,
      -25.588413458402606,
      23.134331040512976,
      -12.57015040605862,
      3.8004886147901615,
      -0.49319797066721793,
  };

  IIR iir_filter(numerators, denominators);

  // 将input输入到filter中并返回output
  vector<double> outputSignal;
  for (double &val : inputSignal) {
    double output = iir_filter.Filter(val);
    outputSignal.push_back(output);
  }

  // 保存信号到文件
  ofstream fout("/home/wu/local_test_py_tool/control_related/C++/"
                "iir_filter/debug_file/data.txt",
                ios::app);
  fout << "Time:" << endl;
  for (double &val : time_line) {
    fout << val << " ";
  }
  fout << "\nInput Signal:" << endl;
  for (double &val : inputSignal) {
    fout << val << " ";
  }
  fout << "\nOutput Signal:" << endl;
  for (double &val : outputSignal) {
    fout << val << " ";
  }
  fout << endl;
  fout.close();

  return 0;
}
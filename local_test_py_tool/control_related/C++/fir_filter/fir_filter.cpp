#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class FIRFilter {
private:
  vector<double> _window;
  vector<double> _numerators;
  deque<double> _x;
  int _length;
  double _cutoff;
  double _sample_frequency;

public:
  FIRFilter(int length, double cutoff, double sample_frequency)
      : _length(length), _cutoff(cutoff), _sample_frequency(sample_frequency),
        _x(length, 0.0) {}
  void HammingWindow() {
    _window.resize(_length);
    for (int i = 0; i < _length; i++) {
      _window[i] = 0.54 - 0.46 * cos(2.0 * M_PI * i / (_length - 1.0));
    }
  }
  void LowPassFilterCoeff() {
    double alpha = 0.5 * (_length - 1.0);
    double normalized_cutoff_frequency = _cutoff / _sample_frequency;
    for (int i = 0; i < _length; i++) {
      double m = i - alpha;
      double numerator = 0.0;
      if (m == 0) {
        numerator = 2.0 * normalized_cutoff_frequency;
      } else {
        numerator =
            sin(2 * M_PI * normalized_cutoff_frequency * m) / (M_PI * m);
      }
      numerator *= _window[i];
      _numerators.push_back(numerator);
    }
  }
  double Filter(double x) {
    _x.pop_back();
    _x.push_front(x);
    double sum = 0.0;
    for (int i = 0; i < _length; i++) {
      sum += _numerators[i] * _x[i];
    }
    return sum;
  }
  vector<double> getHammingWindow() { return _window; }
  vector<double> getFilterCoeff() { return _numerators; }
  deque<double> getBuffer() { return _x; }
};
int main() {

  // 生成带噪声的正弦信号
  double total_time = 50.0;                              // 总时间
  double sample_frequency = 20.0;                        // 采样频率 Hz
  int signalLength = int(total_time * sample_frequency); // 信号长度
  double frequency = 1.0;                                // 正弦波频率
  vector<double> inputSignal(signalLength);
  default_random_engine generator;
  normal_distribution<double> distribution(
      0.0, 0.1); // 均值为0，标准差为0.1的正态分布
  vector<double> time_line(signalLength);
  double start = 0;
  for (int i = 0; i < signalLength; i++) {
    time_line[i] = start + i / sample_frequency;
  }

  for (int i = 0; i < signalLength; ++i) {
    double noise = distribution(generator);
    inputSignal[i] =
        sin(2 * M_PI * frequency * time_line[i]); // 生成正弦波并添加噪声
  }

  // 滤波器参数
  int length = 51;
  double cutoff = 2.0;

  // 初始化滤波器

  FIRFilter fir_filter(length, cutoff, sample_frequency);

  // 创建hamming窗
  fir_filter.HammingWindow();

  // 计算滤波器系数并应用滤波器
  fir_filter.LowPassFilterCoeff();

  vector<double> hamming_window = fir_filter.getHammingWindow();

  vector<double> filter_coeff = fir_filter.getFilterCoeff();

  // 将input输入到filter中并返回output
  vector<double> outputSignal;
  for (double &val : inputSignal) {
    double output = fir_filter.Filter(val);
    outputSignal.push_back(output);
  }

  // 保存信号到文件
  ofstream fout("/home/wu/local_test_py_tool/control_related/C++/"
                "fir_filter/debug_file/data.txt",
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

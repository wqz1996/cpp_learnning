#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class FirFilter {
public:
  FirFilter() = default;
  /**
   * @brief This function computes the coefficients of a finite impulse response
   * filter
   * @param length Length of the filter (number of coefficients, i.e. the filter
   * order + 1). `length` must be odd if a passband includes the Nyquist
   * frequency
   * @param cutoff_freq Cutoff frequency of filter, it should be positive and
   * monotonically increasing between 0 and `nyquist_freq`. The values 0 and
   * `nyquist_freq` must not be included in `cutoff_freq`.
   * @param pass_zero If True, the gain at the frequency 0 (i.e., the "DC gain")
   * is 1. If False, the DC gain is 0.
   * @param scale Set to True to scale the coefficients so that the frequency
   * response is exactly unity at a certain frequency (0 or nyquist_freq)
   * @param nyquist_freq This is the Nyquist frequency. The cutoff_freq must be
   * between 0 and `nyquist_freq` Default is 1.
   */
  bool setFirWindow(int length, double cutoff_frequency, bool pass_zero = true,
                    bool scale = true, double nyquist_freq = 1.0);
  double Filter(double x);
  bool isWindowSetDone() const { return _set_window_done; }
  const std::vector<double> &getNumerator() const { return _numerators; }

private:
  void generateHammingWindow();
  bool _set_window_done = false;
  int _length = 0;
  std::vector<double> _numerators;
  std::vector<double> _window;
  std::deque<double> _x;
};

void FirFilter::generateHammingWindow() {
  _window.reserve(_length);
  for (int i = 0; i < (_length + 1) / 2; ++i) {
    _window[i] = 0.54 - 0.46 * std::cos(2 * M_PI * i / (_length - 1.0));
    _window[_length - 1 - i] = _window[i];
  }
}

bool FirFilter::setFirWindow(int length, double cutoff_frequency,
                             bool pass_zero, bool scale, double nyquist_freq) {
  _length = length;
  bool pass_nyquist = !pass_zero;
  if (pass_nyquist && _length % 2 == 0) {
    _set_window_done = false;
    return false;
  }
  if (nyquist_freq == 0) {
    _set_window_done = false;
    return false;
  }
  double cutoff_freq = cutoff_frequency / nyquist_freq;
  if (cutoff_freq >= 1.0 || cutoff_freq <= 0.0) {
    _set_window_done = false;
    return false;
  }

  double left = 0.0;
  double right = cutoff_freq;
  if (pass_nyquist) {
    left = cutoff_freq;
    right = 1.0;
  }

  generateHammingWindow();

  // computes the coefficients of a finite impulse response filter
  double alpha = 0.5 * (_length - 1);
  double sum = 0.0;
  double scale_frequency = 0.0;
  if (left == 0) {
    scale_frequency = 0.0;
  } else if (right == 1) {
    scale_frequency = 1.0;
  } else {
    scale_frequency = 0.5 * (left + right);
  }
  for (int i = 0; i < _length; ++i) {
    _x.push_front(0.0);
    double m = i - alpha;
    double numerator = 0;
    if (m == 0) {
      numerator += _window[i] * (right - left) / M_PI;
    } else {
      numerator += _window[i] * (std::sin(right * m) / (M_PI * m) -
                                 std::sin(left * m) / (M_PI * m));
    }
    _numerators.push_back(numerator);
    sum += std::cos(M_PI * (i - alpha) * scale_frequency) * numerator;
  }

  // handle scaling if desired.
  if (scale) {
    for (int i = 0; i < _length; ++i) {
      _numerators[i] /= sum;
    }
  }

  _set_window_done = true;
  return true;
}

double FirFilter::Filter(double x) {
  _x.pop_back();
  _x.push_front(x);
  double sum = 0.0;
  for (int i = 0; i < _length; ++i) {
    sum += _numerators[i] * _x[i];
  }
  return sum;
}

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

  // 初始化滤波器
  FirFilter fir_filter;

  // 滤波器参数
  int fir_filter_length = 50;
  double fir_filter_cutoff_freq = 2.0 / sample_frequency;
  double fir_filter_nyquist_freq = 1.0;
  fir_filter.setFirWindow(fir_filter_length, fir_filter_cutoff_freq, true, true,
                          fir_filter_nyquist_freq);

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

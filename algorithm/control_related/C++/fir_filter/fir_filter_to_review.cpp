#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class FIR {
private:
  vector<double> _windows;
  vector<double> _numerators;
  deque<double> _x;
  double _cutoff;
  double _length;

public:
  FIR(double length, double cutoff)
      : _length(length), _cutoff(cutoff), _windows(length, 0.0),
        _numerators(length, 0.0) {}
  void HammingWindows() {
    for (int i = 0; i < _length; i++) {
      _windows[i] = 0.54 - 0.46 * cos(2.0 * i * M_PI / (_length - 1.0));
    }
  }

  void LowpassCoef() {
    double alpha = 0.5 * (_length - 1.0);
    for (int i = 0; i < _length; i++) {
      double m = i - alpha;
      double numerator = 0.0;
      if (m == 0) {
        numerator = 2.0 * _cutoff;
      } else {
        numerator = sin(2.0 * M_PI * _cutoff * m) / (M_PI * m);
      }
      numerator *= _windows[i];
      _numerators[i] = numerator;
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
};

// int main() {
//   // 滤波器参数
//   int length = 11;
//   double cutoff = 0.25;

//   // 生成带噪声的正弦信号

//   double total_time = 50.0;                         // 总时间
//   double sample_rate = 20.0;                        // 采样频率 Hz
//   int signalLength = int(total_time * sample_rate); // 信号长度
//   double frequency = 1.0;                           // 正弦波频率
//   std::vector<double> inputSignal(signalLength);
//   std::default_random_engine generator;
//   std::normal_distribution<double> distribution(
//       0.0, 0.1); // 均值为0，标准差为0.01的正态分布
//   vector<double> time_line(signalLength);
//   double start = 0;
//   for (int i = 0; i < signalLength; i++) {
//     time_line[i] = start + i / sample_rate;
//   }

//   for (int i = 0; i < signalLength; ++i) {
//     double noise = distribution(generator);
//     inputSignal[i] = sin(2 * M_PI * frequency * time_line[i]) +
//                      noise; // 生成正弦波并添加噪声
//   }

//   // 计算滤波器系数并应用滤波器
//   std::vector<double> filterCoeff = lowPassFilterCoeff(length, cutoff);
//   std::vector<double> outputSignal = applyFIRFilter(inputSignal,
//   filterCoeff);

//   // 保存信号到文件
//   std::ofstream fout("/home/wu/local_test_py_tool/control_related/C++/"
//                      "fir_filter/debug_file/data.txt",
//                      std::ios::app);
//   fout << "Time:" << std::endl;
//   for (double &val : time_line) {
//     fout << val << " ";
//   }
//   fout << "\nInput Signal:" << std::endl;
//   for (double &val : inputSignal) {
//     fout << val << " ";
//   }
//   fout << "\nOutput Signal:" << std::endl;
//   for (double &val : outputSignal) {
//     fout << val << " ";
//   }
//   fout << std::endl;
//   fout.close();

//   return 0;
// }

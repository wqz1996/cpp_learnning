#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// 计算汉明窗系数
std::vector<double> hammingWindow(int length) {
  std::vector<double> window(length);
  for (int i = 0; i < length; ++i) {
    window[i] = 0.54 - 0.46 * cos(2 * M_PI * i / (length - 1));
  }
  return window;
}

// 计算低通滤波器系数
std::vector<double> lowPassFilterCoeff(int length, double cutoff) {
  std::vector<double> h(length);
  std::vector<double> w = hammingWindow(length);
  int M2 = (length - 1) / 2;

  for (int i = 0; i < length; ++i) {
    if (i == M2) {
      h[i] = 2 * cutoff;
    } else {
      h[i] = sin(2 * M_PI * cutoff * (i - M2)) / (M_PI * (i - M2));
    }
    h[i] *= w[i];
  }
  return h;
}

// 应用FIR滤波器
std::vector<double> applyFIRFilter(const std::vector<double> &input,
                                   const std::vector<double> &filterCoeff) {
  int length = filterCoeff.size();
  int N = input.size();
  std::vector<double> output(N, 0.0);

  for (int n = 0; n < N; ++n) {
    for (int k = 0; k < length; ++k) {
      if (n - k >= 0) {
        output[n] += filterCoeff[k] * input[n - k];
      }
    }
  }
  return output;
}

int main() {
  // 滤波器参数
  int length = 11;
  double cutoff = 0.25;

  // 生成带噪声的正弦信号

  double total_time = 50.0;                         // 总时间
  double sample_rate = 20.0;                        // 采样频率 Hz
  int signalLength = int(total_time * sample_rate); // 信号长度
  double frequency = 1.0;                           // 正弦波频率
  std::vector<double> inputSignal(signalLength);
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(
      0.0, 0.1); // 均值为0，标准差为0.01的正态分布
  vector<double> time_line(signalLength);
  double start = 0;
  for (int i = 0; i < signalLength; i++) {
    time_line[i] = start + i / sample_rate;
  }

  for (int i = 0; i < signalLength; ++i) {
    double noise = distribution(generator);
    inputSignal[i] = sin(2 * M_PI * frequency * time_line[i]) +
                     noise; // 生成正弦波并添加噪声
  }

  // 计算滤波器系数并应用滤波器
  std::vector<double> filterCoeff = lowPassFilterCoeff(length, cutoff);
  std::vector<double> outputSignal = applyFIRFilter(inputSignal, filterCoeff);

  // 保存信号到文件
  std::ofstream fout("/home/wu/local_test_py_tool/control_related/C++/"
                     "fir_filter/debug_file/data.txt",
                     std::ios::app);
  fout << "Time:" << std::endl;
  for (double &val : time_line) {
    fout << val << " ";
  }
  fout << "\nInput Signal:" << std::endl;
  for (double &val : inputSignal) {
    fout << val << " ";
  }
  fout << "\nOutput Signal:" << std::endl;
  for (double &val : outputSignal) {
    fout << val << " ";
  }
  fout << std::endl;
  fout.close();

  return 0;
}

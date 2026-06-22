#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// 函数：计算周期
double findPeriod(const std::vector<double> &signal) {
  // 寻找信号的峰值位置
  std::vector<int> peaksIndexs;
  double maxVal = signal[0];
  for (int i = 1; i < signal.size(); ++i) {
    if (signal[i] > maxVal) {
      maxVal = signal[i];
      peaksIndexs.clear();
      peaksIndexs.push_back(i);
    } else if (signal[i] == maxVal) {
      peaksIndexs.push_back(i);
    }
  }

  // 计算峰值之间的距离，返回平均周期
  double sumPeriod = 0;
  for (int i = 1; i < peaksIndexs.size(); ++i) {
    sumPeriod += peaksIndexs[i] - peaksIndexs[i - 1];
  }
  return sumPeriod / (peaksIndexs.size() - 1);
}

// 函数：计算周期差
double calculatePeriodDifference(const std::vector<double> &signal1,
                                 const std::vector<double> &signal2) {
  // 找到每个信号的周期
  double period1 = findPeriod(signal1);
  double period2 = findPeriod(signal2);
  cout << "period1: " << period1 << endl;
  cout << "period2: " << period2 << endl;

  // 计算周期差
  return std::abs(period1 - period2);
}

int main() {
  // 示例数据
  std::vector<double> signal1 = {1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0};
  std::vector<double> signal2 = {0.0, 1.0, 2.0, 1.0, 0.0, 1.0, 2.0, 1.0};

  // 计算周期差
  double periodDifference = calculatePeriodDifference(signal1, signal2);
  std::cout << "diff: " << periodDifference << std::endl;

  return 0;
}

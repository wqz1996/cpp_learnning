#include <iostream>
#include <numeric> // 用于std::accumulate
#include <vector>

std::vector<double> meanFilter(const std::vector<double> &input,
                               int windowSize) {
  int n = input.size();
  std::vector<double> output;

  // 检查窗口大小是否有效
  if (windowSize <= 0 || windowSize > n) {
    std::cerr << "Invalid window size." << std::endl;
    return output;
  }

  for (int i = 0; i <= n - windowSize; ++i) {
    double sum =
        std::accumulate(input.begin() + i, input.begin() + i + windowSize, 0.0);
    output.push_back(sum / windowSize);
  }

  return output;
}

int main() {
  std::vector<double> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int windowSize = 3; // 设置窗口大小为3

  std::vector<double> filteredData = meanFilter(data, windowSize);

  std::cout << "Filtered Data: ";
  for (double d : filteredData) {
    std::cout << d << " ";
  }
  std::cout << std::endl;

  return 0;
}

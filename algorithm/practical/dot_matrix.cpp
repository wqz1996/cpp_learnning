#include <iostream>
#include <vector>

std::vector<std::vector<int>>
matrixMultiply(const std::vector<std::vector<int>> &A,
               const std::vector<std::vector<int>> &B) {
  int m = A.size();    // A的行数
  int n = A[0].size(); // A的列数
  int p = B[0].size(); // B的列数

  // 初始化结果矩阵C
  std::vector<std::vector<int>> C(m, std::vector<int>(p, 0));

  // 执行矩阵乘法
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < p; ++j) {
      for (int k = 0; k < n; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return C;
}

int main() {
  // 示例矩阵A和B
  std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};
  std::vector<std::vector<int>> B = {{2, 0}, {1, 2}};

  // 计算矩阵乘法
  std::vector<std::vector<int>> C = matrixMultiply(A, B);

  // 输出结果矩阵C
  for (const auto &row : C) {
    for (int val : row) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}

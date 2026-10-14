// 原理总结：矩阵乘法中 C[i][j] 是 A 第 i 行与 B 第 j 列的点积。
// 用三层循环枚举结果行、结果列和求和下标 k，计算 C[i][j] += A[i][k] * B[k][j]。
// 假设矩阵非空、每行长度一致，且 A 的列数等于 B 的行数。
#include <iostream>
#include <vector>

std::vector<std::vector<int>>
matrixMultiply(const std::vector<std::vector<int>> &A,
               const std::vector<std::vector<int>> &B) {
  int m = A.size();    // 结果矩阵的行数。
  int n = A[0].size(); // 求和项的个数，也是 B 的行数。
  int p = B[0].size(); // 结果矩阵的列数。

  // 累加前将结果矩阵初始化为 0。
  std::vector<std::vector<int>> C(m, std::vector<int>(p, 0));

  // 固定结果元素 (i, j)，沿公共维度 k 累加乘积。
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

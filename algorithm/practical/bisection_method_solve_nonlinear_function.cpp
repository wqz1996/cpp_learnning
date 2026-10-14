// 原理总结：二分法求解 f(x) = ln(x) + x^3 = 0。
// 在 f(a) 与 f(b) 异号的区间中取中点；根所在的一半仍保持端点异号。
// 重复缩小区间，直到区间宽度小于容差。这里要求 0 < a < b，且两端函数值异号。
#include <cmath>
#include <iostream>

// x 必须大于 0，才能计算自然对数。
double func(double x) { return log(x) + pow(x, 3); }

double bisection(double a, double b, double tol) {
  double c = a;
  while ((b - a) >= tol) {
    // 中点将当前搜索区间分成两半。
    c = (a + b) / 2;
    if (func(c) == 0.0)
      break;
    else if (func(c) * func(a) < 0)
      // 左半区间端点异号，根在 [a, c]。
      b = c;
    else
      // 否则保留右半区间 [c, b]。
      a = c;
  }
  return c;
}

int main() {
  double a = 0.0001, b = 1, tol = 0.00001;
  double root = bisection(a, b, tol);
  std::cout
      << "The root of ln(x) + x^3 = 0 in the interval [0.0001,1] is approximately: "
      << root << std::endl;
  return 0;
}

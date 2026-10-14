// 原理总结：把求 x 的平方根转为求 f(y) = y² - x 的零点。
// 当 f(a) 与 f(b) 异号时，逐次取区间中点并保留包含零点的一半。
// 区间足够窄或达到最大迭代次数时停止；这里令目标数 x 等于初始右端点 b。
#include <iostream>

// y 是平方根的候选值，x 是被开方数。
double func(double x, double y) { return y * y - x; }

double bisection(double a, double b, double tol, int max_iter) {
  double init = b; // 示例中用初始右端点作为被开方数。
  double c = a;
  int step = 0;
  while ((b - a) >= tol && step++ < max_iter) {
    // 按函数符号保留有根的半个区间。
    c = (a + b) / 2;
    if (func(init, c) == 0.0)
      break;
    else if (func(init, c) * func(init, a) < 0)
      b = c;
    else
      a = c;
  }
  return c;
}

int main() {
  double a = 0.0001, b = 4, tol = 0.00001;
  int max_iter = 500;
  double root = bisection(a, b, tol, max_iter);
  std::cout << "The square root of " << b << " is approximately: " << root
            << std::endl;
  return 0;
}

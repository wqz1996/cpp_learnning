// 原理总结：牛顿法用当前位置的切线近似曲线，按 x_next = x - f(x)/f'(x) 更新。
// 本例求 x³ - x - 2 = 0；迭代步长足够小时返回近似根。
// 初值会影响收敛，导数为零时不能直接使用这个更新式。
#include <cmath>
#include <iostream>
// 待求根的函数及其导数。
double f(double x) {
  // 例如，求解方程 x^3 - x - 2 = 0
  return x * x * x - x - 2;
}

// 定义函数 f(x) 的导数 f'(x)
double df(double x) {
  // 导数为 3*x^2 - 1
  return 3 * x * x - 1;
}

// 从 initialGuess 开始迭代；此简化示例未设置迭代次数上限。
double newtonMethod(double initialGuess, double tol) {
  double x = initialGuess;
  double h = f(x) / df(x);

  while (std::abs(h) >= tol) {
    // h 是本次切线给出的修正量。
    h = f(x) / df(x);
    x = x - h;
  }

  return x;
}

int main() {
  double initialGuess = 1.5; // 初始猜测值
  double tol = 0.0001;       // 容差

  double root = newtonMethod(initialGuess, tol);
  std::cout << "The root is: " << root << std::endl;

  return 0;
}

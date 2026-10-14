#include <cmath>
#include <iostream>
// newtonMethod
// x(n+1) = x(n) - f(x)/ f'(x)
// 定义函数 f(x)
//请注意，牛顿法的收敛性依赖于初始猜测值和方程的性质，对于某些方程或不合适的初始猜测值，牛顿法可能不会收敛。
//在实际应用中，可能需要结合其他数值方法来确保找到方程的根。
double f(double x) {
  // 例如，求解方程 x^3 - x - 2 = 0
  return x * x * x - x - 2;
}

// 定义函数 f(x) 的导数 f'(x)
double df(double x) {
  // 导数为 3*x^2 - 1
  return 3 * x * x - 1;
}

// 牛顿法
double newtonMethod(double initialGuess, double tol) {
  double x = initialGuess;
  double h = f(x) / df(x);

  while (std::abs(h) >= tol) {
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

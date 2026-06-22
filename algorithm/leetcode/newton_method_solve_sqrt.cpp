#include <cmath>
#include <iostream>
using namespace std;
double f(double y, double x) { return y * y - x; }
double df(double y) { return 2.0 * y; }

double sqrt_newton1(double x, double tol, int max_iter) {
  double y = x;
  double h = f(y, x) / df(y);
  int step = 0;
  while (abs(h) >= tol && step++ < max_iter) {
    h = f(y, x) / df(y);
    y = y - h;
  }
  return y;
}
double sqrt_newton(double x, double tolerance, int max_iter) {
  // 初始猜测值为 x
  double guess = x;

  // 迭代计算平方根
  for (int i = 0; i < max_iter; ++i) {
    double new_guess = 0.5 * (guess + x / guess);
    if (std::abs(new_guess - guess) < tolerance) {
      // 如果当前猜测值与上一次猜测值之间的差小于阈值，则认为已经收敛
      return new_guess;
    }
    guess = new_guess;
  }

  // 如果迭代达到最大次数仍未收敛，则返回当前猜测值
  return guess;
}

int main() {
  double x = 16.0;
  double y = sqrt_newton(x);
  std::cout << "Square root of " << x << " is: " << y << std::endl;
  return 0;
}

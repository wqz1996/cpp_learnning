// 原理总结：对 f(y) = y² - x 使用牛顿法，更新式为 y_next = (y + x/y)/2。
// 两种实现都反复更新近似值，直到变化量小于容差或达到迭代次数上限。
// 本例假设 x > 0，避免初始值和迭代分母为零。
#include <cmath>
#include <iostream>
using namespace std;
// f(y) 的零点就是 x 的平方根；df 是 f 对 y 的导数。
double f(double y, double x) { return y * y - x; }
double df(double y) { return 2.0 * y; }

double sqrt_newton1(double x, double tol, int max_iter) {
  double y = x;
  double h = f(y, x) / df(y);
  int step = 0;
  while (abs(h) >= tol && step++ < max_iter) {
    // 用 f(y)/f'(y) 修正当前估计值。
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
    double new_guess = 0.5 * (guess + x / guess); // 化简后的牛顿更新式。
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
  double y = sqrt_newton(x, 0.00001, 500);
  std::cout << "Square root of " << x << " is: " << y << std::endl;
  return 0;
}

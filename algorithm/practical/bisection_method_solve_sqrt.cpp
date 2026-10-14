#include <cmath>
#include <iostream>

double func(double x, double y) { return y * y - x; }

double bisection(double a, double b, double tol, int max_iter) {
  double init = b;
  double c = a;
  int step = 0;
  while ((b - a) >= tol && step++ > max_iter) {
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
  std::cout
      << "The root of ln(x) + x^3 = 0 in the interval [0,1] is approximately: "
      << root << std::endl;
  return 0;
}

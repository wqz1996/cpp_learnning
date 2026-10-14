#include <cmath>
#include <iostream>

double func(double x) { return log(x) + pow(x, 3); }

double bisection(double a, double b, double tol) {
  double c = a;
  while ((b - a) >= tol) {
    c = (a + b) / 2;
    if (func(c) == 0.0)
      break;
    else if (func(c) * func(a) < 0)
      b = c;
    else
      a = c;
  }
  return c;
}

int main() {
  double a = 0.0001, b = 1, tol = 0.00001;
  double root = bisection(a, b, tol);
  std::cout
      << "The root of ln(x) + x^3 = 0 in the interval [0,1] is approximately: "
      << root << std::endl;
  return 0;
}

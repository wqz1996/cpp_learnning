#include <cmath>
#include <iostream>
using namespace std;
double func(double x) { return log(x) + pow(x, 3); }

double bisection(double a, double b, double tol) {
  double c = a;
  while (fabs(b - a) >= tol) {
    c = a + (b - a) / 2.0;
    if (func(c) == 0.0) {
      break;
    } else if (func(c) * func(a) < 0) {
      b = c;
    } else {
      a = c;
    }
  }
  return c;
}

int main() {
  double a = 0.0001, b = 1.0, tol = 0.00001;
  double ans = bisection(a, b, tol);
  cout << ans;
  return 0;
}

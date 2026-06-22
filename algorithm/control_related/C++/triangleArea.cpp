#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
//计算三角形面积
//海伦公式
//给定三点A(x1,y1) B(x2,y2) C(x3,y3)
// S = 0.5 * |x1(y2-y3) +x2(y3-y1) + x3(y1-y2)|
struct Point {
  double x, y;
};

double triangleArea(const Point &a, const Point &b, const Point &c) {
  return 0.5 * abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

int main() {
  Point A, B, C;
  A = {0.0, 0.0};
  B = {4.0, 0.0};
  C = {0.0, 3.0};
  double area = triangleArea(A, B, C);
  if (area > 0)
    cout << "Triangle's Area: " << area << endl;
  else
    cout << "the given points do not form a valid triangle" << endl;
  return 0;
}

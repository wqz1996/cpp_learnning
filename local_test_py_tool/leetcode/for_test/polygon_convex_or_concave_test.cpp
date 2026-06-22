#include <iostream>
#include <vector>
using namespace std;
struct Point {
  double x, y;
};

//计算向量AB和BC的叉积
double crossProduct(const Point &a, const Point &b, const Point &c) {
  double abX = b.x - a.x;
  double abY = b.y - a.y;
  double bcX = c.x - b.x;
  double bcY = c.y - b.y;

  return abX * bcY - abY * bcX;
}

bool isConvexPolygon(const vector<Point> &poly) {
  int n = poly.size();
  if (n < 3)
    return false;
  bool sign = false;
  for (int i = 0; i < n; i++) {
    double cross = crossProduct(poly[i], poly[(i + 1) % n], poly[(i + 2) % n]);
    if (i == 0) {
      sign = cross > 0;
    } else {
      if ((cross > 0) != sign)
        return false;
    }
  }
  return true;
}
int main() {
  std::vector<Point> points = {{0, 0}, {1, 1}, {1, 0}, {0, 1}};
  bool convex = isConvexPolygon(points);
  std::cout << "The polygon is " << (convex ? "convex" : "concave") << "."
            << std::endl;
  return 0;
}

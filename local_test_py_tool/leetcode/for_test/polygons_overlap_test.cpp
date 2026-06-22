#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
struct Point {
  double x;
  double y;
};

Point operator-(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y};
}

//求投影
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

void projectPoly(const Point &axis, const vector<Point> &poly, double &max,
                 double &min) {
  int n = poly.size();
  max = min = dot(axis, poly[0]);
  for (int i = 0; i < n; i++) {
    double projection = dot(axis, poly[i]);
    max = std::max(max, projection);
    min = std::min(min, projection);
  }
}

bool overlap(double minA, double minB, double maxA, double maxB) {
  return std::max(minA, minB) <= std::min(maxA, maxB);
}

bool isoverlapPoly(const vector<Point> &poly1, const vector<Point> &poly2) {
  for (int i = 0; i < poly1.size(); i++) {
    Point edge = poly1[i] - poly1[(i + 1) % poly1.size()];
    Point axis = {-edge.y, edge.x};
    double maxA, maxB, minA, minB;
    projectPoly(axis, poly1, maxA, minA);
    projectPoly(axis, poly2, maxB, minB);
    if (!overlap(minA, minB, maxA, maxB)) {
      return false;
    }
  }

  for (int i = 0; i < poly2.size(); i++) {
    Point edge = poly2[i] - poly2[(i + 1) % poly2.size()];
    Point axis = {-edge.y, edge.x};
    double maxA, maxB, minA, minB;
    projectPoly(axis, poly1, maxA, minA);
    projectPoly(axis, poly2, maxB, minB);
    if (!overlap(minA, minB, maxA, maxB)) {
      return false;
    }
  }
  return true;
}

int main() {

  // 示例多边形
  std::vector<Point> poly1 = {{0, 0}, {2, 0}, {1, 1}};
  std::vector<Point> poly2 = {{1, 0}, {3, 0}, {2, 1}};

  if (isoverlapPoly(poly1, poly2)) {
    std::cout << "Polygons overlap." << std::endl;
  } else {
    std::cout << "Polygons do not overlap." << std::endl;
  }

  return 0;
}
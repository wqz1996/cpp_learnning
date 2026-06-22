#include <algorithm>
#include <iostream>
#include <vector>

//分离轴定理

struct Point {
  double x, y;
};

// 计算向量的差
Point operator-(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y};
}

// 计算点在轴上的投影
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

// 计算投影的最小和最大值
void projectPolygon(const Point &axis, const std::vector<Point> &polygon,
                    double &min, double &max) {
  min = max = dot(axis, polygon[0]);
  for (const Point &p : polygon) {
    double projection = dot(axis, p);
    min = std::min(min, projection);
    max = std::max(max, projection);
  }
}

// 检查两个投影是否重叠
bool overlap(double minA, double maxA, double minB, double maxB) {
  return std::max(minA, minB) <= std::min(maxA, maxB);
}

// 检查多边形是否重叠
bool polygonsOverlap(const std::vector<Point> &poly1,
                     const std::vector<Point> &poly2) {
  for (int i = 0; i < poly1.size(); ++i) {
    Point edge = poly1[i] - poly1[(i + 1) % poly1.size()];
    Point axis = {-edge.y, edge.x}; // 边的法线

    double minA, maxA, minB, maxB;
    projectPolygon(axis, poly1, minA, maxA);
    projectPolygon(axis, poly2, minB, maxB);

    if (!overlap(minA, maxA, minB, maxB))
      return false;
  }

  for (int i = 0; i < poly2.size(); ++i) {
    Point edge = poly2[i] - poly2[(i + 1) % poly2.size()];
    Point axis = {-edge.y, edge.x}; // 边的法线

    double minA, maxA, minB, maxB;
    projectPolygon(axis, poly1, minA, maxA);
    projectPolygon(axis, poly2, minB, maxB);

    if (!overlap(minA, maxA, minB, maxB))
      return false;
  }

  return true;
}

int main() {
  // 示例多边形
  std::vector<Point> poly1 = {{0, 0}, {2, 0}, {1, 1}};
  std::vector<Point> poly2 = {{1, 0}, {3, 0}, {2, 1}};

  if (polygonsOverlap(poly1, poly2)) {
    std::cout << "Polygons overlap." << std::endl;
  } else {
    std::cout << "Polygons do not overlap." << std::endl;
  }

  return 0;
}

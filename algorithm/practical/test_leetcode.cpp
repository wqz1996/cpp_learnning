// 原理总结：这是凸多边形相交的分离轴定理示例，与 polygons_overlap.cpp 相同。
// 分别沿两个多边形各边的法线投影；某个投影区间分离就说明不相交。
// 所有候选轴均重叠时判为相交，边界接触也算相交。
#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  double x, y;
};

// 二维叉积；本示例的重叠检测未调用这个辅助函数。
double crossProduct(const Point &a, const Point &b) {
  return a.x * b.y - a.y * b.x;
}

// 两点相减得到边的方向向量。
Point operator-(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y};
}

// 点积给出轴方向的投影标量。
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

// 遍历顶点得到投影区间的两端。
void projectPolygon(const Point &axis, const std::vector<Point> &polygon,
                    double &min, double &max) {
  min = max = dot(axis, polygon[0]);
  for (const Point &p : polygon) {
    double projection = dot(axis, p);
    min = std::min(min, projection);
    max = std::max(max, projection);
  }
}

// 闭区间有交集就算重叠，包括边界接触。
bool overlap(double minA, double maxA, double minB, double maxB) {
  return std::max(minA, minB) <= std::min(maxA, maxB);
}

// 输入需为按边界顺序排列的非空凸多边形。
bool polygonsOverlap(const std::vector<Point> &poly1,
                     const std::vector<Point> &poly2) {
  for (int i = 0; i < poly1.size(); ++i) {
    // 检查第一个多边形每条边的法线。
    Point edge = poly1[i] - poly1[(i + 1) % poly1.size()];
    Point axis = {-edge.y, edge.x}; // 边的法线

    double minA, maxA, minB, maxB;
    projectPolygon(axis, poly1, minA, maxA);
    projectPolygon(axis, poly2, minB, maxB);

    if (!overlap(minA, maxA, minB, maxB))
      return false;
  }

  for (int i = 0; i < poly2.size(); ++i) {
    // 第二个多边形的法线也可能是唯一的分离轴。
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

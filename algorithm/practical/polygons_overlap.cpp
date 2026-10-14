// 原理总结：分离轴定理用于判断两个凸多边形是否相交。
// 以两个多边形每条边的法线为投影轴；只要有一个轴上的投影区间不重叠，
// 两个多边形就不相交。所有轴都重叠时判为相交，边界接触也算相交。
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

// 两点相减得到一条边的方向向量。
Point operator-(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y};
}

// 点积给出点在轴方向上的投影标量，无需将轴单位化。
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

// 遍历全部顶点，得到多边形在指定轴上的投影区间。
void projectPolygon(const Point &axis, const std::vector<Point> &polygon,
                    double &min, double &max) {
  min = max = dot(axis, polygon[0]);
  for (const Point &p : polygon) {
    double projection = dot(axis, p);
    min = std::min(min, projection);
    max = std::max(max, projection);
  }
}

// 两个闭区间有公共部分时视为重叠。
bool overlap(double minA, double maxA, double minB, double maxB) {
  return std::max(minA, minB) <= std::min(maxA, maxB);
}

// 两个多边形都必须是非空凸多边形，并按边界顺序给出顶点。
bool polygonsOverlap(const std::vector<Point> &poly1,
                     const std::vector<Point> &poly2) {
  for (int i = 0; i < poly1.size(); ++i) {
    // 先检查 poly1 各边的法线。
    Point edge = poly1[i] - poly1[(i + 1) % poly1.size()];
    Point axis = {-edge.y, edge.x}; // 边的法线

    double minA, maxA, minB, maxB;
    projectPolygon(axis, poly1, minA, maxA);
    projectPolygon(axis, poly2, minB, maxB);

    if (!overlap(minA, maxA, minB, maxB))
      return false;
  }

  for (int i = 0; i < poly2.size(); ++i) {
    // 再检查 poly2 各边的法线；缺一组可能漏掉分离轴。
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

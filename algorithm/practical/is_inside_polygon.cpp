// 原理总结：从待测点向右发射射线，统计射线穿过多边形边的次数。
// 穿过奇数次表示内部，偶数次表示外部；若点恰在线段上则直接判为内部。
// 本示例用有限远点和通用线段相交判断，射线恰好经过顶点时可能重复计数。
#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  double x, y;
};

// 在已知三点共线时，检查 c 是否位于 a、b 的坐标范围内。
bool onSegment(const Point &a, const Point &b, const Point &c) {
  return c.x <= std::max(a.x, b.x) && c.x >= std::min(a.x, b.x) &&
         c.y <= std::max(a.y, b.y) && c.y >= std::min(a.y, b.y);
}

double crossProduct(const Point &a, const Point &b, const Point &c) {
  // (b-a)×(c-a) 的符号表示 c 位于有向边 ab 的哪一侧。
  double abX = b.x - a.x;
  double abY = b.y - a.y;
  double acX = c.x - a.x;
  double acY = c.y - a.y;
  return abX * acY - abY * acX;
}

// 通过叉积符号判断两线段是否跨过对方；共线时再检查端点是否落在线段上。
bool doIntersect(const Point &a, const Point &b, const Point &c,
                 const Point &d) {
  double d1 = crossProduct(a, b, c);
  double d2 = crossProduct(a, b, d);
  double d3 = crossProduct(c, d, a);
  double d4 = crossProduct(c, d, b);

  if (d1 * d2 < 0 && d3 * d4 < 0)
    return true;
  if (d1 == 0 && onSegment(a, b, c))
    return true;
  if (d2 == 0 && onSegment(a, b, d))
    return true;
  if (d3 == 0 && onSegment(c, d, a))
    return true;
  if (d4 == 0 && onSegment(c, d, b))
    return true;

  return false;
}

// 逐边统计与水平射线的交点，并单独处理点在边上的情况。
bool isInsidePolygon(const std::vector<Point> &polygon, const Point &p) {
  int n = polygon.size();
  if (n < 3)
    return false; // 少于3一顶点不是多边形

  Point extreme = {1e9, p.y}; // 射线右端点；要求它在多边形最右侧之外。

  int count = 0;
  for (int i = 0; i < n; i++) {
    int next = (i + 1) % n;
    if (doIntersect(polygon[i], polygon[next], p, extreme)) {
      if (crossProduct(polygon[i], p, polygon[next]) == 0)
        return onSegment(polygon[i], polygon[next], p);
      count++;
    }
  }

  return count & 1; // 奇数为true，偶数为false
}

int main() {
  std::vector<Point> polygon = {{1, 1}, {5, 1}, {5, 5}, {1, 5}};
  Point p = {3, 3}; // 应该在多边形内部

  if (isInsidePolygon(polygon, p)) {
    std::cout << "Point is inside the polygon." << std::endl;
  } else {
    std::cout << "Point is outside the polygon." << std::endl;
  }

  return 0;
}

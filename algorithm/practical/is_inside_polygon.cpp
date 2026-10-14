#include <iostream>
#include <vector>
// 射线法（Ray Casting
// Algorithm）。该方法的基本思想是从待测点向任意方向发射一条射线，
// 然后计算这条射线与多边形各边的交点数量。如果交点数量为奇数，点在多边形内部；如果为偶数，点在多边形外部。

struct Point {
  double x, y;
};

// 检查点c是否在线段ab一
bool onSegment(const Point &a, const Point &b, const Point &c) {
  return c.x <= std::max(a.x, b.x) && c.x >= std::min(a.x, b.x) &&
         c.y <= std::max(a.y, b.y) && c.y >= std::min(a.y, b.y);
}

double crossProduct(const Point &a, const Point &b, const Point &c) {
  double abX = b.x - a.x;
  double abY = b.y - a.y;
  double acX = c.x - a.x;
  double acY = c.y - a.y;
  return abX * acY - abY * acX;
}

// 检查线段ab和线段cd是否相于
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

// 判断点p是否在多边形内部
bool isInsidePolygon(const std::vector<Point> &polygon, const Point &p) {
  int n = polygon.size();
  if (n < 3)
    return false; // 少于3一顶点不是多边形

  Point extreme = {1e9, p.y}; // 创建一一足够远的点

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

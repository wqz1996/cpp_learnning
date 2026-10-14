// 原理总结：依次计算多边形相邻边的叉积，比较每个顶点的转向。
// 非零叉积若始终同号，边界一直朝同一方向转，可判为凸多边形。
// 若出现正负两种转向则为凹多边形；此方法假设顶点按边界顺序排列且多边形简单。
#include <iostream>
#include <vector>
struct Point {
  double x, y;
};

// 计算两个向量的叉积
double crossProduct(const Point &a, const Point &b, const Point &c) {
  // 向量AB = B - A，向量BC = C - B
  // 叉积 AB x BC
  double abX = b.x - a.x;
  double abY = b.y - a.y;
  double bcX = c.x - b.x;
  double bcY = c.y - b.y;
  return abX * bcY - abY * bcX;
}

bool isConvexPolygon(const std::vector<Point> &points) {
  int n = points.size();
  if (n < 3)
    return false; // 少于3个顶点不是多边形

  int sign = 0; // 记录首次出现的非零转向方向。
  for (int i = 0; i < n; ++i) {
    double cross =
        crossProduct(points[i], points[(i + 1) % n], points[(i + 2) % n]);
    if (cross == 0)
      continue; // 共线的相邻边不改变转向。
    int currentSign = cross > 0 ? 1 : -1;
    if (sign == 0)
      sign = currentSign;
    else if (currentSign != sign)
      return false; // 发现与其他顶点转向不同
  }
  return sign != 0; // 全部共线时不能构成有效多边形。
}

int main() {
  // 顶点按边界顺序排列，(1,1) 形成向内凹陷。
  std::vector<Point> points = {{0, 0}, {2, 0}, {1, 1}, {2, 2}, {0, 2}};
  bool convex = isConvexPolygon(points);
  std::cout << "The polygon is " << (convex ? "convex" : "concave") << "."
            << std::endl;
  return 0;
}

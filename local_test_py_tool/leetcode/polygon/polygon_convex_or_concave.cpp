#include <iostream>
#include <vector>
//可以通过检查多边形每个内角的转向来完成。对于凸多边形，沿着顶点顺序遍历时，
//所有内角的转向都相同（要么都是顺时针，要么都是逆时针）。如果发现至少一个内角的转向与其他不同，多边形就是凹的。

//我们可以通过计算相邻边的叉积来确定每个内角的转向。对于三个连续的顶点
// AA、BB、CC，向量 ABAB 和向量 BCBC 的叉积可以告诉我们顶点 BB
//的转向是顺时针还是逆时针。
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

  bool sign = false;
  for (int i = 0; i < n; ++i) {
    double cross =
        crossProduct(points[i], points[(i + 1) % n], points[(i + 2) % n]);
    if (i == 0)
      sign = cross > 0;
    else if ((cross > 0) != sign)
      return false; // 发现与其他顶点转向不同
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

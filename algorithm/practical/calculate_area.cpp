// 原理总结：两个轴对齐矩形的并集面积 = 各自面积之和 - 重叠面积。
// 重叠宽度取右边界较小值减左边界较大值，高度同理；负值按 0 处理。
// 两个函数分别用点坐标和独立数值传参，均假设左下角在前、右上角在后。
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct Point {
  double x, y;
};
// 每个矩形由左下角和右上角两个点表示。
double calculate_area(vector<Point> &rectangle1, vector<Point> &rectangle2) {
  Point a1 = rectangle1[0];
  Point b1 = rectangle1[1];
  Point a2 = rectangle2[0];
  Point b2 = rectangle2[1];
  double area1 = (a1.x - b1.x) * (a1.y - b1.y),
         area2 = (a2.x - b2.x) * (a2.y - b2.y);
  // 相交区间的右端减左端；不相交时宽或高为 0。
  double overlapWidth = max((min(b1.x, b2.x) - max(a1.x, a2.x)), 0.0);
  double overlapHeight = max(min(b1.y, b2.y) - max(a1.y, a2.y), 0.0);
  double overlaparea = overlapWidth * overlapHeight;
  return area1 + area2 - overlaparea;
}

// 参数 a 和 b 分别表示两个矩形；(x1, y1) 为左下角，(x2, y2) 为右上角。
double calculate_area_1(double ax1, double ay1, double ax2, double ay2,
                        double bx1, double by1, double bx2, double by2) {
  double area1 = (ax1 - ax2) * (ay1 - ay2), area2 = (bx1 - bx2) * (by1 - by2);
  // 与上面的点坐标版本使用相同的容斥计算。
  double overlapWidth = max((min(ax2, bx2) - max(ax1, bx1)), 0.0);
  double overlapHeight = max((min(ay2, by2) - max(ay1, by1)), 0.0);
  double overlapArea = overlapWidth * overlapHeight;
  return area1 + area2 - overlapArea;
}
int main() {
  std::vector<Point> A = {{-3, 0}, {3, 4}};
  std::vector<Point> B = {{0, -1}, {9, 2}};
  double res = calculate_area(A, B);

  double res1 = calculate_area_1(-3.0, 0.0, 3.0, 4.0, 0.0, -1.0, 9.0, 2.0);
  cout << "res: " << res << " res1: " << res1 << endl;
  return 0;
}

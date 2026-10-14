// 原理总结：二元二次多项式 ax² + bxy + cy² + dx + ey + f
// 可写为 zᵀAz + Bᵀz + f，其中 z = [x,y]ᵀ，A = [[a,b/2],[b/2,c]]，B = [d,e]ᵀ。
// 交叉项由对称矩阵的两个非对角元素共同产生，所以各放入 b/2。
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

// 将二元二次多项式转化为二次型
void polynomialToQuadraticForm(double a, double b, double c, double d, double e,
                               double f) {
  // 对称矩阵 A 保存二次项系数。
  Matrix2d A;
  // a,c为二次项系数，b为xy交叉项系数，d,e为一次项系数，f为常数项
  A << a, b / 2, b / 2, c;

  // z 是示例中的自变量取值，B 保存一次项系数。
  Vector2d x, B;
  x << 0, 0; // 这里在 (0,0) 处计算 Q；改变 x 可计算其他位置的值。
  B << d, e; // b向量的值对应于多项式中的线性项

  // 代入当前 x，计算多项式在该点的值。
  double Q = x.transpose() * A * x + B.transpose() * x + f;

  // 打印矩阵A和向量B
  cout << "Matrix A:\n" << A << endl;
  cout << "Vector B:\n" << B << endl;
  cout << "Quadratic Form: Q(x) = x^T*A*x + B^T*x + f = " << Q
       << " (这里Q的值依赖于x的具体值)" << endl;
}

int main() {
  // 示例：将多项式2x^2 + 3xy + 4y^2 + 5x + 6y + 7转化为二次型
  polynomialToQuadraticForm(2, 3, 4, 5, 6, 7);

  return 0;
}

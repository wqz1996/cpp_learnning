#include <Eigen/Dense> // 需要Eigen库
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

// 将二元二次多项式转化为二次型
void polynomialToQuadraticForm(double a, double b, double c, double d, double e,
                               double f) {
  // 定义2x2的对称矩阵A
  Matrix2d A;
  // a,c为二次项系数，b为xy交叉项系数，d,e为一次项系数，f为常数项
  A << a, b / 2, b / 2, c;

  // 定义2x1的向量x和b
  Vector2d x, B;
  x << 0, 0; // 初始化x向量，这里假设x向量的值未知
  B << d, e; // b向量的值对应于多项式中的线性项

  // 计算二次型
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

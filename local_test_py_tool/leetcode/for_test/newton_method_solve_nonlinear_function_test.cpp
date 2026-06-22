#include <cmath>
#include <iostream>
// newtonMethod
// x(n+1) = x(n) - f(x)/ f'(x)
// 瀹氫箟鍑芥暟 f(x)
//璇锋敞鎰忥紝鐗涢】娉曠殑鏀舵暃鎬т緷璧栦簬鍒濆�嬬寽娴嬪€煎拰鏂圭▼鐨勬€ц川锛屽�逛簬鏌愪簺鏂圭▼鎴栦笉鍚堥€傜殑鍒濆�嬬寽娴嬪€硷紝鐗涢】娉曞彲鑳戒笉浼氭敹鏁涖€�
//鍦ㄥ疄闄呭簲鐢ㄤ腑锛屽彲鑳介渶瑕佺粨鍚堝叾浠栨暟鍊兼柟娉曟潵纭�淇濇壘鍒版柟绋嬬殑鏍广€�
double f(double y, double x) {
  // 渚嬪�傦紝姹傝В鏂圭▼ x^3 - x - 2 = 0
  return y * y - x;
}

// 瀹氫箟鍑芥暟 f(x) 鐨勫�兼暟 f'(x)
double df(double y) {
  // 瀵兼暟涓� 3*x^2 - 1
  return 2 * y;
}

// 鐗涢】娉�
double newtonMethod(double initialGuess, double tol, int max_iter) {
  double x = initialGuess;
  double h = f(x, initialGuess) / df(x);
  int step = 0;
  while (std::abs(h) >= tol) {
    step++;
    if (step > max_iter)
      break;
    h = f(x, initialGuess) / df(x);
    x = x - h;
  }

  return x;
}

int main() {
  double initialGuess = 4; // 鍒濆�嬬寽娴嬪€�
  double tol = 0.000001;   // 瀹瑰樊

  double root = newtonMethod(initialGuess, tol);
  std::cout << "The root is: " << root << std::endl;

  return 0;
}

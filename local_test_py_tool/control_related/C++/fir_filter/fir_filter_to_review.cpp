#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class FIR {
private:
  vector<double> _windows, _numerators;
  deque<double> _x;
  double _length, _cutoff;

public:
  FIR(double length, double cutoff)
      : _length(length), _cutoff(cutoff), _windows(length, 0.0),
        _numerators(length, 0.0), _x(length, 0.0) {}

  void HammingWindow() {
    for (int i = 0; i < _length; i++) {
      _windows[i] = 0.54 - 0.46 * cos(2.0 * M_PI * i / (_length - 1.0));
    }
  }

  void LowpassCoeff() {
    double alpha = 0.5 * (_length - 1.0);
    for (int i = 0; i < _length; i++) {
      double m = i - alpha;
      double numerator = 0.0;
      if (m == 0) {
        numerator = 2.0 * _cutoff;
      } else {
        numerator = sin(2.0 * M_PI * _cutoff * m) / (M_PI * m);
      }
      numerator *= _windows[i];
      _numerators[i] = numerator;
    }
  }

  double Filter(double x) {
    _x.pop_back();
    _x.push_front(x);
    double sum = 0.0;
    for (int i = 0; i < _length; i++) {
      sum += _numerators[i] * _x[i];
    }
    return sum;
  }
};

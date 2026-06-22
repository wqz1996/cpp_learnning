#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class IIR {
private:
  vector<double> _numerators, _denominators;
  deque<double> _x, _y;

  IIR(vector<double> &numerators, vector<double> &denominators)
      : _numerators(numerators), _denominators(denominators),
        _x(numerators.size(), 0.0), _y(denominators.size(), 0.0) {}

  double Filter(double x) {
    _x.pop_back();
    _x.push_front(x);
    double sum = 0.0;
    for (int i = 0; i < _numerators.size(); i++) {
      sum += _numerators[i] * _x[i];
    }
    _y.pop_back();
    for (int i = 1; i < _denominators.size(); i++) {
      sum -= _denominators[i] * _y[i - 1];
    }
    if (_denominators.front() > 1e-16) {
      sum /= _denominators.front();
    }
    _y.push_front(sum);
    return sum;
  }

public:
};

int main() { return 0; }
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct GridLocation {
  int x, y;

  bool operator==(const GridLocation &other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const GridLocation &other) const { return !(*this == other); }

  bool operator<(const GridLocation &other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};

namespace std {
template <> struct hash<GridLocation> {
  size_t operator()(const GridLocation &id) const noexcept {
    return hash<int>()(id.x ^ (id.y << 4));
  }
};
} // namespace std

class GridWithWeights {
public:
  int width, height;
  unordered_set<GridLocation> walls;
  unordered_map<GridLocation, double> weights;

  GridWithWeights(int width_, int height_) : width(width_), height(height_) {}

  bool InBounds(const GridLocation &id) const {
    return 0 <= id.x && id.x < width && 0 <= id.y && id.y < height;
  }

  bool Passable(const GridLocation &id) const {
    return walls.find(id) == walls.end();
  }

  double Cost(const GridLocation &from_node,
              const GridLocation &to_node) const {
    auto iter = weights.find(to_node);
    if (iter != weights.end()) {
      return iter->second;
    }
    return 1.0; // Default cost
  }

  vector<GridLocation> Neighbors(const GridLocation &id) const {
    vector<GridLocation> results;

    const int DIRS = 4;
    static const int delta[DIRS][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (int i = 0; i < DIRS; ++i) {
      GridLocation next{id.x + delta[i][0], id.y + delta[i][1]};
      if (InBounds(next) && Passable(next)) {
        results.push_back(next);
      }
    }

    return results;
  }
};

template <typename T, typename Number = double> struct PriorityQueue {
  typedef pair<Number, T> PQElement;
  priority_queue<PQElement, vector<PQElement>, greater<PQElement>> elements;

  inline bool Empty() const { return elements.empty(); }

  inline void Put(T item, Number priority) { elements.emplace(priority, item); }

  T Get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};

inline double Heuristic(const GridLocation &a, const GridLocation &b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

void Dijkstra(const GridWithWeights &grid, const GridLocation &start,
              const GridLocation &goal,
              unordered_map<GridLocation, GridLocation> &came_from,
              unordered_map<GridLocation, double> &cost_so_far) {
  PriorityQueue<GridLocation, double> frontier;
  frontier.Put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0.0;

  while (!frontier.Empty()) {
    GridLocation current = frontier.Get();

    if (current == goal) {
      break;
    }

    for (GridLocation &next : grid.Neighbors(current)) {
      double new_cost = cost_so_far[current] + grid.Cost(current, next);
      if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost;
        frontier.Put(next, priority);
        came_from[next] = current;
      }
    }
  }
}

vector<GridLocation>
ReconstructPath(const GridLocation &start, const GridLocation &goal,
                unordered_map<GridLocation, GridLocation> &came_from) {
  vector<GridLocation> path;
  GridLocation current = goal;
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  reverse(path.begin(), path.end());
  return path;
}

int main() {
  GridWithWeights grid(10, 10);
  grid.walls.insert(
      {GridLocation{1, 7}, GridLocation{2, 7}, GridLocation{3, 7}});
  grid.weights[{4, 4}] = 5.0; // 更高的成本

  GridLocation start{0, 0};
  GridLocation goal{9, 9};
  unordered_map<GridLocation, GridLocation> came_from;
  unordered_map<GridLocation, double> cost_so_far;

  Dijkstra(grid, start, goal, came_from, cost_so_far);

  vector<GridLocation> path = ReconstructPath(start, goal, came_from);

  // 打印路径
  cout << "Path from start to goal:" << endl;
  for (GridLocation loc : path) {
    cout << "(" << loc.x << ", " << loc.y << ") ";
  }
  cout << endl;

  return 0;
}

// A* 在带权网格上按 f(n) = g(n) + h(n) 扩展节点：g 是起点到当前节点
// 的已知最小代价，h 用曼哈顿距离估计到终点的剩余代价。
// 本例只允许四向移动，且每步代价至少为 1，因此 h 不高估实际剩余代价；
// 找到终点后沿前驱节点回溯，即可得到最短路径。
#include <cstddef> // 使用处：第 36 行的 size_t
#include <utility> // 使用处：第 89 行的 pair
#include <functional> // 使用处：第 35 行的 hash<
#include <algorithm> // 使用处：第 150 行的 reverse(
#include <cmath> // 使用处：第 105 行的 abs
#include <iostream> // 使用处：第 183 行的 cout
#include <queue> // 使用处：第 90 行的 priority_queue
#include <unordered_map> // 使用处：第 47 行的 unordered_map
#include <unordered_set> // 使用处：第 46 行的 unordered_set
#include <vector> // 使用处：第 69 行的 vector

using namespace std;

// 网格坐标作为哈希容器的键，也用于同优先级节点的排序。
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
// 为 GridLocation 提供哈希函数，以便存入 unordered_map / unordered_set。
template <> struct hash<GridLocation> {
  size_t operator()(const GridLocation &id) const noexcept {
    return hash<int>()(id.x ^ (id.y << 4));
  }
};
} // namespace std

// 网格保存障碍和进入各格子的代价；只允许在边界内向上下左右移动。
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
    // 边的代价由目标格决定，未单独设置的格子代价为 1。
    auto iter = weights.find(to_node);
    if (iter != weights.end()) {
      return iter->second;
    }
    return 1.0; // Default cost
  }

  vector<GridLocation> Neighbors(const GridLocation &id) const {
    vector<GridLocation> results;

    const int DIRS = 4;
    static vector<vector<int>> delta(DIRS, vector<int>(2, 0));
    delta = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (int i = 0; i < DIRS; ++i) {
      GridLocation next{id.x + delta[i][0], id.y + delta[i][1]};
      if (InBounds(next) && Passable(next)) {
        results.push_back(next);
      }
    }

    return results;
  }
};

// 小顶堆始终先取出估计总代价最低的候选节点。
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

// 四向移动时的曼哈顿距离；适用于本例每步代价不低于 1 的网格。
inline double Heuristic(const GridLocation &a, const GridLocation &b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

void AStarSearch(const GridWithWeights &grid, const GridLocation &start,
                 const GridLocation &goal,
                 unordered_map<GridLocation, GridLocation> &came_from,
                 unordered_map<GridLocation, double> &cost_so_far) {
  PriorityQueue<GridLocation, double> frontier;
  frontier.Put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0.0;

  // 扩展当前估计总代价最低的节点，到达终点即可结束搜索。
  while (!frontier.Empty()) {
    GridLocation current = frontier.Get();

    if (current == goal) {
      break;
    }

    for (GridLocation &next : grid.Neighbors(current)) {
      double new_cost = cost_so_far[current] + grid.Cost(current, next);
      // 发现更便宜的路径时，更新实际代价、搜索优先级和前驱节点。
      if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost + Heuristic(next, goal);
        frontier.Put(next, priority);
        came_from[next] = current;
      }
    }
  }
}

vector<GridLocation>
ReconstructPath(const GridLocation &start, const GridLocation &goal,
                unordered_map<GridLocation, GridLocation> &came_from) {
  // 从终点沿前驱回溯，再反转为起点到终点的顺序；调用前需确认终点可达。
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

vector<vector<char>> buildMap(const vector<GridLocation> &path, int size) {
  // 用 '#' 标记路径经过的网格坐标，其他格子保持为 '.'。
  vector<vector<char>> grid_with_path(10, vector<char>(10, '.'));
  for (const GridLocation &point : path) {
    grid_with_path[point.x][point.y] = '#';
  }
  return grid_with_path;
}
int main() {
  // 设置障碍和高代价格子，搜索并展示示例路径。
  int size = 10;
  GridWithWeights grid(size, size);

  grid.walls.insert(
      {GridLocation{1, 7}, GridLocation{2, 7}, GridLocation{3, 7}});
  grid.weights[{4, 4}] = 5.0; // 更高的成本

  GridLocation start{0, 0};
  GridLocation goal{5, 5};
  unordered_map<GridLocation, GridLocation> came_from;
  unordered_map<GridLocation, double> cost_so_far;

  AStarSearch(grid, start, goal, came_from, cost_so_far);

  vector<GridLocation> path = ReconstructPath(start, goal, came_from);

  vector<vector<char>> grid_with_path = buildMap(path, size);

  // 打印路径
  cout << "Path from start to goal:" << endl;
  for (GridLocation loc : path) {
    cout << "(" << loc.x << ", " << loc.y << ") ";
  }
  cout << endl;

  cout << "Path in grid" << endl;

  for (vector<char> row : grid_with_path) {
    for (char col : row) {
      cout << col << ' ';
    }
    cout << endl;
  }

  return 0;
}

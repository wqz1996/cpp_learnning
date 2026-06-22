# Sample code from https://www.redblobgames.com/pathfinding/a-star/
# Copyright 2014 Red Blob Games <redblobgames@gmail.com>
#
# Feel free to use this code in your own projects, including commercial projects
# License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>

# some of these types are deprecated: https://www.python.org/dev/peps/pep-0585/
from typing import Iterator, Tuple, TypeVar, Optional
import heapq
import collections

T = TypeVar('T')

Location = TypeVar('Location')


class Graph():

    def neighbors(self, id: Location):
        pass


class SimpleGraph:

    def __init__(self):
        self.edges: dict[Location, list[Location]] = {}

    def neighbors(self, id: Location):
        return self.edges[id]


class Queue:

    def __init__(self):
        self.elements = collections.deque()

    def empty(self) -> bool:
        return not self.elements

    def put(self, x: T):
        self.elements.append(x)

    def get(self) -> T:
        return self.elements.popleft()

    def show(self) -> T:
        print(self.elements)


# utility functions for dealing with square grids
def from_id_width(id, width):
    return (id % width, id // width)


def draw_tile(graph, id, style):
    r = " . "
    if 'number' in style and id in style['number']:
        r = " %-2d" % style['number'][id]
    if 'point_to' in style and style['point_to'].get(id, None) is not None:
        (x1, y1) = id
        (x2, y2) = style['point_to'][id]
        if x2 == x1 + 1: r = " > "
        if x2 == x1 - 1: r = " < "
        if y2 == y1 + 1: r = " v "
        if y2 == y1 - 1: r = " ^ "
    if 'path' in style and id in style['path']: r = " @ "
    if 'start' in style and id == style['start']: r = " A "
    if 'goal' in style and id == style['goal']: r = " Z "
    if id in graph.walls: r = "###"
    return r


def draw_grid(graph, **style):
    print("___" * graph.width)
    for y in range(graph.height):
        for x in range(graph.width):
            print("%s" % draw_tile(graph, (x, y), style), end="")
        print()
    print("~~~" * graph.width)


# data from main article
DIAGRAM1_WALLS = [
    from_id_width(id, width=30) for id in [
        21,
        22,
        51,
        52,
        81,
        82,
        93,
        94,
        111,
        112,
        123,
        124,
        133,
        134,
        141,
        142,
        153,
        154,
        163,
        164,
        171,
        172,
        173,
        174,
        175,
        183,
        184,
        193,
        194,
        201,
        202,
        203,
        204,
        205,
        213,
        214,
        223,
        224,
        243,
        244,
        253,
        254,
        273,
        274,
        283,
        284,
        303,
        304,
        313,
        314,
        333,
        334,
        343,
        344,
        373,
        374,
        403,
        404,
        433,
        434,
    ]
]
#print("wall: \n{}".format(DIAGRAM1_WALLS))
GridLocation = Tuple[int, int]


class SquareGrid:

    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height
        self.walls: list[GridLocation] = []

    def in_bounds(self, id: GridLocation) -> bool:
        (x, y) = id
        return 0 <= x < self.width and 0 <= y < self.height

    def passable(self, id: GridLocation) -> bool:
        return id not in self.walls

    def neighbors(self, id: GridLocation) -> Iterator[GridLocation]:
        (x, y) = id
        neighbors = [(x + 1, y), (x - 1, y), (x, y - 1), (x, y + 1)]  # E W N S
        # see "Ugly paths" section for an explanation:
        if (x + y) % 2 == 0: neighbors.reverse()  # S N W E
        results = filter(self.in_bounds, neighbors)
        results = filter(self.passable, results)
        return results


class WeightedGraph(Graph):

    def cost(self, from_id: Location, to_id: Location) -> float:
        pass


class GridWithWeights(SquareGrid):

    def __init__(self, width: int, height: int):
        super().__init__(width, height)
        self.weights: dict[GridLocation, float] = {}

    def cost(self, from_node: GridLocation, to_node: GridLocation) -> float:
        return self.weights.get(to_node, 1)


diagram4 = GridWithWeights(10, 10)
diagram4.walls = [(1, 7), (1, 8), (2, 7), (2, 8), (3, 7), (3, 8)]
diagram4.weights = {
    loc: 5
    for loc in [
        (3, 4),
        (3, 5),
        (4, 1),
        (4, 2),
        (4, 3),
        (4, 4),
        (4, 5),
        (4, 6),
        (4, 7),
        (4, 8),
        (5, 1),
        (5, 2),
        (5, 3),
        (5, 4),
        (5, 5),
        (5, 6),
        (5, 7),
        (5, 8),
        (6, 2),
        (6, 3),
        (6, 4),
        (6, 5),
        (6, 6),
        (6, 7),
        (7, 3),
        (7, 4),
        (7, 5),
    ]
}


class PriorityQueue:

    def __init__(self):
        self.elements: list[tuple[float, T]] = []

    def empty(self) -> bool:
        return not self.elements

    def put(self, priority: float, item: T):
        heapq.heappush(self.elements, (priority, item))

    def get(self) -> T:
        return heapq.heappop(self.elements)[1]

    def show(self) -> T:
        print("PriorityQueue: {}".format(self.elements))


def dijkstra_search(graph: GridWithWeights, start: Location, goal: Location):
    frontier = PriorityQueue()
    frontier.put(0, start)  # (priority,location)
    came_from: dict[Location, Optional[Location]] = {}
    cost_so_far: dict[Location, float] = {}
    came_from[start] = None
    cost_so_far[start] = 0
    visit_num = 1
    step = 0
    while not frontier.empty():
        print("*****************while begin************************")
        print("visit_num: {}".format(visit_num))
        visit_num += 1
        frontier.show()
        print("came_from: \n{}".format(came_from))
        print("cost_so_far: \n{}".format(cost_so_far))

        current: Location = frontier.get()
        print("After Pop the first")
        frontier.show()

        print("Visiting: {}".format(current))

        if current == goal:
            print("reach the goal!")
            break

        for next in graph.neighbors(current):

            new_cost = cost_so_far[current] + graph.cost(current, next)
            step += 1
            print("step: {}".format(step))

            print("visit neighbors: {}".format(next))
            print(
                "new_cost: {} = cost_so_far[current:{}]: {}  + current:{}->next:{} cost: {}"
                .format(new_cost, current, cost_so_far[current], current, next,
                        graph.cost(current, next)))
            next_not_in_came_from = (next not in cost_so_far)
            print("next not in cost_so_far: {}".format(next_not_in_came_from))
            if cost_so_far.get(next) is not None:
                new_cost_less_than_cost_so_far_next = (new_cost <
                                                       cost_so_far[next])
                print("new_cost < cost_so_far[next]: {}".format(
                    new_cost_less_than_cost_so_far_next))

            if next not in cost_so_far or new_cost < cost_so_far[next]:
                cost_so_far[next] = new_cost
                priority = new_cost
                frontier.put(priority, next)
                came_from[next] = current

                frontier.show()
                print("came_from: \n{}".format(came_from))
                print("cost_so_far: \n{}".format(cost_so_far))
        print("*****************while end************************")
    return came_from, cost_so_far


# thanks to @m1sp <Jaiden Mispy> for this simpler version of
# reconstruct_path that doesn't have duplicate entries


def reconstruct_path(came_from, start: Location, goal: Location):

    current: Location = goal
    path: list[Location] = []
    if goal not in came_from:  # no path was found
        return []
    while current != start:
        path.append(current)
        current = came_from[current]
    path.append(start)  # optional
    path.reverse()  # optional
    return path


diagram_nopath = GridWithWeights(10, 10)
diagram_nopath.walls = [(5, row) for row in range(10)]


def heuristic(a: GridLocation, b: GridLocation) -> float:
    (x1, y1) = a
    (x2, y2) = b
    return abs(x1 - x2) + abs(y1 - y2)


def a_star_search(graph: GridWithWeights, start: Location, goal: Location):
    frontier = PriorityQueue()
    frontier.put(0, start)
    came_from: dict[Location, Optional[Location]] = {}
    cost_so_far: dict[Location, float] = {}
    came_from[start] = None
    cost_so_far[start] = 0

    while not frontier.empty():
        current: Location = frontier.get()

        if current == goal:
            break

        for next in graph.neighbors(current):
            new_cost = cost_so_far[current] + graph.cost(current, next)
            if next not in cost_so_far or new_cost < cost_so_far[next]:
                cost_so_far[next] = new_cost
                priority = new_cost + heuristic(next, goal)
                frontier.put(priority, next)
                came_from[next] = current

    return came_from, cost_so_far


def breadth_first_search(graph: Graph, start: Location, goal: Location):
    frontier = Queue()
    frontier.put(start)
    came_from: dict[Location, Optional[Location]] = {}
    came_from[start] = None
    step = 0
    visit_num = 1
    while not frontier.empty():
        print("visit_num {}".format(visit_num))
        visit_num += 1
        frontier.show()
        print("came_from: \n{}".format(came_from))
        current: Location = frontier.get()
        print("Visiting {}".format(current))
        if current == goal:
            print("reach_the_goal!")
            break

        for next in graph.neighbors(current):
            if next not in came_from:
                frontier.put(next)
                came_from[next] = current
            ###########
            step += 1
            print("step {}".format(step))
            frontier.show()
            print("came_from: \n{}".format(came_from))
            ###########

    return came_from


# def breadth_first_search(graph: Graph, start: Location):
#     frontier = Queue()
#     frontier.put(start)
#     came_from: dict[Location, Optional[Location]] = {}
#     came_from[start] = None

#     while not frontier.empty():
#         current: Location = frontier.get()
#         for next in graph.neighbors(current):
#             if next not in came_from:
#                 frontier.put(next)
#                 came_from[next] = current

#     return came_from


class SquareGridNeighborOrder(SquareGrid):

    def neighbors(self, id):
        (x, y) = id
        neighbors = [(x + dx, y + dy) for (dx, dy) in self.NEIGHBOR_ORDER]
        results = filter(self.in_bounds, neighbors)
        results = filter(self.passable, results)
        return list(results)


def test_with_custom_order(neighbor_order):
    if neighbor_order:
        g = SquareGridNeighborOrder(30, 15)
        g.NEIGHBOR_ORDER = neighbor_order
    else:
        g = SquareGrid(30, 15)
    g.walls = DIAGRAM1_WALLS
    start, goal = (8, 7), (27, 2)
    came_from = breadth_first_search(g, start, goal)
    draw_grid(g,
              path=reconstruct_path(came_from, start=start, goal=goal),
              point_to=came_from,
              start=start,
              goal=goal)


class GridWithAdjustedWeights(GridWithWeights):

    def cost(self, from_node, to_node):
        prev_cost = super().cost(from_node, to_node)
        nudge = 0
        (x1, y1) = from_node
        (x2, y2) = to_node
        if (x1 + y1) % 2 == 0 and x2 != x1: nudge = 1
        if (x1 + y1) % 2 == 1 and y2 != y1: nudge = 1
        return prev_cost + 0.001 * nudge


if __name__ == "__main__":
    # example_graph = SimpleGraph()
    # example_graph.edges = {
    #     'A': ['B'],
    #     'B': ['C'],
    #     'C': ['B', 'D', 'F'],
    #     'D': ['C', 'E'],
    #     'E': ['F'],
    #     'F': [],
    # }
    # breadth_first_search(example_graph, 'B', 'E')
    #################breadth_first_search###########
    # g = SquareGrid(30, 15)
    # g.walls = DIAGRAM1_WALLS
    # g = SquareGrid(4, 4)
    # g.walls = []

    # start = (1, 1)
    # goal = (3, 2)
    # came_from = breadth_first_search(g, start=start, goal=goal)
    # draw_grid(g, point_to=came_from, start=start, goal=goal)
    # path = reconstruct_path(came_from, start=start, goal=goal)
    ##################a_star#########################
    # start, goal = (1, 4), (8, 3)
    # came_from, cost_so_far = a_star_search(diagram4, start, goal)
    # draw_grid(diagram4, point_to=came_from, start=start, goal=goal)
    # print()
    # draw_grid(diagram4,
    #           path=reconstruct_path(came_from, start=start, goal=goal))
    #####################dijkstra####################
    g = GridWithWeights(4, 4)
    # g.walls = [(3, 4), (3, 5), (4, 4), (4, 5), (5, 4), (5, 5), (6, 4), (6, 5)]
    # g.weights = {
    #     loc: 5
    #     for loc in [
    #         (3, 4),
    #         (3, 5),
    #         (4, 1),
    #         (4, 2),
    #         (4, 3),
    #         (4, 4),
    #         (4, 5),
    #         (4, 6),
    #         (4, 7),
    #         (4, 8),
    #         (5, 1),
    #         (5, 2),
    #         (5, 3),
    #         (5, 4),
    #         (5, 5),
    #         (5, 6),
    #         (5, 7),
    #         (5, 8),
    #         (6, 2),
    #         (6, 3),
    #         (6, 4),
    #         (6, 5),
    #         (6, 6),
    #         (6, 7),
    #         (7, 3),
    #         (7, 4),
    #         (7, 5),
    #     ]
    # }
    # print("weight: \n{}".format(g.weights))
    start = (1, 1)
    goal = (3, 2)
    came_from, cost_so_far = dijkstra_search(g, start=start, goal=goal)
    print("cost_so_far: \n{}".format(cost_so_far))
    draw_grid(g, number=cost_so_far, start=start, goal=goal)

    print("")

    draw_grid(g,
              start=start,
              goal=goal,
              path=reconstruct_path(came_from, start=start, goal=goal))
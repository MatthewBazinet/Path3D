#include "Pathfinding.h"



std::vector<GridVec> Pathfinding::reconstruct_path(
	GridVec start, GridVec goal,
	std::unordered_map<GridVec, GridVec> came_from
) {
	std::vector<GridVec> path;
	GridVec current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}



bool operator==(GridVec a, GridVec b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator!=(GridVec a, GridVec b)
{
	return !(a == b);
}

bool operator<(GridVec a, GridVec b)
{

	return std::tie(a.x, a.y) < std::tie(b.x, b.y);

}

void SquareGrid::add_rect(int x1, int y1, int x2, int y2)
{
		for (int x = x1; x < x2; ++x) {
			for (int y = y1; y < y2; ++y) {
				walls.insert(GridVec{ x, y });
			}
		}
}

void Pathfinding::a_star_search(GridWithWeights graph, GridVec start, GridVec goal, std::unordered_map<GridVec, GridVec>& came_from, std::unordered_map<GridVec, double>& cost_so_far)
{
	PriorityQueue<GridVec, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		GridVec current = frontier.get();

		if (current == goal) {
			break;
		}

		for (GridVec next : graph.neighbors(current)) {
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}
}

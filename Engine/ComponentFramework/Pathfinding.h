#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>

struct SimpleGraph {
	std::unordered_map<char, std::vector<char> > edges;

	std::vector<char> neighbors(char id) {
		return edges[id];
	}
};


struct GridVec {
	int x, y;
};

namespace std {
	/* implement hash function so we can put GridVec into an unordered_set */
	template <> struct hash<GridVec> {
		typedef GridVec argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const GridVec& id) const noexcept {
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}


struct SquareGrid {
	std::array<GridVec, 4> DIRS = {
		GridVec{1, 0}, GridVec{-1, 0},
		GridVec{0, -1}, GridVec{0, 1}
	};
	int width, height;
	std::unordered_set<GridVec> walls;

	SquareGrid(int width_, int height_)
		: width(width_), height(height_) {}

	bool in_bounds(GridVec id) const {
		return 0 <= id.x && id.x < width
			&& 0 <= id.y && id.y < height;
	}

	bool passable(GridVec id) const {
		return walls.find(id) == walls.end();
	}

	std::vector<GridVec> neighbors(GridVec id) const {
		std::vector<GridVec> results;

		for (GridVec dir : DIRS) {
			GridVec next{ id.x + dir.x, id.y + dir.y };
			if (in_bounds(next) && passable(next)) {
				results.push_back(next);
			}
		}

		if ((id.x + id.y) % 2 == 0) {
			// see "Ugly paths" section for an explanation:
			std::reverse(results.begin(), results.end());
		}

		return results;
	}
	void add_rect(int x1, int y1, int x2, int y2);
};



// Helpers for GridVec

bool operator == (GridVec a, GridVec b);

bool operator != (GridVec a, GridVec b);

bool operator < (GridVec a, GridVec b);



struct GridWithWeights : SquareGrid {
	std::unordered_set<GridVec> forests;
	GridWithWeights(int w, int h) : SquareGrid(w, h) {}
	inline double cost(GridVec from_node, GridVec to_node) const {
		return forests.find(to_node) != forests.end() ? 5 : 1;
	}
};


template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};





struct Pathfinding {
public:
	static void a_star_search(GridWithWeights graph, GridVec start, GridVec goal, std::unordered_map<GridVec, GridVec>& came_from, std::unordered_map<GridVec, double>& cost_so_far);
	static inline double heuristic(GridVec a, GridVec b) {
		return std::abs(a.x - b.x) + std::abs(a.y - b.y);
	}
	static std::vector<GridVec> reconstruct_path(GridVec start, GridVec goal, std::unordered_map<GridVec, GridVec> came_from);
};
#endif



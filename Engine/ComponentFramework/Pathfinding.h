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

//Essentially a Vec2 but with different operator overloads and less functions
struct GridVec {
	int x, y;
};

//Operator Overloads for GridVec

bool operator == (GridVec a, GridVec b);

bool operator != (GridVec a, GridVec b);

bool operator < (GridVec a, GridVec b);

namespace std {
	//implement hash function so we can put GridVec into an unordered_set 
	template <> struct hash<GridVec> {
		typedef GridVec argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const GridVec& id) const noexcept {
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}

//A two dimensional coordinate system that can contain walls that are impassable
struct Grid {
	std::array<GridVec, 4> DIRS = {
		GridVec{1, 0}, GridVec{-1, 0},
		GridVec{0, -1}, GridVec{0, 1}
	};
	int width, height;
	std::unordered_set<GridVec> walls;

	Grid(int width_, int height_)
		: width(width_), height(height_) {}

	bool inBounds(GridVec id) const {
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
			if (inBounds(next) && passable(next)) {
				results.push_back(next);
			}
		}

		return results;
	}
	void addRect(int x1, int y1, int x2, int y2);
};


//A Grid that has sections that are roughTerrain meaning they cost more to navigate
struct GridWithWeights : Grid {
	std::unordered_set<GridVec> roughTerrain;
	GridWithWeights(int w, int h) : Grid(w, h) {}
	inline double cost(GridVec from_node, GridVec to_node) const {
		return roughTerrain.find(to_node) != roughTerrain.end() ? 5 : 1;
	}
};

//A wrapper around std::priority_queue that reverses the order
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
		T bestItem = elements.top().second;
		elements.pop();
		return bestItem;
	}
};




//Contains the aStar algorithm
struct Pathfinding {
public:
	static void aStarSearch(GridWithWeights graph, GridVec start, GridVec goal, std::unordered_map<GridVec, GridVec>& cameFrom, std::unordered_map<GridVec, double>& costSoFar);
	static inline double heuristic(GridVec a, GridVec b) {
		return std::abs(a.x - b.x) + std::abs(a.y - b.y);
	}
	static std::vector<GridVec> makePath(GridVec start, GridVec goal, std::unordered_map<GridVec, GridVec> cameFrom);
};
#endif



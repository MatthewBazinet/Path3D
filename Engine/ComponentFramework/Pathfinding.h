#ifndef PATHFINDING_H
#define PATHFINDING_H
#include <vector>
#include <stack>
#include <iostream>
#define NUMBER_OF_DIRECTIONS 8
#define MAP_WIDTH 100
#define MAP_HEIGHT 100


using namespace std;

struct Node {
	int x;
	int y;
	int parentX;
	int parentY;
	float distanceFromStartCost;
	float heuristicCost;
	float finalCost;
	bool obstacle;
	Node* neigbours[NUMBER_OF_DIRECTIONS];
	Node() {
		distanceFromStartCost = FLT_MAX;
		heuristicCost = FLT_MAX;
		finalCost = FLT_MAX;
		parentX = -1;
		parentY = -1;
		obstacle = false;
	}
	Node(int i, int j) {
		x = i;
		y = j;
		distanceFromStartCost = FLT_MAX;
		heuristicCost = FLT_MAX;
		finalCost = FLT_MAX;
		parentX = -1;
		parentY = -1;
		obstacle = false;
	}
	~Node() {
		for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++) {
			delete neigbours[i];
			neigbours[i] = nullptr;
		}
		delete neigbours;
	}
};


struct NodeMap {
	Node nodes[MAP_WIDTH][MAP_HEIGHT];
	int costs[MAP_WIDTH][MAP_HEIGHT];

	NodeMap() {
		for (int i = 0; i < MAP_WIDTH; i++) {
			for (int j = 0; j < MAP_HEIGHT; j++) {
				nodes[i][j] = Node(i, j);
			}
		}
	};
	~NodeMap() {};
};

static double calculateHeuristic(int x, int y, Node destination) {
	double H = (sqrt((x - destination.x) * (x - destination.x)
		+ (y - destination.y) * (y - destination.y)));
	return H;
}

static bool isDestination(int x, int y, Node destination) {
	if (x == destination.x && y == destination.y) {
		return true;
	}
	return false;
}

static vector<Node> aStar(Node pawn, Node destination) {
	vector<Node> empty;
	if (destination.x < 0 || destination.x >= MAP_WIDTH || destination.y < 0 || destination.y >= MAP_HEIGHT) {
		return empty;
	}
	if (pawn.x == destination.x && pawn.y == destination.y) {
		return empty;
	}
	bool closedList[MAP_WIDTH][MAP_HEIGHT];
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			closedList[i][j] = false;
		}
	}

	NodeMap map = NodeMap();
	int x = pawn.x;
	int y = pawn.y;
	map.nodes[x][y].finalCost = 0.0;
	map.nodes[x][y].distanceFromStartCost = 0.0;
	map.nodes[x][y].heuristicCost = 0.0;
	map.nodes[x][y].parentX = x;
	map.nodes[x][y].parentY = y;

	vector<Node> openList;
	openList.emplace_back(map.nodes[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < (MAP_WIDTH) * (MAP_HEIGHT)) {
		Node node;
		do {
			float temp = FLT_MAX;
			vector<Node>::iterator itNode;
			for (vector<Node>::iterator it = openList.begin();
				it != openList.end(); it = next(it)) {
				Node n = *it;
				if (n.finalCost < temp) {
					temp = n.finalCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!(node.x < 0 || node.x >= MAP_WIDTH || node.y < 0 || node.y >= MAP_HEIGHT));

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		//For each neighbour starting from North-West to South-East
		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (!(x + newX < 0 || x + newX >= MAP_WIDTH || y + newY < 0 || y + newY >= MAP_HEIGHT)) {
					if (isDestination(x + newX, y + newY, destination))
					{
						//Destination found - make path
						map.nodes[x + newX][y + newY].parentX = x;
						map.nodes[x + newX][y + newY].parentY = y;
						destinationFound = true;
						return makePath(map.nodes, destination);
					}
					else if (closedList[x + newX][y + newY] == false)
					{
						gNew = node.distanceFromStartCost + 1.0;
						hNew = calculateHeuristic(x + newX, y + newY, destination);
						fNew = gNew + hNew;
						// Check if this path is better than the one already present
						if (map.nodes[x + newX][y + newY].finalCost == FLT_MAX ||
							map.nodes[x + newX][y + newY].finalCost > fNew)
						{
							// Update the details of this neighbour node
							map.nodes[x + newX][y + newY].finalCost = fNew;
							map.nodes[x + newX][y + newY].distanceFromStartCost = gNew;
							map.nodes[x + newX][y + newY].heuristicCost = hNew;
							map.nodes[x + newX][y + newY].parentX = x;
							map.nodes[x + newX][y + newY].parentY = y;
							openList.emplace_back(map.nodes[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (destinationFound == false) {
		cout << "Destination not found" << endl;
		return empty;
	}
}

static vector<Node> makePath(Node map[MAP_WIDTH][MAP_HEIGHT], Node dest) {
	try {
		cout << "Found a path" << endl;
		int x = dest.x;
		int y = dest.y;
		stack<Node> path;
		vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			&& map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;

		}
		path.push(map[x][y]);

		while (!path.empty()) {
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		return usablePath;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}


#endif
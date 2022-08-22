#include <iostream>
#include <vector>
#include <queue>

const int INF = 1000000000;

int main()
{
	/* graph init */ 

	std::vector <std::vector<std::pair<int, int>>> graph = 
	{
		{ {1, 1}, {5, 2} },
		{ {0, 1}, {2, 1} },
		{ {1, 1}, {3, 1} },
		{ {2, 1}, {4, 1}, {6, 2} },
		{ {3, 1}, {7, 2} },
		{ {0, 2}, {8, 2} },
		{ {3, 2}, {7, 1}, {10, 5} },
		{ {4, 2}, {6, 1}, {11, 2} },
		{ {5, 2}, {12, 2} },
		{ {10, 1}, {14, 1} },
		{ {6, 5}, {9, 1}, {11, 1} },
		{ {7, 2}, {10, 1} },
		{ {8, 2}, {13, 1}, {15, 2} },
		{ {12, 1}, {14, 1}, {16, 1} },
		{ {9, 1}, {13, 1}, {17, 1} },
		{ {12, 2}, {16, 1} },
		{ {13, 1}, {15, 1}, {17, 1} },
		{ {14, 1}, {16, 1}, {18, 1} },
		{ {17, 1}, {19, 1} },
		{ {18, 1} }
	};

	int vertexSum = 20; // vertices amount
	int iterCount = 0;  // iterations counter

	int start = 0;	// initial vertex
	int goal = 19;	// target vertex
	int current;	// the vertex considered at the certain iteration

	std::vector <bool> visited(vertexSum);		// flags indicating whether vertex was visited
	std::vector <int> distance(vertexSum, INF);  // distances from initial vertex to the n-th vertex
	std::vector <int> parents(vertexSum);		// numbers of vertices parent to the n-th vertex

	distance[start] = 0;
	parents[start] = -1;

	std::queue <int> vertexQueue; // vertices to consider

	vertexQueue.push(start);

	while (!vertexQueue.empty())
	{
		current = vertexQueue.front();
		vertexQueue.pop();

		visited[current] = true;

		if (current == goal)
			break;

		for (int i = 0; i < graph[current].size(); ++i)
		{
			int neighbor = graph[current][i].first;

			int nextCost = graph[current][i].second;
			int newCost = distance[current] + nextCost;

			if ( !(visited[neighbor]) && newCost < distance[neighbor])
			{
				distance[neighbor] = newCost;
				vertexQueue.push(neighbor);
				parents[neighbor] = current;
			}
		}
		iterCount++;
	}

	std::vector<int> path;

	for (int current = goal; current != -1; current = parents[current])
		path.push_back(current);

	reverse(path.begin(), path.end());

	std::cout << "Path: ";

	for (size_t i = 0; i < path.size(); ++i)
		std::cout << path[i] << " ";

	std::cout << "\nDistance: " << distance[goal];
	std::cout << "\nIterations: " << iterCount;
}

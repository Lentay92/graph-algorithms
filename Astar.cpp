#include <iostream>
#include <vector>
#include <set>

const int INF = 1000000000;

class Vertex
{
public:
	int x;
	int y;
	int num;

	Vertex()
	{
		x = y = num = -1;
	}

	Vertex(int a, int b, int n)
	{
		x = a;
		y = b;
		num = n;
	}
};

/* Manhattan heuristic */

int heuristic(Vertex& a, Vertex& b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector <int> totalDistance(20, INF); // totalDistance means distance + heuristic distance

bool operator<(const Vertex& A, const Vertex& B)
{
	return totalDistance[A.num] < totalDistance[B.num]; // the less total distance is, the closer vertex to front of vertexQueue
};

int main()
{
	/* vertices init */
	
	Vertex A(0, 0, 0);	Vertex F(1, 0, 5);	Vertex I(2, 0, 8);	Vertex M(3, 0, 12);	Vertex P(4, 0, 15);
	Vertex B(0, 1, 1);	                  	                 	Vertex N(3, 1, 13);	Vertex Q(4, 1, 16);
	Vertex C(0, 2, 2);	                 	Vertex J(2, 2, 9);	Vertex O(3, 2, 14);	Vertex R(4, 2, 17);
	Vertex D(0, 3, 3);	Vertex G(1, 3, 6);	Vertex K(2, 3, 10);						Vertex S(4, 3, 18);
	Vertex E(0, 4, 4);	Vertex H(1, 4, 7);	Vertex L(2, 4, 11);						Vertex T(4, 4, 19);

	/* graph init */
	
	std::vector <std::vector<std::pair<Vertex, int>>> graph =
	{
		{ {B, 1}, {F, 2} },
		{ {A, 1}, {C, 1} },
		{ {B, 1}, {D, 1} },
		{ {C, 1}, {E, 1}, {G, 2} },
		{ {D, 1}, {H, 2} },
		{ {A, 2}, {I, 2} },
		{ {D, 2}, {H, 1}, {K, 5} },
		{ {E, 2}, {G, 1}, {L, 2} },
		{ {F, 2}, {M, 2} },
		{ {K, 1}, {O, 1} },
		{ {G, 5}, {J, 1}, {L, 1} },
		{ {H, 2}, {K, 1} },
		{ {I, 2}, {N, 1}, {P, 2} },
		{ {M, 1}, {O, 1}, {Q, 1} },
		{ {J, 1}, {N, 1}, {R, 1} },
		{ {M, 2}, {Q, 1} },
		{ {N, 1}, {P, 1}, {R, 1} },
		{ {O, 1}, {Q, 1}, {S, 1} },
		{ {R, 1}, {T, 1} },
		{ {S, 1} }
	};

	size_t vertexSum = 20; // vertices amount
	size_t iterCount = 0;  // iterations counter

	Vertex Start = A; // initial vertex
	Vertex Goal = T;  // target vertex
	Vertex Current;   // the vertex considered at the certain iteration

	std::vector <bool> visited(vertexSum); 		// flags indicating whether vertex was visited
	std::vector <int> distance(vertexSum, INF); 	// distances from initial vertex to the n-th vertex
	std::vector <int> parents(vertexSum); 		// numbers of vertices parent to the n-th vertex
	
	distance[Start.num] = 0;
	parents[Start.num] = -1;

	std::multiset <Vertex> vertexQueue = { Start }; // vertices to consider

	while (!vertexQueue.empty())
	{
		Current = *vertexQueue.begin();
		vertexQueue.erase(vertexQueue.begin());

		visited[Current.num] = true;

		if (Current.num == Goal.num)
			break;

		for (int i = 0; i < graph[Current.num].size(); ++i)
		{
			Vertex* Neighbor = &graph[Current.num][i].first;

			int NeighborCost = graph[Current.num][i].second;
			int newCost = distance[Current.num] + NeighborCost;

			if (!(visited[Neighbor->num]) && newCost < distance[Neighbor->num])
			{
				distance[Neighbor->num] = newCost;
				totalDistance[Neighbor->num] = newCost + heuristic(*Neighbor, Goal);
				parents[Neighbor->num] = Current.num;

				vertexQueue.insert(*Neighbor);
			}
		}
		iterCount++;
	}

	std::vector <int> path;

	for (int currentNum = Goal.num; currentNum != -1; currentNum = parents[currentNum])
		path.push_back(currentNum);

	reverse(path.begin(), path.end());

	std::cout << "Path: ";

	for (size_t i = 0; i < path.size(); ++i)
		std::cout << path[i] << " ";

	std::cout << "\nDistance: " << distance[Goal.num];
	std::cout << "\nIterations: " << iterCount;
}

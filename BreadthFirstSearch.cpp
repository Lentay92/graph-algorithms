#include <iostream>
#include <vector>
#include <queue>

int main()
{
    std::vector <std::vector<int>> graph =
    {
        {1, 5}, 
        {0, 2}, 
        {1, 3}, 
        {2, 4, 6}, 
        {3, 7}, 
        {0, 8}, 
        {3, 7, 10}, 
        {4, 6, 11}, 
        {5, 12}, 
        {10, 14}, 
        {6, 9, 11},
        {7, 10}, 
        {8, 13, 15}, 
        {12, 14, 16}, 
        {9, 13, 17},
        {12, 16}, 
        {13, 15, 17}, 
        {14, 16, 18}, 
        {17, 19}, 
        {18}
    };

    int vertexSum = 20; // vertices amount
    int iterCount = 0;  // iterations counter

    int start = 0;  // initial vertex
    int goal = 19;  // target vertex
    int current;    // vertex considered at the certain iteration

    std::vector <bool> visited(vertexSum);  // flags indicating whether vertex was visited
    std::vector <int> distance(vertexSum);  // distances from initial vertex to the n-th vertex
    std::vector <int> parents(vertexSum);   // numbers of vertices parent to the n-th vertex

    visited[start] = true;
    parents[start] = -1;

    std::queue <int> vertexQueue;

    vertexQueue.push(start);

    while (!vertexQueue.empty())
    {
        current = vertexQueue.front();
        vertexQueue.pop();

        if (current == goal)
            break;

        for (size_t i = 0; i < graph[current].size(); ++i)
        {
            int next = graph[current][i];
            if (!visited[next])
            {
                visited[next] = true;
                vertexQueue.push(next);
                distance[next] = distance[current] + 1;
                parents[next] = current;
            }
        }
        iterCount++;
    }

    if (!visited[goal])
        std::cout << "No path!\n";
    else
    {
        std::vector <int> path;
        for (int currVertex = goal; current != -1; current = parents[current])
            path.push_back(current);

        reverse(path.begin(), path.end());

        std::cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i)
            std::cout << path[i] << " ";
        std::cout << "\nDistance: " << distance[goal];
        std::cout << "\nIterations: " << iterCount;
    }
}




#include <iostream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

class Graph
{
    int verticesCount;
    list<int> *edges;
    list<int> *reversedEdges;

    void FirstPassDFS(int node, vector<bool> &visitedNodes, stack<int> &finishOrderStack, bool isSecondPass = false, int *componentSize = nullptr)
    {
        visitedNodes[node] = true;
        if (isSecondPass && componentSize)
            (*componentSize)++;

        list<int> &edgeList = isSecondPass ? reversedEdges[node] : edges[node];
        for (auto adjNode = edgeList.begin(); adjNode != edgeList.end(); ++adjNode)
            if (!visitedNodes[*adjNode])
                FirstPassDFS(*adjNode, visitedNodes, finishOrderStack, isSecondPass, componentSize);

        if (!isSecondPass)
            finishOrderStack.push(node);
    }

public:
    Graph(int totalVertices) : verticesCount(totalVertices)
    {
        edges = new list<int>[verticesCount];
        reversedEdges = new list<int>[verticesCount];
    }

    void InsertEdge(int startVertex, int endVertex)
    {
        edges[startVertex].push_back(endVertex);
        reversedEdges[endVertex].push_back(startVertex);
    }

    int LargestSCC()
    {
        stack<int> nodeFinishOrder;
        vector<bool> visited(verticesCount, false);
        int maxComponentSize = 0;

        for (int i = 0; i < verticesCount; i++)
            if (!visited[i])
                FirstPassDFS(i, visited, nodeFinishOrder);

        fill(visited.begin(), visited.end(), false);

        while (!nodeFinishOrder.empty())
        {
            int currentVertex = nodeFinishOrder.top();
            nodeFinishOrder.pop();

            if (!visited[currentVertex])
            {
                int currentSize = 0;
                FirstPassDFS(currentVertex, visited, nodeFinishOrder, true, &currentSize);
                maxComponentSize = max(maxComponentSize, currentSize);
            }
        }

        return maxComponentSize;
    }
};

int main()
{
    Graph graph(9);
    graph.InsertEdge(0, 1);
    graph.InsertEdge(1, 2);
    graph.InsertEdge(2, 0);
    graph.InsertEdge(1, 3);
    graph.InsertEdge(3, 4);
    graph.InsertEdge(4, 5);
    graph.InsertEdge(5, 2);
    graph.InsertEdge(2, 6);
    graph.InsertEdge(3, 1);

    cout << "Largest SCC" << graph.LargestSCC() << endl;

    return 0;
}

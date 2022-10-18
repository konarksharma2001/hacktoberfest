#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    // T.C. -> O(E * log(N))
    // S.C. -> O(N + E)
    // where N is the number of nodes in the graph
    // E is the number of edges in the graph

    unordered_map<int, list<pair<int, int>>> adj;

    vector<int> dijkstra(int vertices, int source)
    {

        // Creating & Initailizing distance vector with INT_MAX
        vector<int> dist(5);
        for (int i = 0; i < dist.size(); i++)
        {
            dist[i] = INT_MAX;
        }

        // creation of set on basis {distance, node}
        set<pair<int, int>> st;

        // Initializing dist and set with source node
        dist[source] = 0;
        st.insert({0, source});

        while (!st.empty())
        {

            // Fetch top record in the set
            auto top = *(st.begin());

            int nodeDistance = top.first;
            int topNode = top.second;

            // Remove top record from set
            st.erase(st.begin());

            // Traverse all neighbours
            for (auto neighbour : adj[topNode])
            {

                if (nodeDistance + neighbour.second < dist[neighbour.first])
                {
                    auto record = st.find({dist[neighbour.first], neighbour.first});

                    // If record found, then erase it
                    if (record != st.end())
                    {
                        st.erase(record);
                    }

                    // Update shortest distance
                    dist[neighbour.first] = nodeDistance + neighbour.second;

                    // Push record in set { Node distance,topNode }
                    st.insert({dist[neighbour.first], neighbour.first});
                }
            }
        }

        return dist;
    }

    void addEdge(int u, int v, int weight)
    {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
    }

    void printAdj()
    {
        cout << endl;
        for (auto i : adj)
        {
            cout << i.first << " -> ";
            for (auto j : i.second)
            {
                cout << "(" << j.first << "," << j.second << "), ";
            }
            cout << endl;
        }
    }
};

int main()
{

    Graph g;

    int vertices = 5;
    int source = 0;

    g.addEdge(0, 1, 7);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(3, 1, 5);
    g.addEdge(3, 4, 7);
    g.addEdge(1, 4, 1);

    g.printAdj();

    vector<int> ans = g.dijkstra(vertices, source);

    cout << "\nDijkstra Shortest Path is: " << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << " " << ans[i] << " ";
    }
    cout << endl;

    return 0;
}

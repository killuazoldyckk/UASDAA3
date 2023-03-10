#include<stdio.h>
using namespace std;

// Creating shortcut for an integer pair
typedef pair<int, int> iPair;

class Graph
{
	int V; 
	list<int> *adj;
	vector< pair<int, iPair> > edges;
	void DFS(int v, bool visited[]);

public:
	Graph(int V); 

	void addEdge(int u, int v, int w);

	bool isConnected();

	void reverseDeleteMST();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(v);
	adj[v].push_back(u); 
	edges.push_back({w, {u, v}});
}

void Graph::DFS(int v, bool visited[])
{
	visited[v] = true;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS(*i, visited);
}

bool Graph::isConnected()
{
	bool visited[V];
	memset(visited, false, sizeof(visited));

	DFS(0, visited);

	for (int i=1; i<V; i++)
		if (visited[i] == false)
			return false;

	return true;
}

void Graph::reverseDeleteMST()
{
	sort(edges.begin(), edges.end());

	int mst_wt = 0; 

	cout << "Edges in MST\n";

	for (int i=edges.size()-1; i>=0; i--)
	{
		int u = edges[i].second.first;
		int v = edges[i].second.second;

		adj[u].remove(v);
		adj[v].remove(u);

		if (isConnected() == false)
		{
			adj[u].push_back(v);
			adj[v].push_back(u);

			cout << "(" << u << ", " << v << ") \n";
			mst_wt += edges[i].first;
		}
	}

	cout << "Total weight of MST is " << mst_wt;
}

int main()
{
	int V = 7;
	Graph g(V);

	g.addEdge(0, 1, 7);
	g.addEdge(0, 3, 5);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 3, 9);
	g.addEdge(1, 4, 7);
	g.addEdge(2, 4, 5);
	g.addEdge(3, 4, 15);
	g.addEdge(3, 5, 6);
	g.addEdge(4, 5, 8);
	g.addEdge(4, 6, 9);
	g.addEdge(5, 6, 11);

	g.reverseDeleteMST();
	return 0;
}

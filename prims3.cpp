#include <iostream>
using namespace std;

// jumlah vertex pada graf
#define V 7

// Fungsi untuk menemuka vertex dengan
// nilai minimum.
// Belum masuk kedalam MST.
int minKey(int key[], bool mstSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// Sebuah fungsi untuk menampilkan
// hasil MST yang telah dibangun
void printMST(int parent[], int graph[V][V])
{
	cout << "Edge \tBobot\n";
	for (int i = 1; i < V; i++)
		cout << parent[i] << " - " << i << " \t"
			<< graph[i][parent[i]] << " \n";
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V])
{
	// Array untuk menyimpan tiap bagian MST yang telah diperoleh
	int parent[V];

	// Key values digunakan untuk menempukan edges dengan bobot paling rendah
	int key[V];

	// Untuk merepresentasikan MST
	bool mstSet[V];

	// Inisialisasikan nilai key menjadi infinite
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Memilih vertex 0 sebagai start vertex dari MST 
	key[0] = 0;
	parent[0] = -1; 
	// The MST akan memilih V-1 vertex
	for (int count = 0; count < V - 1; count++) {
		int u = minKey(key, mstSet);

		mstSet[u] = true;

		for (int v = 0; v < V; v++)

			if (graph[u][v] && mstSet[v] == false
				&& graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// Menampilkan MST
	printMST(parent, graph);
}

int main()
{
	int graph[V][V] = { { 0, 7, 0, 5, 0, 0, 0 },
						{ 7, 0, 8, 9, 7, 0, 0 },
						{ 0, 8, 0, 0, 5, 0, 0 },
						{ 5, 9, 0, 0, 15, 6, 0 },
						{ 0, 7, 5, 15, 0, 8, 9 },
                        { 0, 0, 0, 6, 8, 0, 11 },
                        { 0, 0, 0, 0, 9, 11, 0 } };

	// Memanggil fungsi
	primMST(graph);

	return 0;
}


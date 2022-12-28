#include<stdio.h>
#include<stdlib.h>

int comparator(const void *p1,const void *p2)
{
	const int (*x)[6]=p1;
	const int (*y)[6]=p2;

	return (*x)[2]-(*y)[2];
}

void makeSet(int parent[],int rank[],int n)
{
	for(int i=0;i<n;i++)
	{
		parent[i]=i;
		rank[i]=0;
	}
}

int findParent(int parent[],int component)
{
	if(parent[component]==component)
	return component;

	return parent[component]=findParent(parent,parent[component]);
}

void unionSet(int u,int v,int parent[],int rank[],int n)
{
	u=findParent(parent,u);
	v=findParent(parent,v);

	if(rank[u]<rank[v])
	{
		parent[u]=v;
	}
	else if(rank[u]<rank[v])
	{
		parent[v]=u;
	}
	else
	{
		parent[v]=u;
		rank[u]++;
	}
}

void kruskalAlgo(int n,int edge[n][6])
{

	qsort(edge,n,sizeof(edge[0]),comparator);
	
	int parent[n];
	int rank[n];
	makeSet(parent,rank,n);

	int minCost=0;

	printf("Following are the edges in the constructed MST\n");
	for(int i=0;i<n;i++)
	{
		int v1=findParent(parent,edge[i][0]);
		int v2=findParent(parent,edge[i][1]);
		int wt=edge[i][2];

		if(v1!=v2)
			unionSet(v1,v2,parent,rank,n);
			minCost+=wt;
			printf("%d -- %d == %d\n",edge[i][0],edge[i][1],wt);
		}
	}

	printf("Minimum Cost Spanning Tree: %d\n",minCost);
}

int main()
{

	int edge[11][6]={{0,1,7},
			{0,3,5},
			{1,2,8},
			{1,3,9},
                    	{1,4,7},
                    	{2,4,5},
                    	{3,4,15},
                    	{3,5,6},
                    	{4,5,8},
                    	{4,6,9},
                    	{5,6,11}};

	kruskalAlgo(11,edge);
}

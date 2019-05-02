// Djiktras.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
using namespace std;
#define MAX 10																			//useless
class graph
{
	int n, e,traffic;
	char ch;
public:			
	int findMinVertex(int* distance, bool* visited, int n)								//substitute function to find minimum vertex. Can be avoided if we use priority queue
	{
		int minVertex = -1;																//initializing minVertex to -1 so that we dont get to the same vertex again and again
		for (int i = 0;i < n;i++)
		{
			if (!visited[i] && (minVertex == -1 || distance[i] < distance[minVertex]))	// check if not visited AND if the minVertex =-1 or distance of i is less than the minVertex value
																						//Look carefully! theres a OR in AND :):):):):):):):)
			{																			
				minVertex = i;															//keep updating value of minVertex until the smallest distance is found out through iteration
			}
		}
		cout << "Rider is at point " << minVertex << endl;
		return minVertex;
	}
	void djiktras(int **edges, int n,int k)													//main djiktras function... passing edge array and no of vertices only
	{
		int* distance = new int[n];														//declaring distance to keep track of current minimum distance
		bool* visited = new bool[n];													//declaring visited boolean to keep track of visited vertices
		for (int i = 0;i < n;i++)
		{
			distance[i] = INT_MAX;														//initializing infinity value initially to complete array
			visited[i] = false;															//initializing all visited array to false
		}
		distance[k] = 0;
		for (int i = 0;i < n - 1;i++)
		{
			int q=0;
			//cout << "Inside first loop" << i << endl;
			int minVertex = findMinVertex(distance, visited, n);						//finding minimum vertex from the array of vertices distance values 
			visited[minVertex] = true;													//mark the minVertex as true as we are now going to operate over this value
			cout << "Do you want to change traffic congestion" << endl;
			cin >> ch;
			while (ch == 'y' || ch == 'Y')
			{
				int f, s, wt;
				cout << "Enter first, second and weights and also the traffic congestion in terms of units" << endl;			//giving input in terms of pair of edges
				cin >> f >> s >>wt>> traffic;
				if (edges[f][s] != 0)
				{
					edges[f][s] = wt * traffic;
					edges[s][f] = wt * traffic;
				}
				else
				{
					cout << "New edge found" << endl;
				}
				cout << "Do you want to continue changing traffic congestion" << endl;
				cin >> ch;
				q++;
			}
			if (q != 0)
			{
				djiktras(edges, n, minVertex);
			}
			for (int j = 0;j < n;j++)
			{
				//cout << "Inside second loop" << j << endl;
				if (edges[minVertex][j] != 0 && !visited[j])							//check if a neighbouring edge exist and is unvisited
				{
					int dist = distance[minVertex] + edges[minVertex][j];				//initialize new distance value which will be sum of current distance value + 
					//cout << distance[j] << endl;																	//new value between neighbouring vertex and current vertex
					if (dist < distance[j])												//if that distance is smaller than the previous value, we must replace it with the new value
					{
						distance[j] = dist;												//finally update the new value
					}

				}
			}
			//cout << "inserting comment" << endl;
		}
		/*for (int i = 0;i < n;i++)														//print the values of end point and its minimum distance
		{
			cout << i << " " << distance[i] << endl;
		}*/
		delete[] distance;																//delete distance and visited to release space from pointers
		delete[] visited;																//unnecessary for a bad programmer
	}
	void create()
	{
		cout << "Enter no of vertices" << endl;										//Entering no of vertices
		int n, e;
		cin >> n;			
		int **edges = new int*[n];													//pointer array of edges made....two ** cause we have two dimensional array of pointer to pointer
																					//in this case we are just making a new 1 dimensional array of edges
		for (int i = 0;i < n;i++)
		{
			edges[i] = new int[n];													//here, we are adding n new integers to every edge[i], thus making it a two dimensional array
			for (int j = 0;j < n;j++)
			{
				edges[i][j] = 0;													//initialising all values to zeros.. unnecessary whil using adjacency list
			}
		}
		cout << "Enter no of edges" << endl;
		cin >> e;
		int wt;
		for (int i = 0;i < e;i++)
		{
			int f, s;
			cout << "Enter first, second and weight of the edge and also the traffic congestion in terms of units" << endl;			//giving input in terms of pair of edges
			cin >> f >> s >> wt>>traffic;
			edges[f][s] = wt*traffic;
			edges[s][f] = wt*traffic;
		}
		djiktras(edges, n,0);
		for (int i = 0;i < n;i++)														//display function just to check if the adjacenecy matrix is properly formed or not
		{
			for (int j = 0;j < n;j++)
			{
				cout << edges[i][j] << " ";
			}
			cout << endl;
		}
	}
};
	int main()
	{
		graph gh;																	//everything is declared in class. So making object of class graph
		gh.create();																//function call in class graph using object
	}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
// 6. In the future, to open this project again, go to File > Open > Project and select the .sln file

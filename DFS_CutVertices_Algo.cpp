//============================================================================
// Name        : DFS_CutVertices_Algo.cpp
//			   : Finding Cut vertices using depth-first-search (DFS)
// Author      : Ayub Shaikh
// Roll Number : CS21M515
// Version     : v.1
// Copyright   : Your copyright notice -IIT Madras Assignment

// Description :  Finding Cut vertices (articulation points in an undirected Find_CutVertices_DFS )using depth-first-search (DFS) in C++, Ansi-style
//	Date	   :  3rd- MAY -2022
//============================================================================

#include <iostream>

#include <list>
#define NIL -1
using namespace std;


class Find_CutVertices_DFS
{
    int vertices;    // Number of vertices
    list<int> *adjacency_lists;    // A dynamic array of adjacency lists

    //cout << "-----------------------------------------------------------------" << endl;
    //cout << "----LAB Programming Assignment-3 Submitted by Roll number: CS21M515 ----------" << endl;
    //cout << "------- Finding Cut vertices - depth-first-search (DFS) in C++----------" << endl;
    //cout << "-----------------------------------------------------------------" << endl;


    void doCheckCutVertices(int vertexVistedNext, bool visitedVertices[], int FindTmeVistedVerte[], int end[],
                int parentVerticesArray[], bool CutVertices[]);



public:
    Find_CutVertices_DFS(int V);   // This is class Constructor

    void inGraphAddingEdge(int v, int w);   // Thsi function to adding an edge to Find_CutVertices_DFS Graph

    void Cut_Vertices_ArticulationPoints();    //Finding CutVertices and printing
};

Find_CutVertices_DFS::Find_CutVertices_DFS(int V)
{
    this->vertices = V;
    adjacency_lists = new list<int>[V];
}

void Find_CutVertices_DFS::inGraphAddingEdge(int v, int w)
{
	adjacency_lists[v].push_back(w);
	adjacency_lists[w].push_back(v);  // Find_CutVertices_DFS is undirected
}


void Find_CutVertices_DFS::doCheckCutVertices(int vertexVistedNext, bool visitedVertices[], int FindTimeVistedVerte[],
                                      int low[], int parentVerticesArray[], bool ap[])
{


    static int time = 0;

    // Count of children in DFS Tree
    int countofChildren = 0;

    // visitedVertices Mark the current node as visited
    visitedVertices[vertexVistedNext] = true;


    FindTimeVistedVerte[vertexVistedNext] = low[vertexVistedNext] = ++time;

    // Go through all vertices adjacent to this
    list<int>::iterator i;
    for (i = adjacency_lists[vertexVistedNext].begin(); i != adjacency_lists[vertexVistedNext].end(); ++i)
    {
        int vertexAdjNext = *i;  // v is current adjacent of u


        // in DFS tree and recur for it
        if (!visitedVertices[vertexAdjNext])
        {
        	countofChildren++;
            parentVerticesArray[vertexAdjNext] = vertexVistedNext;
            doCheckCutVertices(vertexAdjNext, visitedVertices, FindTimeVistedVerte, low, parentVerticesArray, ap);

            // Check if the subtree rooted with vertexVistedNext has a connection to
            // one of the ancestors of u
            low[vertexVistedNext]  = min(low[vertexVistedNext], low[vertexAdjNext]);



            // (1) vertexVistedNext is root of DFS tree and has two or more child.
            if (parentVerticesArray[vertexVistedNext] == NIL && countofChildren > 1)
               ap[vertexVistedNext] = true;

            if (parentVerticesArray[vertexVistedNext] != NIL && low[vertexAdjNext] >= FindTimeVistedVerte[vertexVistedNext])
               ap[vertexVistedNext] = true;
        }

        // Update for parent function calls.
        else if (vertexAdjNext != parentVerticesArray[vertexVistedNext])
            low[vertexVistedNext]  = min(low[vertexVistedNext], FindTimeVistedVerte[vertexAdjNext]);
    }
}


void Find_CutVertices_DFS::Cut_Vertices_ArticulationPoints()
{
    // First we have to Mark all the vertices as not visited
    bool *visited = new bool[vertices];
    int *findTimeVistedVerte = new int[vertices];
    int *low = new int[vertices];
    int *parent = new int[vertices];
    bool *storeCutVertices = new bool[vertices]; // To store Cut vertices points

    // Initialize parent and visited, and (Cut vertices point) arrays
    for (int i = 0; i < vertices; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
        storeCutVertices[i] = false;
    }

    // Call the recursive helper function to find Cut vertices points
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < vertices; i++)
        if (visited[i] == false)
        	doCheckCutVertices(i, visited, findTimeVistedVerte, low, parent, storeCutVertices);

    // Now ap[] contains articulation points, print them
    for (int i = 0; i < vertices; i++)
        if (storeCutVertices[i] == true)
            cout << i << " ";
}

// The MAin Function to run code
int main()
{



    cout << "-----------------------------------------------------------------" << endl;
    cout << "--LAB Programming Assignment-3 Submitted by Roll number: CS21M515 ----------" << endl;
    cout << "----------Name- Ayub Shaikh-------------------------------------------" << endl;
    cout << "------- Finding Cut vertices - depth-first-search (DFS) in C++----------" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    // Create Find_CutVertices_DFSs Graph
    cout << "\n********************************************\n ";
    cout << "\n Finding Cut vertices in FIRST Graph  : ";
           Find_CutVertices_DFS findCutVerticesInDFS(8);

           findCutVerticesInDFS.inGraphAddingEdge(0, 1);
           findCutVerticesInDFS.inGraphAddingEdge(0, 2);
           findCutVerticesInDFS.inGraphAddingEdge(1, 3);

           findCutVerticesInDFS.inGraphAddingEdge(2, 3);
           findCutVerticesInDFS.inGraphAddingEdge(3, 4);
           findCutVerticesInDFS.inGraphAddingEdge(3, 5);

           findCutVerticesInDFS.inGraphAddingEdge(4, 5);

           findCutVerticesInDFS.inGraphAddingEdge(2,6);
           findCutVerticesInDFS.inGraphAddingEdge(2,7);
           findCutVerticesInDFS.inGraphAddingEdge(6,7);


           findCutVerticesInDFS.Cut_Vertices_ArticulationPoints();
           cout << "\n\n*********************************************-\n ";

    cout << "Finding Cut vertices points in second Graph:";
    Find_CutVertices_DFS findCutVerticesDFS(5);
    findCutVerticesDFS.inGraphAddingEdge(1, 0);
    findCutVerticesDFS.inGraphAddingEdge(0, 2);
    findCutVerticesDFS.inGraphAddingEdge(2, 1);
    findCutVerticesDFS.inGraphAddingEdge(0, 3);
    findCutVerticesDFS.inGraphAddingEdge(3, 4);
    findCutVerticesDFS.Cut_Vertices_ArticulationPoints();
    cout << "\n ==================================================-\n ";
    cout << "\n Finding Cut vertices (Articulation points) in Third Graph : ";
    Find_CutVertices_DFS findCutVerticesDFSObj2(4);
    findCutVerticesDFSObj2.inGraphAddingEdge(0, 1);
    findCutVerticesDFSObj2.inGraphAddingEdge(1, 2);
    findCutVerticesDFSObj2.inGraphAddingEdge(2, 3);
    findCutVerticesDFSObj2.Cut_Vertices_ArticulationPoints();
    cout << "\n ++++++++++++++++++++++++++++++++++++++++++++++++++++++\n ";

    cout << "\n Finding Cut vertices in Fourth Find_CutVertices_DFS : ";

    Find_CutVertices_DFS findCutVerticesDFSTechObj(7);
    findCutVerticesDFSTechObj.inGraphAddingEdge(0, 1);
    findCutVerticesDFSTechObj.inGraphAddingEdge(1, 2);
    findCutVerticesDFSTechObj.inGraphAddingEdge(2, 0);
    findCutVerticesDFSTechObj.inGraphAddingEdge(1, 3);
    findCutVerticesDFSTechObj.inGraphAddingEdge(1, 4);
    findCutVerticesDFSTechObj.inGraphAddingEdge(2, 6);
    findCutVerticesDFSTechObj.inGraphAddingEdge(3, 5);
    findCutVerticesDFSTechObj.inGraphAddingEdge(4, 5);
    findCutVerticesDFSTechObj.Cut_Vertices_ArticulationPoints();



    cout << "\n ********************************************************" << endl;
    cout << "----------------------END Thank You!-----------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    int exit;
    cout << "press any number to exit: ";
    cin >> exit;
    if(exit>0){
      	   return 0;
    }
}

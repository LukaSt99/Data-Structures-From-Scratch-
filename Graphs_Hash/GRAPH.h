#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "MINHEAP.h"

using namespace std;

struct edge;//struct για την αναπαρασταση του κομβου του γραφου
struct node
{
	node *next;
	int key;
	edge *adj;
};
struct edge//struct αναπαρασταση για τουσ γειτονες στις λιστες οθσιστικα για τις ακμες
{
	int dest;
	edge *link;
    int weight;
};

class GRAPH
  {
     public:

		GRAPH();
		GRAPH(int* , int*, int);
		~GRAPH();

		int GETNODES();
		int GETEDGES();

		void del_edge(int,int);
		void insert_edge(int,int);
		void insert_node(int);

		node *Find(int );

		bool existnode(int);
        bool existedge(int,int);

		void INSERT(int,int);
		void DELETE(int,int);

		int FINDCONNECTEDCOMPONENTS ();
		void DFSU(int,bool*,int*);

		int COMPUTESPANNINGTREE();

        int COMPUTESHORTESTPATH(int,int);

        void PRINT();

    private:
        node *start;//η αρχη
		int nodes;//κραταει τους κομβους
		int edges;//κραταει τις ακμες


};
#endif // GRAPH_H


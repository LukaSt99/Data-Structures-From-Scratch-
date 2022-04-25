#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <chrono>

#include "MINHEAP.h"
#include "MAXHEAP.h"
#include "AVLTREE.h"
#include "HASHTABLE.h"
#include "GRAPH.h"

using namespace std;
using namespace std::chrono;

void Extract (string &file, int* &A, int &size) //Extracts the integers from the given file
{
    ifstream f;
    int count = 0;
    char line[20];

    f.open(file.c_str(), ios::in);
    if (f.is_open())
    {
        while(f.getline(line, 19)) //Counts the number of integers in the data file
        {
            stringstream ss(line);
            count++;
            ss.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignores the \n
        }
    }
    f.close();

    int *B;
    B = new int[count]; //Creates new array from the given number of integers in the data file

    int i = 0;

    f.open(file.c_str(), ios::in);
    if (f.is_open())
    {
        while(f.getline(line, 19)) //Reads each line (one integer) and inserts it into the temporary B array
        {
            stringstream ss(line);
            ss >> B[i];
            i++;
            ss.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    f.close();

    size = count; //returns the array by reference (the variables size and array A are called by reference)
    A = B;
}

void Extract (string &file, int* &A, int* &B, int &size) //Extracts the integer PAIRS from the given file. It is used for the Graphs.
{
    ifstream f;
    int count = 0;
    char line[20];

    f.open(file.c_str(), ios::in);
    if (f.is_open())
    {
        while(f.getline(line, 19)) //Counts the number of integers in the data file
        {
            stringstream ss(line);
            count++;
            ss.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignores the \n
        }
    }
    f.close();

    int *C, *D;
    C = new int[count]; //Creates two arrays this time from the given number of integers in the data file
    D = new int[count];

    int i = 0;

    f.open(file.c_str(), ios::in);
    if (f.is_open())
    {
        while(f.getline(line, 19)) //Reads each line (a pair of integers) and inserts them into the temporary C and D arrays
        {
            stringstream ss(line);
            ss >> C[i];
            ss >> D[i];
            i++;
            ss.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    f.close();

    size = count; //returns the array by references (all the variables are called by reference)
    A = C;
    B = D;
}

int main()
{
    ifstream f;
    ofstream of;
    char line[60];

    of.open("output.txt");
    of.close(); //creates, or initializes the output.txt file at every start of the program


    MINHEAP *minheap; //Pointers to each data structure we had to create so that we create a dynamic object of each data structure using the integer data files and the commands.txt
    MAXHEAP *maxheap;
    AVLTREE *avltree;
    HASHTABLE *hashtable;
    GRAPH *graph;

    minheap = NULL; //Initializes to null because it was giving problems when there was only one build command of only one structure
    maxheap = NULL;
    avltree = NULL;
    hashtable = NULL;
    graph = NULL;

    f.open("commands.txt", ios::in); //Opens commands.txt
    if(f.is_open())
    {
        while (f.getline(line, 59))
        {
            string command, structure, arg1, arg2; //Each line of commands.txt consists of the command, the data structure to which we want to apply the command, and one or two other arguments, depending on the structure and the command. Ex. In the Graphs, we need two arguments to represent the nodes.

            stringstream ss(line); //Reads each line and separates the stringstream into the variables "command", "structure", "arg1" and "arg2".
            ss >> command;
            ss >> structure;
            ss >> arg1;
            ss >> arg2;
            ss.ignore(numeric_limits<streamsize>::max(), '\n');

            if(!structure.compare("MINHEAP")) //Compares the string "structure" to the data structure names.
            {
                if(!command.compare("BUILD"))
                {
                    int *A, minhsize; //Creates an int array and sets it to NULL. We found that if we don't initialize it to NULL, there was a problem assigning the extracted numbers from the data file to the array A
                    A = NULL;

                    Extract(arg1, A, minhsize); //Calls Extract and fills A with the integers from the data file and assigns its size to minhsize

                    auto start = chrono::steady_clock::now(); //Starting timepoint to calculate the time needed to build the minheap

                    minheap = new MINHEAP(A, minhsize); //Builds the MINHEAP

                    auto finish = steady_clock::now(); //Sets the end point
                    auto duration = duration_cast<microseconds>(finish - start); //Subtracts the end point from the start point and casts it to microseconds (for greater resolution)
                    double micros = (double)duration.count();

                    minheap->SHOW(); //Displays the minheap array

                    ofstream of; //Opens the output.txt file to write the command results into. It is opened with "append".
                    of.open("output.txt", ios::app);
                    if(of.is_open())
                    {
                        of << "MINHEAP CREATED" << endl; //Writes the results to the txt file.
                        of << micros << " microseconds" << endl;
                    }
                    of.close();

                }
                if(minheap != NULL) //Just in case something went wrong with creating the minheap.
                {
                    if (!command.compare("GETSIZE"))
                    {
                        auto start = chrono::steady_clock::now();

                        int s = minheap->GETSIZE();

                        auto finish = steady_clock::now();
                        auto duration = duration_cast<microseconds>(finish - start);
                        double micros = (double)duration.count();

                        of.open("output.txt", ios::app);
                        if(of.is_open())
                        {
                            of << "MINHEAP SIZE: " << s << endl;
                            of << micros << " microseconds" << endl;
                        }
                        of.close();
                    }
                    else
                    {
                        if(!command.compare("FINDMIN"))
                        {
                            auto start = steady_clock::now();

                            int m = minheap->FINDMIN();

                            auto finish = steady_clock::now();
                            auto duration = duration_cast<microseconds>(finish - start);
                            double micros = (double)duration.count();

                            of.open("output.txt", ios::app);
                            if(of.is_open())
                            {
                                of << "MINHEAP MIN: " << m << endl;
                                of << micros << " microseconds" << endl;
                            }
                            of.close();
                        }
                        else
                        {
                            if(!command.compare("INSERT"))
                            {
                                int k = stoi(arg1); //The INSERT command's third argument is an integer. Using stoi(str) i cast the string into an integer

                                auto start = steady_clock::now();

                                minheap->INSERT(k);

                                auto finish = steady_clock::now();
                                auto duration = duration_cast<microseconds>(finish - start);
                                double micros = (double)duration.count();

                                minheap->SHOW();

                                of.open("output.txt", ios::app);
                                if(f.is_open())
                                {
                                    of << "VALUE INSERTED" << endl;
                                    of << micros << " microseconds" << endl;
                                }
                                of.close();
                            }
                            else
                            {
                                if(!command.compare("DELETEMIN"))
                                {
                                    auto start = steady_clock::now();

                                    minheap->DELETEMIN();

                                    auto finish = steady_clock::now(); //Sets the end point
                                    auto duration = duration_cast<microseconds>(finish - start); //Subtracts the end point from the start point and casts it to microseconds (for greater resolution)
                                    double micros = (double)duration.count();

                                    minheap->SHOW();

                                    of.open("output.txt", ios::app);
                                    if(of.is_open())
                                    {
                                        of << "MIN DELETED" << endl;
                                        of << micros << " microseconds" << endl;
                                    }
                                    of.close();
                                }
                            }
                        }
                    }
                }
            }
            else if(!structure.compare("MAXHEAP")) //The code is similar to MINHEAP above
            {
                if(!command.compare("BUILD"))
                {
                    int *B;
                    int maxhsize;
                    B = NULL;

                    Extract(arg1, B, maxhsize);

                    auto start = steady_clock::now();

                    maxheap = new MAXHEAP(B, maxhsize);

                    auto finish = steady_clock::now();
                    auto duration = duration_cast<microseconds>(finish - start);
                    double micros = (double)duration.count();
                    maxheap->SHOW();

                    of.open("output.txt", ios::app);
                    if(of.is_open())
                    {
                        of << "MAXHEAP CREATED" << endl;
                        of << micros << " microseconds" << endl;
                        of.close();
                    }
                }
                    else
                    {
                        if(!command.compare("GETSIZE"))
                        {
                            auto start = steady_clock::now();

                            int s = maxheap->GETSIZE();

                            auto finish = steady_clock::now();
                            auto duration = duration_cast<microseconds>(finish - start);
                            double micros = (double)duration.count();

                            of.open("output.txt", ios::app);
                            if(of.is_open())
                            {
                                of << "MAXHEAP SIZE: " << s << endl;
                                of << micros << " microseconds" << endl;
                            }
                            of.close();
                        }
                        else
                        {
                            if(!command.compare("FINDMAX"))
                            {
                                auto start = steady_clock::now();

                                int m = maxheap->FINDMAX();

                                auto finish = steady_clock::now();
                                auto duration = duration_cast<microseconds>(finish - start);
                                double micros = (double)duration.count();

                                of.open("output.txt", ios::app);
                                if(of.is_open())
                                {
                                    of << "MAXHEAP MAX: " << m << endl;
                                    of << micros << " microseconds" << endl;
                                }
                                of.close();

                            }
                            else
                            {
                                if(!command.compare("INSERT"))
                                {
                                    int k = stoi(arg1);

                                    auto start = steady_clock::now();

                                    maxheap->INSERT(k);

                                    auto finish = steady_clock::now();
                                    auto duration = duration_cast<microseconds>(finish - start);
                                    double micros = (double)duration.count();

                                    maxheap->SHOW();
                                    of.open("output.txt", ios::app);
                                    if(of.is_open())
                                    {
                                        of << k << " INSERTED" << endl;
                                        of << micros << " microseconds" << endl;
                                    }
                                }
                                else
                                {
                                    if(!command.compare("DELETEMAX"))
                                    {
                                        auto start = steady_clock::now();

                                        maxheap->DELETEMAX();

                                        auto finish = steady_clock::now();
                                        auto duration = duration_cast<microseconds>(finish - start);
                                        double micros = (double)duration.count();

                                        of.open("output.txt", ios::app);
                                        if(of.is_open())
                                        {
                                            of << "MAX DELETED" << endl;
                                            of << micros << " microseconds" << endl;
                                        }
                                        of.close();

                                        maxheap->SHOW();
                                    }
                                }
                            }
                        }
                    }
                }
                else if (!structure.compare("AVLTREE"))
                {
                    if(!command.compare("BUILD"))
                    {
                        int *A, avlsize; //The integer extraction process is the same as above
                        A = NULL;
                        Extract(arg1, A, avlsize);

                        auto start = steady_clock::now();

                        avltree = new AVLTREE(A, avlsize);

                        auto finish = steady_clock::now();
                        auto duration = duration_cast<microseconds>(finish - start);
                        double micros = (double)duration.count();

                        avltree->PRINTINORDER();

                        of.open("output.txt", ios::app);
                        if(of.is_open())
                        {
                            of << "AVLTREE CREATED" << endl;
                            of << micros << " microseconds" << endl;
                        }
                        of.close();
                    }
                    else
                    {
                        if(!command.compare("GETSIZE"))
                        {
                            auto start = steady_clock::now();

                            int s = avltree->GETSIZE();

                            auto finish = steady_clock::now();
                            auto duration = duration_cast<microseconds>(finish - start);
                            double micros = (double)duration.count();

                            of.open("output.txt", ios::app);
                            if(of.is_open())
                            {
                                of << "AVLTREE SIZE: " << s << endl;
                                of << micros << " microseconds" << endl;
                            }
                            of.close();
                        }
                        else
                        {
                            if(!command.compare("SEARCH"))
                            {
                                int k = stoi(arg1); //Casts the integer which is in string form (arg1) to integer

                                auto start = steady_clock::now();

                                string found = avltree->SEARCH(k);

                                auto finish = steady_clock::now();
                                auto duration = duration_cast<microseconds>(finish - start);
                                double micros = (double)duration.count();

                                of.open("output.txt", ios::app);
                                if(of.is_open())
                                {
                                    of << found << endl;
                                    of << micros << " microseconds" << endl;
                                }
                                of.close();
                            }
                            else
                            {
                                if(!command.compare("INSERT"))
                                {
                                    int k = stoi(arg1);

                                    auto start = steady_clock::now();
                                    avltree->INSERT(k);
                                    auto finish = steady_clock::now();
                                    auto duration = duration_cast<microseconds>(finish - start);
                                    double micros = (double)duration.count();

                                    avltree->PRINTINORDER();

                                    of.open("output.txt", ios::app);
                                    if(of.is_open())
                                    {
                                        of << k << " INSERTED" << endl;
                                        of << micros << " microseconds" << endl;
                                    }
                                    of.close();
                                }
                                else
                                {
                                    if(!command.compare("DELETE"))
                                    {
                                        int k = stoi(arg1);
                                        auto start = steady_clock::now();

                                        avltree->DELETE(k);

                                        auto finish = steady_clock::now();
                                        auto duration = duration_cast<microseconds>(finish - start);
                                        double micros = (double)duration.count();

                                        avltree->PRINTINORDER();

                                        of.open("output.txt", ios::app);
                                        if(of.is_open())
                                        {
                                            of << k << " DELETED" << endl;
                                            of << micros << " microseconds" << endl;
                                        }
                                        of.close();
                                    }
                                }
                            }
                        }
                    }
                }
            else if(!structure.compare("HASHTABLE"))
            {
                if(!command.compare("BUILD"))
                {
                    int *A, hashsize = 0;
                    A = NULL;

                    Extract(arg1, A, hashsize);

                    auto start = steady_clock::now();

                    hashtable = new HASHTABLE(A, hashsize);

                    auto finish = steady_clock::now();
                    auto duration = duration_cast<microseconds>(finish - start);
                    double micros = (double)duration.count();

                    hashtable->PRINT();
                    of.open("output.txt", ios::app);
                    if(of.is_open())
                    {
                        of << "HASHTABLE CREATED" << endl;
                        of << "TIMES REHASHED: " << hashtable->Getrehashed() << endl;
                        of << micros << " microseconds" << endl;
                    }
                    of.close();
                }
                else
                {
                    if(!command.compare("GETSIZE"))
                    {
                        of.open("output.txt", ios::app);

                        auto start = steady_clock::now();
                        int s = hashtable->GETSIZE();
                        auto finish = steady_clock::now();
                        auto duration = duration_cast<microseconds>(finish - start);
                        double micros = (double)duration.count();

                        if (of.is_open())
                        {
                            of << "HASHTABLE SIZE: " << s << endl;
                            of << micros << " microseconds" << endl;
                        }
                        of.close();
                    }
                    else
                    {
                        if(!command.compare("INSERT"))
                        {
                            auto start = steady_clock::now();

                            hashtable->INSERT(stoi(arg1));

                            auto finish = steady_clock::now();
                            auto duration = duration_cast<microseconds>(finish - start);
                            double micros = (double)duration.count();

                            of.open("output.txt", ios::app);
                            if(of.is_open())
                            {
                                of << arg1 << " INSERTED" << endl;
                                of << micros << " microseconds" << endl;
                            }
                            of.close();
                            hashtable->PRINT();

                        }
                        else
                        {
                            if(!command.compare("SEARCH"))
                            {
                                auto start = steady_clock::now();

                                string found = hashtable->SEARCH(stoi(arg1));
                                auto finish = steady_clock::now();
                                auto duration = duration_cast<microseconds>(finish - start);
                                double micros = (double)duration.count();

                                of.open("output.txt", ios::app);
                                if(of.is_open())
                                {
                                    of << found << endl;
                                    of << micros << " microseconds" << endl;
                                }
                                of.close();
                            }
                        }
                    }
                }
            }
            else
            {
                if(!command.compare("BUILD"))
                {
                    int *A, *B; //This time we use the second Extract function, because this time we need a pair of integers to represent a connection in the graph.
                    int graphsize;
                    B = NULL;

                    Extract(arg1, A, B, graphsize);

                    auto start = steady_clock::now();

                    graph = new GRAPH(A, B, graphsize);

                    auto finish = steady_clock::now();
                    auto duration = duration_cast<microseconds>(finish - start);
                    double micros = (double)duration.count();

                    graph->PRINT();

                    of.open("output.txt", ios::app);
                    if(of.is_open())
                    {
                        of << "GRAPH CREATED" << endl;
                        of << micros << " microseconds" << endl;
                    }
                    of.close();
                }
                else
                {
                      if(!command.compare("GETSIZE"))
                        {
                            auto start = chrono::steady_clock::now();

                            int n = graph->GETNODES(); //The size of a graph is the number of its nodes and the number of its edges
                            int e = graph->GETEDGES();

                            auto finish = steady_clock::now();
                            auto duration = duration_cast<microseconds>(finish - start);
                            double micros = (double)duration.count();

                            of.open("output.txt", ios::app);
                            if(of.is_open())
                            {
                                of << "GRAPH SIZE: " << endl;
                                of << "NODES: " << n << endl;
                                of << "EDGES: " << e << endl;
                                of << micros << " microseconds" << endl;
                            }
                            of.close();
                        }
                        else
                        {
                            if(!command.compare("COMPUTESHORTESTPATH"))
                            {
                                auto start = chrono::steady_clock::now();

                                int s = graph->COMPUTESHORTESTPATH(stoi(arg1), stoi(arg2));

                                auto finish = steady_clock::now();
                                auto duration = duration_cast<microseconds>(finish - start);
                                double micros = (double)duration.count();

                                of.open("output.txt", ios::app);
                                if(of.is_open())
                                {
                                    of << "SHORTEST PATH: " << s << endl;
                                    of << micros << " microseconds" << endl;
                                }
                                of.close();
                            }
                            else
                            {
                                if(!command.compare("COMPUTESPANNINGTREE"))
                                {
                                    auto start = steady_clock::now();

                                    int st = graph->COMPUTESPANNINGTREE();

                                    auto finish = steady_clock::now();
                                    auto duration = duration_cast<microseconds>(finish - start);
                                    double micros = (double)duration.count();

                                    of.open("output.txt", ios::app);
                                    if(of.is_open())
                                    {
                                        of << "SPANNING TREE : " << st << endl;
                                        of << micros << " microseconds" << endl;
                                    }
                                    of.close();
                                }
                                else
                                {
                                    if(!command.compare("FINDCONNECTEDCOMPONENTS"))
                                    {
                                        auto start = chrono::steady_clock::now();

                                        int cc = graph->FINDCONNECTEDCOMPONENTS();

                                        auto finish = steady_clock::now();
                                        auto duration = duration_cast<microseconds>(finish - start);
                                        double micros = (double)duration.count();

                                        of.open("output.txt", ios::app);
                                        if(of.is_open())
                                        {
                                            of << "CONNECTED COMPONENTS: " << cc << endl;
                                            of << micros << " microseconds" << endl;
                                        }
                                        of.close();
                                    }
                                    else
                                    {
                                        if(!command.compare("INSERT"))
                                        {
                                            auto start = steady_clock::now();

                                            graph->INSERT(stoi(arg1), stoi(arg2));

                                            auto finish = steady_clock::now();
                                            auto duration = duration_cast<microseconds>(finish - start);
                                            double micros = (double)duration.count();

                                            of.open("output.txt", ios::app);
                                            if(of.is_open())
                                            {
                                                of << arg1 << "-" << arg2 << " INSERTED" << endl;
                                                of << micros << " microseconds" << endl;
                                            }
                                            of.close();
                                            graph->PRINT();
                                        }
                                        else
                                        {
                                            if(!command.compare("DELETE"))
                                            {
                                                auto start = steady_clock::now();

                                                graph->DELETE(stoi(arg1), stoi(arg2));

                                                auto finish = steady_clock::now();
                                                auto duration = duration_cast<microseconds>(finish - start);
                                                double micros = (double)duration.count();

                                                graph->PRINT();

                                                of.open("output.txt", ios::app);
                                                if(of.is_open())
                                                {
                                                    of << "CONNECTION DELETED" << endl;
                                                    of << micros << " microseconds" << endl;
                                                }
                                                of.close();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    delete minheap; //Deletes the dynamic objects to free their memory
    delete maxheap;
    delete avltree;
    delete hashtable;
    delete graph;
}

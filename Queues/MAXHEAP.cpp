#include "MAXHEAP.h"
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

MAXHEAP::GETLEFT(int j)//επιστρεφει το αριστερο παιδι
{
    return 2 * j + 1;
}

MAXHEAP::GETRIGHT(int j)//επιστρεφει το δεξι παιδι
{
    return 2 * j + 2;
}
void MAXHEAP::SWAP(int& a, int& b)//κανει swap με αναφορα
{
    int temp = a;
    a = b;
    b = temp;
}

MAXHEAP::MAXHEAP()//κενοσ constructor
{
    data = NULL;// o πινακας null
    size = 0;
}

MAXHEAP::MAXHEAP(int *heap_Array, int heap_size) //constructor με ορισμα για να χτισει το σωρο μεγιστων σε O(n)
{
    data = new int[heap_size];
    size = heap_size;

    for(int i = 0; i < heap_size; i++)
    {
        data[i] = heap_Array[i];
    }
    // βαζοντας τα στοιχεια οπως ειναι και μετα απο κατω προσ τα πανω
    //χτιζουμε το σωρο σε O(n);
    int subtrees = floor(heap_size/2);

    for (int i = subtrees - 1; i >= 0; i--)
    {
        MAX_HEAPIFY(data, i, heap_size);
    }
}

MAXHEAP::~MAXHEAP()//destrcutor
{
    delete[] data;
}

int MAXHEAP::GETSIZE()//επιστρεφει το πληυος των στοιχειων
{
    return size;
}

int MAXHEAP::FINDMAX()//επιστρεφει το μεγαλυτερο στοιχειο που ειναι στην πρωτη θεση
{
    return data[0];
}

void MAXHEAP::MAX_HEAPIFY(int *heapArray, int i, int heap_size)//heapify δεχονας το πινακα την θεση και το size του σωρου

    //βρισκοντας τα παιδια κανουμε συγκρισεις για να βρουμε το μεγαλυτερο και αν θα πρεπει να ανεβει πρψσ τα πανω η οχι
{
    //κανει heapify δεχοντας το πινακα με τα στοιεχεια
    //και καθε φορα βρισκει το μεγαλυτεο μεταζυ των παιδιβν ετσι ωστε αν χρειαστει να ανεβαινει πανω στο σωρο
    int largest = 0;
    int leftchild = GETLEFT(i);
    int rightchild = GETRIGHT(i);

    if ((leftchild < heap_size) && (heapArray[leftchild] > heapArray[i]))
    {
        largest = leftchild;
    }
    else
    {
        largest = i;
    }
    if ((rightchild < heap_size) && (heapArray[rightchild] > heapArray[largest]))
    {
        largest = rightchild;
    }
    if (largest != i)
    {
        SWAP(heapArray[i], heapArray[largest]);
        MAX_HEAPIFY(heapArray, largest, heap_size);
    }

    return;
}

void MAXHEAP::INSERT(int num)//insert για στοιχειο στη main
{
    int *newdata, i;

    size++;
    //για καθε στοιχειο που μαινει μεγαλωνω δθναμικα το πινακα
    if(data != NULL)
    {

        newdata = new int[size]; //Creates a new array with previous size+1 elements
        for (i = 0; i < size; i++)
        {
            newdata[i] = data[i];
        } //Assigns the old data to the new array

        i = size - 1; //Index of the last element
        newdata[i] = num; //inserts the new integer into the new array
        int n = size;
        int subtrees = (n / 2);

        for (int i = subtrees - 1; i >= 0; i--)
        {
            MAX_HEAPIFY(newdata, i, size);
        }

        delete[] data;
        data = newdata;


    }
    else
    {
        data = new int[1];
        data[0] = num;
    }
}

void MAXHEAP::DELETEMAX()//κανει delete to μεγαλυτερο στοιχειο
{

    SWAP(data[0],data[size-1]);//swap το τελευταιο με το πρωτο και σβηνω το τελευταιο με ενα αλλο πινακα με size-1
    size = size - 1;

    int *temp;
    temp = new int[size];

    for (int i = 0; i < size; i++)
    {
        temp[i] = data[i];
    }

    int n = size;
    int subtrees = (n / 2);
    //κανω heapify αν θα χρειαστει η ριζα να κατεβει κατω

    for (int i = subtrees - 1; i >= 0; i--)
    {
        MAX_HEAPIFY(temp, i, size);
    }

    delete[] data;
    data = temp;
}

void MAXHEAP::SHOW()
//εμφανιζει τα στοιχεια στο αρχειο
{
    ofstream f;
    f.open("output.txt", ios::app);
    if(f.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            f << data[i] << " ";
            if (!(i % 100) && i > 0)
            {
                f << endl;
            }
        }
        f << endl;
    }
    f.close();
}

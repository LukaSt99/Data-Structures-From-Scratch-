#include "MINHEAP.h"
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int MINHEAP::GETLEFT(int j)
{
    return 2 * j + 1;
}

int MINHEAP::GETRIGHT(int j)
{
    return 2 * j + 2;
}
void MINHEAP::SWAP(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

MINHEAP::MINHEAP()
{
    data = NULL;
    size = 0;
}

MINHEAP::MINHEAP(int *heap_Array, int heap_size) //This implementation will build the MinHeap in O(n), t is the time taken to execute the function
{
    data = new int[heap_size];
    size = heap_size;
     // βαζοντας τα στοιχεια οπως ειναι και μετα απο κατω προσ τα πανω
    //χτιζουμε το σωρο σε O(n) κανωντας συγκρισεις

    for(int i = 0; i < heap_size; i++)
    {
        data[i] = heap_Array[i];
    }

    int subtrees = floor(heap_size/2);

    for (int i = subtrees - 1; i >= 0; i--)
    {
        MIN_HEAPIFY(data, i, heap_size);
    }
}

MINHEAP::~MINHEAP()
{
    delete[] data;
}

int MINHEAP::GETSIZE()
{
    return size;
}

int MINHEAP::FINDMIN()
{
    return data[0];
}

void MINHEAP::MIN_HEAPIFY(int *heapArray, int i, int heap_size)//heapify δεχονας το πινακα την θεση και το size του σωρου
{
    //βρισκοντας τα παιδια κανουμε συγκρισεις για να βρουμε το μεγαλυτερο και αν θα πρεπει να ανεβει πρψσ τα πανω η οχι
    int smallest = 0;
    int leftchild = GETLEFT(i);
    int rightchild = GETRIGHT(i);

    //κανει heapify δεχοντας το πινακα με τα στοιεχεια
    //και καθε φορα βρισκει το μεγαλυτεο μεταζυ των παιδιων ετσι ωστε αν χρειαστει να ανεβαινει πανω στο σωρο
    //αυτα εφαρμοζονται στον ιδιο τον πινακα
    if ((leftchild < heap_size) && (heapArray[leftchild] < heapArray[i]))
    {
        smallest = leftchild;
    }
    else
    {
        smallest = i;
    }
    if ((rightchild < heap_size) && (heapArray[rightchild] < heapArray[smallest]))
    {
        smallest = rightchild;
    }
    if (smallest != i)
    {
        SWAP(heapArray[i], heapArray[smallest]);
        MIN_HEAPIFY(heapArray, smallest, heap_size);
    }
    return;
}

void MINHEAP::INSERT(int num)// insert στοιχειο στο σωρο ελαχιστων Ο(logn)
{
    // καθε φορα φτιαχνουμε δυναμικα το πινακα newdata με size +1 τετοια ωστε να μπει και το καινουργιο στοιχειο
    int *newdata, i;

    size++;

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
        // μπορει να χρειαστει να κανουμε heapify για  να μπουν στις θεσεις τουσ τα στοιχεια

        for (int i = subtrees - 1; i >= 0; i--)
        {
            MIN_HEAPIFY(newdata, i, size);
        }

        delete[] data;
        data = newdata;
    }
    else
    {
        data = new int[1];
        data[0] = num; //the first integer inserted is the root
    }


}

void MINHEAP::DELETEMIN()// delete min που ειναι στην πρωτη θεση
{
    SWAP(data[0],data[size-1]);
    size=size-1;//swap το πρωτο στοιχειο με το τελευταιο και σβηνουμε το τελευταιο φτιαχνοντας ενα αλλο πινακα με size -1

    int *temp;
    temp = new int[size];

    for (int i = 0; i < size; i++)
    {
        temp[i] = data[i];
    }

    int n = size;
    int subtrees = (n / 2);

    //μπορει να χρειαστει να κανουμε heapify για να μπουν στις θεσεις τους τα στοιχεια
    for (int i = subtrees - 1; i >= 0; i--)
    {
        MIN_HEAPIFY(temp, i, size);
    }

    delete[] data;// delete το προηγουμενο
    data=temp;// update με το καινουργιο
}

void MINHEAP::SHOW()
{
    //εμφανιζουμε τα στοιχεια στο αρχειο
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

void MINHEAP::DECREASEKEY(int a, int b)//κανουμε ανικατασταση στην υεση με index a την τιμη b Ο(n)
{
    data[a] = b;

    //θα μπορει να χρειαστει να ανεβει η καινουργια τιμη οποτε κανουμε heapify//O(logn)
    int subtrees = floor(size/2);

    for (int i = subtrees - 1; i >= 0; i--)
    {
        MIN_HEAPIFY(data, i, size);
    }

                                    //logn + n= nlogn (θα μπορουσαμε και σε O(logn) αλλα θα επρεπε να χρεισημοποιησαμε hashmap)

    return;
}

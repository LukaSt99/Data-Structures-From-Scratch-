#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;
#include <iostream>

class HASHTABLE//
{
   struct Hashnode//struct για την αναπαρασταση tou hash
    {
        int key;
        Hashnode *next;
    };

    public:

        HASHTABLE();
        HASHTABLE(int*, int);
        ~HASHTABLE();
        void INSERT(int);
        string SEARCH(int);
        int  GETSIZE();
        void PRINT();
        int Getfilled()
        {
            return filled;
        };
        int Getallelements()
        {
            return allelements;
        }
        int Getrehashed()
        {
            return rehashed;
        }
        void DOUB();

    private:
        Hashnode **Hashtable;//πινακα απο δεικτες για την αναπαραστση του hashtable με αλυσιδες
        int HashFunction(int);
        int Hsize;//το size του πινακα
        int filled;//μονο τα στοιχεια στο πινακα οχι στισ αλυσιδεσ
        int allelements;
        int rehashed;
};

#endif // HASHTABLE_H

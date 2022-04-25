#ifndef MAXHEAP_H
#define MAXHEAP_H


class MAXHEAP
{
    public:
        MAXHEAP(int *, int);
        MAXHEAP();
        ~MAXHEAP();
        int GETSIZE();
        int FINDMAX();
        void INSERT(int );
        void DELETEMAX();
        void SHOW();

    private:
        int *data;//πινακα για την αναπαραστση του σωρου μεγιστου
        int size;
        void SWAP(int&, int&);
        void MAX_HEAPIFY(int *,int,int);
        int GETLEFT(int);
        int GETRIGHT(int);

};

#endif // MAXHEAP_H


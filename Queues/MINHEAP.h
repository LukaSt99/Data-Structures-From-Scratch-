#ifndef MINHEAP_H
#define MINHEAP_H


class MINHEAP
{
    public:
        MINHEAP(int *, int);
        MINHEAP();
        ~MINHEAP();
        int GETSIZE();
        int FINDMIN();
        void INSERT(int );
        void DELETEMIN();
        void DECREASEKEY(int,int);
        void SHOW();

    private:
        int *data;//πινακ για την αναπαρασταση του σωρου ελαχιστου
        int size;
        void SWAP(int&, int&);
        void MIN_HEAPIFY(int *,int,int);
        int GETLEFT(int);
        int GETRIGHT(int);

};

#endif // MINHEAP_H

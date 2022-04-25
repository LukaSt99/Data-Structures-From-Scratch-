#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

using namespace std;

struct AvlNode//struct για την αναπαρασταση του κομνβου
    {
        int key;
        AvlNode *left;
        AvlNode *right;
        int height;
    };

class AVLTREE
{
    public:
        AVLTREE();
        AVLTREE(int *, int);
        ~AVLTREE();
        void DELETE(AvlNode *);

        AvlNode* FINDMINNode(AvlNode*);

        int NodeHeight(AvlNode  *);
        AvlNode* rightRotate(AvlNode *);
        AvlNode* leftRotate(AvlNode *);

        int Balance(AvlNode *);

        AvlNode* INSERT(AvlNode *, int );
        void INSERT(int);

        AvlNode* DELETE(AvlNode *, int );
        void DELETE(int);

        int FINDMIN(AvlNode*);
        int FINDMIN();

        void inorder(AvlNode*);
        void PRINTINORDER();

        int GETSIZE(AvlNode*);
        int GETSIZE();

        bool SEARCH(AvlNode *, int );
        string SEARCH(int);

    private:
        AvlNode *root;//η αρχη ριζα
};

#endif // AVLTREE_H

#include "AVLTREE.h"
#include <iostream>
#include <fstream>

using namespace std;

AVLTREE::AVLTREE()//κενος constructor , η αρχη ειναι null
{
    root = NULL;
}

AVLTREE::AVLTREE(int *A, int size)//constructor με ορισμα το πινακα με τα στοιχεια και το size του για το BUILD της AVL
{
    root = NULL;
    for (int i = 0; i < size; i++)
    {
        INSERT(A[i]);
    }
}

AVLTREE::~AVLTREE()
{
    DELETE(root);//DESTRUCTOR
}

void AVLTREE::DELETE(AvlNode *root)//διαγραφει ενα κομβο δεχοντας σαν ορισμα την διευθυνση του
{
    if ( root != NULL )// χωρισ να επιστρεφει τιποτα (void)
    {
        DELETE ( root -> left ) ;// κανει delete με recursion ολα τα παιδια του  left
        DELETE ( root -> right ) ;// και right
    }
    delete ( root ) ;//διαγραφει την ριζα
}
int AVLTREE::NodeHeight(AvlNode *N)
{
    if (N != NULL)
        return N->height;// επιστρεφει την height ενος κομβου περνωντας σαν ορισμα την διευθυνση του
    return 0;

}
AvlNode* AVLTREE::FINDMINNode(AvlNode* node)
{
    AvlNode* curr=node;
    while(curr->left != NULL)//επιστρεφει την θεση του κομβου με το μικροτερο key
    {
        curr=curr->left;//πηγαινοντας καθε φορα προσς τα αριστερα εκει που θα βρισκεται το μικροτερο στοιχειο
    }
    return curr;//επιστρεφει την διευθυνση
}
AvlNode* AVLTREE::rightRotate(AvlNode *node)// εφαρμοζει την δεξια περιστροφη της AVL επιστρεφοντας την  διευθυνση του κομβου
{
    AvlNode *temp = node->left;// θετοντας την temp σαν αρστερο παιδι
    AvlNode *temp2 = temp->right;//και την τεmp2 σαν δεξιο της temp

    temp->right = node;//και το δεξι του temp σαν node
    node->left = temp2;// το αριστερο του node σαν temp2


   //υπολογισουμε τα height και των δυο μεριων
   //και το κραταμε σε ενα TEMP +1
    int TEMP;
    if(NodeHeight(node->left) > NodeHeight(node->right))
        TEMP=NodeHeight(node->left)+1;
    else
        TEMP=NodeHeight(node->right)+1;
    node->height=TEMP;
    //αρα το height του node ειναι το TEMP

    //kai του temp ειναι το TEMP2
    int TEMP2;
    if(NodeHeight(temp->left) > NodeHeight(temp->right))
        TEMP2=NodeHeight(temp->left)+1;
    else
        TEMP2=NodeHeight(temp->right)+1;
    temp->height=TEMP2;

    return temp;
}
AvlNode* AVLTREE::leftRotate(AvlNode *node)
{
    //οπως υπολογισαμε το προηγουμενο
    //υπολογιζουμε τα height καθε μεριων θετωντας σε temp
    //ετσι βρισκουμε το μερος που θα πρεπει να κανουμε peristrofh κανωντας return την διευθυνση του
    AvlNode *temp = node->right;
    AvlNode *temp2 = temp->left;

    temp->left = node;
    node->right = temp2;

    int TEMP;
    if(NodeHeight(node->left) > NodeHeight(node->right))
        TEMP=NodeHeight(node->left)+1;
    else
        TEMP=NodeHeight(node->right)+1;
    node->height=TEMP;

    int TEMP2;
    if(NodeHeight(temp->left) > NodeHeight(temp->right))
        TEMP2=NodeHeight(temp->left)+1;
    else
        TEMP2=NodeHeight(temp->right)+1;
    temp->height=TEMP2;
    return temp;
}

int AVLTREE::Balance(AvlNode *node)//υπολογιζει την διαφορα  των heights δυο υποδενδρων και το επιστρεφει
{
    if (node != NULL)//αν η ριζα δεν ειναι null
        return NodeHeight(node->left) - NodeHeight(node->right);//τοτε επιστρεφει την διαφορα μεταξυ του αριστερου και δεξιου παιδιου
    return 0;
}

AvlNode* AVLTREE::INSERT(AvlNode* node, int key)//κανει insert κομβου δεχοντας ενα key και την διευθυνση του κομβου
{
    if (node == NULL)// αν δεν υπαρχει στοιχεια φτιαχνουμε το κομβο που θα ειναι η ριζα
    {
        AvlNode* node = new AvlNode();
        node->key = key;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        return(node);
    }

    // ελενχουμε σε ποιο μερος πρεπει να μπει αν εχει στοιχεια το δενδρο
    //συγκρινωντας τα στοιχεια , αν ειναι μικροτερος θα παει αριστερα της ριζας αλλιως δεξια καθε φορα αλλαζοντας την ριζα
    //με το αριστερο η δεξι παιδι εξαρτητος την συγκρισει , και αυτο το κανουμε με αναδρομη μεχρι να βρει την θεση του
    //ο κομβος με το περιορισμο οτι δεξια ειναι μεγαλυτερα και αριστερα μικροτερα στοιχεια για καυε κομβο
    if (key <= node->key)
        node->left = INSERT(node->left, key);
    else if (key > node->key)
        node->right = INSERT(node->right, key);
    else
        return node;

    // οταν θα τελειωσει η εισαγωγη μπορει να χρειαστει να γινονται περιστροφες για να ειναι το δενδρο avl
    //οποτε υπολογιζουμε το height
    int TEMP;
    if(NodeHeight(node->left) > NodeHeight(node->right))
        TEMP=NodeHeight(node->left)+1;
    else
        TEMP=NodeHeight(node->right)+1;
    node->height=TEMP;
    //υπολογιζουμε την διαφορα των height καλωντας την balance

    int bal = Balance(node);
    // και κανουμε συγκρισεις ωστε να βρουμε τη περιστροφη χρειαζεται
    //αν η διαφορα ειναι μεγαλυτερη απο ενα και η τιμη που μπηκε μικροτερη του αριστερου παιδιου τοτε->οπου βρισκουμε το κομβο που πρεπει να κανουμε περιστροφη
    //τοτε εχουμε πολλα στοιχεια στο αριστερο(επειδη η διαφορα του αριστερου με το δεξι βγαινει θετικο) μεροσ οποτε θα κανουμε δεξι περιστροφη στη node
    if (bal > 1 && key < node->left->key)
        return rightRotate(node);

    //το ιδιο θα ειναι αν εχει η bal ειναι <-1 που θα πει θα εχει περσσοτερα στοιχεια στο δεξι μερος
    //και αν η  key ειναι μεγαλυτερη του δεξιου μερος τοτε υα εφαρμοζουμε  leftrotate στην node

    if (bal < -1 && key > node->right->key)
        return leftRotate(node);

    if (bal > 1 && key > node->left->key)
    {
        //αν η bal ειναι μεγαλυτερη του 1 θα πει οτι το αριστερο μερος εχει περρισοτερα στοιχεια αλλα
        // η key ειναι μεγαλυτερη του αριστερου παιδιου οποτε θα πρεπει να κανουμε δυο περιστροφες
        //μια αριστερη και μια δεξι
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //το ιδιο απλα θελει μια δεξι και μετα μια αριστερη περιστροφη
    if (bal < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVLTREE::INSERT(int k)// το insert αυτο ειναι  για διευκολια για να μην χρειαζεται να βαλω την αρχη στην main για καθε insert
{
    root = INSERT(root,k);
}

int AVLTREE::FINDMIN(AvlNode *node)//επιστρεφει το μικροτερο στοιχειο του δενδρο δεχοντας την διευθυνση της αρχης
{
//οπου πηγαινωντας καθε φορα στο αριστερο μερος οπου βρισκεται το μικροτερο στοιχειο ( ο κομβος με το μικροτερο key)
    if(node == NULL)//αν εχει 0 στοιχεια
        return -1;
    else if(node->left == NULL)
        return node->key;
    else
        return FINDMIN(node->left);//recursion μεχρι να βρει το μικροτερο στο αριστερο μεροσ στο τελος
}

int AVLTREE::FINDMIN()//επιστρεφει το μικροτερο στοιχειο για την main
{
    return FINDMIN(root);//δεχεται σαν ορισμα την αρχη(ριζα)
}

void AVLTREE::inorder(AvlNode *tree)//εμφανιζει τα στοιχεια σε inorder δεχοντας σαν οριζμα την διευθυνση της αρχης της AVL
{
    //δουλευει με αναδρομη
    //εμφανιζει το αριστερο παιδι , την ριζα και μετα το δεξι μερος
    if (tree == NULL)
        return;
    inorder(tree->left);

    ofstream f;//τα εμφανιζει τα στοιχεια στο αρχειο output
    f.open("output.txt", ios::app);
    if (f.is_open())
    {
        f << tree->key << " ";
    }
    f.close();
 //   cout << tree->key << " ";
    inorder(tree->right);
}
void AVLTREE::PRINTINORDER()//χωρις ορισμα
{
    inorder(root);// η ιδια δουλεια με την προηγουμενη απλος περνει σαν οριζμα μεσα στην συναρτηση την ριζα
//για διευκολια στην main

    ofstream f;
    f.open("output.txt", ios::app);
    if(f.is_open())
    {
        f << endl;
    }
    f.close();


 //   cout << endl;
}

int AVLTREE::GETSIZE(AvlNode *node)//επιστρεφειε το size περνωντας  σαν ορισμα την διευθυνση της αρχης του avl (ριζα)
{
    //to πληθος των στοιχειων του avl καλωντας καθε φορα την getsize με αναδρομη για το αριστερο μεροσ και για το
    //δεξι συν 1 για την ριζα
    if (node == NULL)
        return 0;
    else
        return  (GETSIZE(node->left)) + 1 + (GETSIZE(node->right));//αναδρομη
}
int AVLTREE::GETSIZE()//χωρις ορισμα επιστρεφει το size (για την main)
{
    return GETSIZE(root);//καλωντας την συναρτηση απο πανω με ορισμα την διευθυνση της ριζας
}

bool AVLTREE::SEARCH(AvlNode *node, int y)// επιστρεφει 0 η 1 αν βρισκεται το στοιχειο y στο δενδρο
//δεχοντας σαν ορισμα την διευθυνση της αρχησ και την τιμη που ψαχνουμε
{
    while (node != NULL)//μεχρι να η ριζα που μετα θα κατεβαινει δεν θα ειναι null
    {
        if ( y== node->key)//αν η τιμη ειναι οσο η τιμη του κομβου επιστρεφουμε 1
            return true;
       // αν το y μεγαλυτερο θα ψαξουμε στο δεξι υποδενδρογιατι εκει βρισκονται μεγαλυτερεσ τιμες απο την ριζα
       //αλλιως κανουμε το ιδιο στο αριστερο μερος που εινια τα μικροτερα στοχεια της ριζασ
        if ( y > node->key )
            node = node->right;
        else
            node = node->left;
    }
    return false;// αν δεν το βρισκει επιστρεφει 0

}
string AVLTREE::SEARCH(int y)// το search για την main δεχεται την τιμη που ψαχνουμε και επιστρεφει succes η failure
// καλωντας την συναρτηση απο πανω και βαζοντας σαν ορισμα το root αρα την αρχη τηε avl μαζι με την τιμη που ψαχνουμε
{
    if (SEARCH(root,y))
        return "SUCCESS";
    else
        return "FAILURE";
}

AvlNode* AVLTREE::DELETE(AvlNode *node, int key )
{
    //αρχηκα θα ψαχνουμε το στειχειο
    //αν δεν ειναι η ριζα τοτε θα κατεβουμε κατω με το περιοσρισμο ορι
    //αν ειναι μικροτερο το στοιχειο που θελουμε να σβησουμε να παμε αριστερα
    //αλλιως θα παμε δεξια
    if (node == NULL)
        return node;
    if ( key < node->key )
        node->left = DELETE(node->left, key);
    else if( key > node->key )
        node->right = DELETE(node->right, key);
    else
    {
        if( (node->left == NULL) ||(node->right == NULL) )
        {
            AvlNode *temp = node->left ? node->left : node->right;

            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;
            delete(temp);
        }
        else
        {
            AvlNode* temp = FINDMINNode(node->right);
            node->key = temp->key;
            node->right = DELETE(node->right,temp->key);
        }
    }
    if (node == NULL)
        return node;

   //μετα την διαγραφει μπορει να χρειαστει να κανουμε στο δενδρο περιστροφες
   //ετσι ελενχουμε τα height για τισ διαφορεσ
   //υπολογιζοντας για την node την BALANCE αρα την height ετσι ωστε να βρισκουμε τι περιστροφη να κανουμε

    int TEMP;
    if(NodeHeight(node->left) > NodeHeight(node->right))
        TEMP=NodeHeight(node->left)+1;
    else
        TEMP=NodeHeight(node->right)+1;
    node->height=TEMP;

    int bal =Balance(node);

    if (bal > 1 && Balance(node->left) >= 0)
        return rightRotate(node);
    if (bal > 1 && Balance(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bal < -1 && Balance(node->right) <= 0)
        return leftRotate(node);
    if (bal < -1 && Balance(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;//επιστρεφουμε την διευθηνση

}
void AVLTREE::DELETE(int k)// delete στοιχειο για την main καλοντας την delete απο πανω με ανανεωνοντας την ριζα (root)
{
    root = DELETE(root,k);
}

#include "HASHTABLE.h"
#include <iostream>
#include <fstream>

using namespace std;
//hash με αλυσιδες
HASHTABLE::HASHTABLE()//κενος contructor
// φτιαχνει ενα πινακα απο δηκτες αρχικα 1000 θεσεις και θετει ολα τα αλλα 0
{
    Hsize = 1000;
    filled = 0;
    allelements = 0;
    rehashed = 0;
    Hashtable = new Hashnode*[Hsize];
    for (int i = 0; i < Hsize; i++)//καθε δηκτη στο πινακα εινα ιnull επειδη δεν εχουν μπει στοιχεια
        Hashtable[i] = NULL;
}

HASHTABLE::HASHTABLE(int *A, int size)//constructor me ορισμα ενα πινακα και την size για την buildhash για αυτα τα στοιχεια
{
    Hsize = 1000;
    filled = 0;
    allelements = 0;
    rehashed = 0;
    Hashtable = new Hashnode*[Hsize];
    for (int i = 0; i < Hsize; i++)
    {
        Hashtable[i] = NULL;
    }

    for (int i = 0; i < size; i++)
    {
        INSERT(A[i]);
    }
    //insert καθε στοιχειο στο hash

}

HASHTABLE::~HASHTABLE()//destructo
{
        delete[] Hashtable;
}

int HASHTABLE::HashFunction(int k)//συναρτηση κατακερματισμου (τα aem μασ και ενασ μεγαλος πωτος αριθμος)
{
    return (3305 *k + 3413) % 104729 % Hsize;

}
void HASHTABLE::INSERT(int k)//εισαγωγη στοιχειου στο πινακα
{
    if(filled>=Hsize/2)//διπλασιασουμε το πινακα αν τα στοιχεια στο πινακα ειναι μεγαλυτερα απο τα μισα που δεχεται
    {
       DOUB();
    }
    if(filled<Hsize/2)//αν οχι
    //φτιαχνει ενα καινουργιο στοιχειο
    {
        Hashnode *temp,*temp2;
        temp=new Hashnode;
        temp->key=k;
        temp->next=NULL;

        int index = HashFunction(k);
        //βρισκει την θεση απο την συναρτηση
        if (Hashtable[index] == NULL)
            //αν ειναι πρωτο στοιχειο μπαινει κατεθυαν
        {
            string found = SEARCH(k);

            if(!found.compare("FAILURE"))
            {
            Hashtable[index]=temp;
            filled=filled+1;
            allelements=allelements+1;
            }
        }
        else
        {
            //αλλιως θα σαρωνει ολη την συνδεδεμενη λιστα μεχρι να βρει το τελος και να βαλει το καινουγιο στοιχειο
            temp2=new Hashnode;
            temp2=Hashtable[index];
            string found = SEARCH(k);

            if(!found.compare("FAILURE"))
            {
            while (temp2->next!= NULL)
                temp2 = temp2->next;
            temp2->next=temp;
            allelements=allelements+1;
            }
        }

    }
}
void HASHTABLE::PRINT()
{
    ofstream f;
    f.open("output.txt", ios::app);
    //εμφανιζει τα στοιχεια στο αρχειο
    Hashnode *q;
    if(f.is_open())
    {
        for (int i=0; i<Hsize; i++)//μεχρι το hsize θα μπουν ολα τα στοιχεια του πινακα και για καθε στοιχειο
            //αν εχει στοιχεια που εχουν το ιδιο index απο την συναρτηση και ειναι στισ λιστεσ θα εμφανιζονται στο αρχειο
        {
            q=Hashtable[i];
            if(q==NULL)
            {
                f <<"NULL";
            }
            else
                while(q!=NULL)
                {
                    f <<"->"<<q->key;
                    q=q->next;
                }
            f<<endl;
        }
    }
    f.close();
}
string HASHTABLE::SEARCH(int k)
{
    //search ενα στοιχειο ιδια διαδικασια με την insert
    //βρισκουμε το index απο την συναρτηση
    //αν ειναι η θεση του index ειναι null δεν υπαρχει
    int index = HashFunction(k);
    if (Hashtable[index] == NULL)
             return "FAILURE";

    Hashnode *temp;
    temp = Hashtable[index];

    //αλλιως θα ψαξουμε στισ λιστες (το χειροτερο O(n))
    while (temp != NULL)
        {
          if (temp->key == k)
              return "SUCCESS";
          temp = temp->next;
        }
    return "FAILURE";
}

int HASHTABLE::GETSIZE()
{
    return Hsize;
}
void HASHTABLE::DOUB()//ειναι για να διπλασιαζει το πινακα οταν χρειαζεται και να κανει rehash τα στοιχεια
{
    rehashed++;
    Hsize=2*Hsize;
    //διπλασιαζουμε το size
    Hashnode **tmp;
    tmp=new Hashnode*[Hsize];
    //φτιαχνουμε αλλο πινακα με διπλασιο πληθο θεσεων απο το προηγουμενο
    filled=0;
    allelements=0;
    for (int i = 0; i < Hsize; i++)
        tmp[i] = NULL;
        //για τα πρωτα μια στοιχεια που ηδη ειναι μεσα κανουμε rehash στο καινουργιο με
        //διπλασιο νουμερο θεσεων
      for (int i = 0; i < Hsize/2; i++)
       {
            Hashnode *temp1;
            temp1 = Hashtable[i];

            if(temp1!=NULL)
            {
                //φτιαχνωντας για καθε στοιχειο που κανουμε rehash
                //ενα hashnode οπυ μετα το κανουμε insertστο καινουργιο
                //πινακα και με το update hashfunction
                while (temp1 != NULL)
               {

                    Hashnode *temp2,*temp3;
                    int k=temp1->key;
                    temp2=new Hashnode;
                    temp2->key=k;
                    temp2->next=NULL;

                    //βρισκουμε το indeex οπως καναμε και στο insert

                    int index = HashFunction(k);
                        if (tmp[index] == NULL)
                          {
                              tmp[index]=temp2;
                              filled=filled+1;
                              allelements=allelements+1;
                         }
                         //και αν εχει συγκρουσεις θα σαρωνει ολη την λιστα για να μπει στην θεση του
                         //κανωντας update και ολα ταsize που χρηαζομαστε
                         else
                           {
                            temp3=new Hashnode;
                            temp3=tmp[index];

                            while (temp3->next!= NULL)
                                    temp3 = temp3->next;
                            temp3->next=temp2;
                            allelements=allelements+1;
                           }

                    temp1 = temp1->next;
               }
            }
      }
     delete[] Hashtable;//σβινουμε το προηγουμενο
     Hashtable=tmp;//και κανουμε update με το καινουργιο
}

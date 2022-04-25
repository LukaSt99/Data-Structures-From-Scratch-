#include "GRAPH.h"
#include "MINHEAP.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

GRAPH::GRAPH()//κενος constructor
{
    nodes=0;
    edges=0;
    start=NULL;
}

GRAPH::GRAPH(int *A, int *B, int size)//constructor με ορισμα το πινακα με τα στοιχεια
{
    nodes = 0;
    edges = 0;
    start = NULL;

    for (int i = 0; i < size; i++)
    {
        INSERT(A[i], B[i]);
    }
    //κανει insert ολες της  ακμεες απο του πινακες
}

GRAPH::~GRAPH()//destructor
{
    delete [] start;
}
node* GRAPH::Find(int item)//επιστερεφει την διευθυνση του κομβου που ψαχνουμε
{
    node *ptr,*loc;
    ptr=start;
    //αρχιζωντας απο την start την αρχη
    //σαρωνουμε ολα τουσς κομβους κανωντας το ptr =ptr->next
	while(ptr!=NULL)
	{
		if(item==ptr->key)
		{
			loc=ptr;//επιστρεφουμε την διευθηνση αν βρισκεται στο γραφο
			return loc;
		}
		else
			ptr=ptr->next;
	}
	loc=NULL;//αλλιως null
	return loc;
}

bool GRAPH::existedge(int u,int v)
{
    //επιστρεφει 0 η 1 αν θπαρχει η ακμη απο την u στην v και αναποδα
	edge *ptr;
	ptr=Find(u)->adj;
	//βρισκωντασ με την find την θεση του κομβου u
	//ψαχνουμε στουε γειτονες του u αν υπαρχει η v
    while(ptr!=NULL)
    {
        if(ptr->dest==v)
            return true;
        else
            ptr=ptr->link;//ανανεωνουμε το δηκτη να δειχνει σττο επομενο
    }
    return false;
}
bool GRAPH::existnode(int item)
{
    //επιστρεφει 0 η 1 αν θπαρχει κομβος με τιμη item
    node *ptr;
	ptr=start;
	//ξεκιναμε απο την start
	while(ptr!=NULL)
	{
		if(item==ptr->key)//ελενχουμε αν η τιμη του κομβου ειναι ιδιο με το item
		{
			return true;
		}
		else
			ptr=ptr->next;//ανανεωνουμε το δηκτη στο να δειχνει στο επομενο
	}
    return false;
}
void GRAPH::insert_node(int x)
{
    //insert καινουγιου κομβου
    node *tmp,*ptr;
	tmp=new node;
	tmp->key=x;
	tmp->next=NULL;
	tmp->adj=NULL;
    //φτιαχνουμε καινουγιο node για κομβο

    //αν δεν θπαρχει στοιχεια θα μπει στην πρωτη θεση
	if(start==NULL)
	{
		start=tmp;
		nodes=nodes+1;
		return;
	}
	//αν δεν υπαρχει ηδη
	//σαρωνουμε ολη την λιστα με τουσ κομβους και το βαζοθυμε στην θεση του
	if(!existnode(x))
    {
	ptr=start;
	while( ptr->next!=NULL)
		ptr=ptr->next;
	ptr->next=tmp;
	nodes=nodes+1;//αυζανουμε το node
    }
}
void GRAPH::insert_edge(int u,int v)
{// insert ακμης
    node *locu;
	edge *ptr,*tmp;

	locu=Find(u);
	//βρισκουμε την θεση του u στους κομβους

	tmp=new edge;
	tmp->dest=v;
	tmp->weight=1;
	tmp->link=NULL;
 //φτιαχνουμε μια καινουργια ακμη

    //αν η u δεν εχει γειτονες θα μπει κατεθυαν στην πρβτη θεση τοων γειτωνων
	if(locu->adj==NULL)
	{
		 locu->adj=tmp;
		  return;
	}
   //αλλιψς θα προπελαση ολη την λιστα με τουσ γειτονες και θα το βαλει στην θεση του
    ptr=locu->adj;
    while(ptr->link!=NULL)
         ptr=ptr->link;
    ptr->link=tmp;
}


void GRAPH::del_edge(int u,int v)
{
    //delete ακμης
    node *locu,*locv;
	edge *ptr,*tmp,*q;
	locu=Find(u);

    //βρισκουμε την θεση της υ
    //αν ειναι στην πρωτη θεση τοτε την σβηνουμε κατεθυαν
	if(locu->adj->dest == v)
	{
		tmp=locu->adj;
		locu->adj=locu->adj->link;
		delete tmp;
		return;
	}
	//αλλιως θα ψαχνουμε στην λιστα των γειτονων μεχρι να γινεται locu->adjnull
	//αν ητιμη καποιο γειτονα ειναι ισο με την v τοτε κανουμε update τουσ δεικτες ωστε ο κομβος με τιμη v να σβηνεται απο την λιστα
	q=locu->adj;
	while(q->link->link != NULL)
	{
		if(q->link->dest==v)
		{
			tmp=q->link;
			q->link=tmp->link;
			delete tmp;
			return;
		}
		q=q->link;
	}
	if(q->link->dest==v)
	{
		tmp=q->link;
		delete tmp;
		q->link=NULL;
		return;
	}
}
void GRAPH::PRINT()
{
   //εμφανιζει τα στοιχεια στο αρχειο
   //σαρωνει ολη την λιστα με τουσ κομβους κανωντας print την key καθε κομβοθ
    node *ptr;
	edge *q;
	ofstream f;
	f.open("output.txt", ios::app);
    if(f.is_open())
    {

        ptr=start;
        //και για καθε κομβο κανει print την key καθε γειτονου
        while(ptr!=NULL)
        {
            f<<ptr->key<<"->";
            q=ptr->adj;
            while(q!=NULL)
            {
                f<<q->dest;
                q=q->link;
                f<<"->";
            }
            f<<endl;
            ptr=ptr->next;
        }
    }
    f.close();
}
void GRAPH::INSERT(int a,int b)//αυτο ειναι για insert απο την main
{
    //κανει ελενχους πριν να μπει μια ακμη
    node *loca,*locb;

	loca=Find(a);
	locb=Find(b);
     //αν δεν υπαρχουν οι κομβοι υα δημιορυγουν καινουργοι
	if(loca==NULL )
	{
		insert_node(a);
	}
	if(locb==NULL )
	{
		insert_node(b);
	}
	if(!existedge(a,b))
    {
        insert_edge(a,b);
        insert_edge(b,a);
        edges=edges+1;
    //και για καυε insert οι γειτονες θα μπαινουν και στουσ δυο κομβουσ
    //αυξανουμε το edge
    }
}
void GRAPH::DELETE(int a,int b)//αυτο ειναι για delete απο την main
{
    //το ιδιο και για το delete
    //ελενχουμε αν υπαρχουν οι κομβοι
    if(existnode(a)&& existnode(b))
        if(existedge(a,b))
        {
            //αν υπαρχει ακμη
         del_edge(a,b);
         del_edge(b,a);
         edges=edges-1;
         //update edges
        }
}
int GRAPH::GETNODES()
{
    return nodes;//επιστρεφει nodes
}
int GRAPH::GETEDGES()
{
    return edges;//επιστρεφει edges
}
int GRAPH::FINDCONNECTEDCOMPONENTS()
{
//υλοποιησει του DFS
// εφαρμοσαμε το pseudocode των σημηωσεως
   node *ptr2;
   int *NODESKEY2;
   NODESKEY2= new int [nodes];//κραταμε τους κομβους σε ενα πινακ
   ptr2=start;
   while(ptr2!=NULL)
   {
       for(int i=0;i<nodes;i++)
        {
            NODESKEY2[i]=ptr2->key;
            ptr2=ptr2->next;
        }
	}
    bool* visit = new bool[nodes];//φτιαχνουμε ενα array visit bool για
    //να κραταμε αν εχουμε περασει απο αυτο το κομβο
    for (int i=0; i<nodes; i++)
         visit[i] = false;

    int  componum=0;
    //για καθε κομβο αν η visit ειναι false ΚΑΝΟΥΜΕ DFSU σε αυτον
    for (int  v=0; v<nodes; v++)
     {
        if (visit[v] == false)
         {
            DFSU(v, visit,NODESKEY2);
            componum += 1;//κραταμε ποσεσ φορες καναμε ΔΦΣ για να μασ δειχνει ποσα conncected cmponents εχουμε
         }
     }
     return componum;//επιστρεφει το πληθος
}
void GRAPH::DFSU(int v,bool *visit,int *NODESKEY)
{
    int a;
    visit[v] = true;//κανουμε το visit του κομβου true
    node *locv;
    locv=Find(NODESKEY[v]);
    ////βρισκουμε την θεση του κομβου
    edge *o;
    o=locv->adj;
    //και για καθε γειτονα του κομβο αυτου κανουμε dfs
    while(o!=NULL)
     {
        for(int i=0;i<nodes;i++)
        {
            if(NODESKEY[i]==o->dest)
                {a=i;}
        }
        if (visit[a]==false)
            DFSU(a, visit,NODESKEY);
        o=o->link;//update δηκτη για να περασει σε ολου τους γειτονες
     }
}

int  GRAPH::COMPUTESPANNINGTREE()
{
    //εκτελουμε Prim για το minimum spannig tree
    if(FINDCONNECTEDCOMPONENTS()==1)
    {
      //αν υπαρχει ενα coonceted component τοτε εκτελουμε το prim
       node *ptr2;
       int *NODESKEY2;
       NODESKEY2= new int [nodes];//κραταμε τις τιμες των κομβων
       ptr2=start;
       while(ptr2!=NULL)
       {
           for(int i=0;i<nodes;i++)
            {
                NODESKEY2[i]=ptr2->key;
                ptr2=ptr2->next;
            }
        }
      int key[nodes];// πινακα key κραταει το τρεχον κοστοε συνδεσης
      bool color[nodes];// αν εχουμε περασει απο αυτο το κομβο
      bool color2[nodes];// για υλοποησει των γειτονων επειδη η αναπαρασταση ειναι με λιστερ
      int pred[nodes];//κραταει το προηγουμενο

      for (int i = 0; i < nodes; i++)
        {
            key[i] = INT_MAX;//intiliaze
            color[i] = false;
            color2[i]=false;
            pred[i]=INT_MAX;
        }
     key[0] = 0;
     pred[0]=-1;

     MINHEAP Q;
     for(int i=0;i<nodes;i++)
     {
         Q.INSERT(key[i]);
     }
     ////φτιαχνουμε ενα σωρο ελαχιστων για τουε key[i]
     int p=0;
     while(Q.GETSIZE()!=0)
     {
         int x=Q.FINDMIN();
         Q.DELETEMIN();
         //καθε φορα περνουμε το λιγοτερο
         int index;
         for(int i=0;i<nodes;i++)
         {
             if(x==key[i] && color2[i]==false)
               {
                 index=i;
                color2[i]=true;
                break;
               }
         }
         //βρισκουμε το index του λιγοτερου
         int u=NODESKEY2[index];
         node *locu;
         locu=Find(u);
         int index2;
         edge *o;
         o=locu->adj;
         //για καθε γειτονα του ελχισοτυ κοστος κομβου που πηραμε
         while(o!=NULL)
         {

             for(int k=0;k<nodes;k++)
             {
                 if(NODESKEY2[k]==o->dest)
                    {
                        index2=k;
                    }
              }
              if(color[index2]==false && 1< key[index2])
                 {
                    p=p+1;
                   key[index2]=1;
                   Q.DECREASEKEY(Q.GETSIZE()-p,key[index2]);
                   pred[index2]=u;
                 }
                 //αν ο δεν εχουμε περασει απο αυτο τον κομβο και το 1 επειδη ειναι χωρισ βαρη ειναι μικροτεου του key του γειτονα τοτε
                 // κανουμε update το τρεχον κοστος του γειτονα και κανουμε decrese αθτην τη τιμη στο minheap
             o=o->link;
         }
         color[index]=true;
         p=0;
     }

     int sum=0;
     for(int i=0;i<nodes;i++)
     {
             sum=sum+key[i];
     }
     return sum;
//επιστρεφουμε το μικροτερο κοστο μου βρηκαμε
     }
    else
       return -1;
}
int GRAPH::COMPUTESHORTESTPATH(int a,int b)
{
    //υλοποιησει με DIJKSTRA
     if(existnode(a)==false || existnode(b)==false)
     {
         return -1;
         //αν κανενα απο τουσ κομβους δεν υπραχει τοτε -1
     }
     else
     {
         //αλλιως ειναι ο αλγοριθμος ειναι παρομοιως με το prim
       node *ptr2;
       int *NODESKEY2;
       NODESKEY2= new int [nodes];//κραταμε τους κομβοθσ σενα πινακα
       ptr2=start;
       while(ptr2!=NULL)
       {
           for(int i=0;i<nodes;i++)
            {
                NODESKEY2[i]=ptr2->key;
                ptr2=ptr2->next;
            }
        }
      int d[nodes];// πινακα για να κραταμε το κοστο για να παμε απο α στο καθε κομβου
      bool color[nodes];//αν εχουμε περασει απο αυτο τον κομβο
      bool color2[nodes];
      int pred[nodes];//κραταμε το προηγουμενο αυτου του κομβου

      for (int i = 0; i < nodes; i++)
        {
            d[i] = INT_MAX;//intiliaze
            color[i] = false;
            color2[i]=false;
            pred[i]=INT_MAX;
        }
     int src;
     for(int i=0;i<nodes;i++)
     {
         if(NODESKEY2[i]==a)
            {src=i;}//
     }
     d[src] = 0;
     pred[src]=-1;
     //βρισκουμε την θεση του κομβου με τιμη a


     MINHEAP Q;
     for(int i=0;i<nodes;i++)
     {
         Q.INSERT(d[i]);
     }
     //insert ολα τα d[i] στο minheap για να μας επιστρεφει το ελαχιστο κοστο καθε φορα
     int index;
     int index2;
     int p=0;
     while(Q.GETSIZE()!=0)
     {
         //μεχρι που ο σωρος να αδιασει
         int x=Q.FINDMIN();
         Q.DELETEMIN();
         //περνουμε το ελαχιστο κοστος
         for(int i=0;i<nodes;i++)
         {
             if(x==d[i] && color2[i]==false)
                {
                    index=i;
                    color2[i]=true;
                    break;
                }
         }
         //βρισκουμε το index του ελαχιστου κοστου αρα το κομβο
         int u=NODESKEY2[index];
         node *locu;
         locu=Find(u);
         edge *o;
         o=locu->adj;
         //και για καθε γειτονα αυτου
         //ελενχουμε
         while(o!=NULL)
         {

             for(int k=0;k<nodes;k++)
             {
                 if(NODESKEY2[k]==o->dest)
                    {index2=k;}
              }
              //αν το κοστο του γειτονα ειναι μεγαλυτεο του προηγουμενου +1 γιατι ο γραφος μας ειναι με βαρη 1 μονο
              if(d[index]+1 < d[index2])
                 {
                   p=p+1;
                   d[index2]=d[index]+1;
                   Q.DECREASEKEY(Q.GETSIZE()-p,d[index2]);
                   pred[index2]=u;
                 }
                 //αν ναι κανουμε update το κοστος του γειτονα και decrease αυτο το κοστο στο miheap
             o=o->link;
         }
         color[index]=true;
         p=0;
     }
     int indexb;
     int h=-2147483647;
     int g=-2147483648;
     for(int i=0;i<nodes;i++)
     {
         if(NODESKEY2[i]==b)
            indexb=i;
     }
     //βρισκουμε το index του b που θελουμε να βρουμε το κοστος
     if(d[indexb]!=INT_MAX && d[indexb]!=g && d[indexb]!=h)
         {
             return d[indexb];
         }
         //και επιστρεφουμε το d[indexb] για να μα; δειχνει το κοστος απο το α στο b
     else
        return -1;
}
}

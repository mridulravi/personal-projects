#include <iostream>
#include <cstdlib>
using namespace std;
enum{FALSE=0,TRUE=-1};

/////////////////////////////////
///// Implements Priority Queue
/////////////////////////////////

class PriorityQueue  // Class Prioriry Queue
{
private:
    struct Node   // Node of Priority Queue
    {
        struct Node *Previous;
        int Data;
        struct Node *Next;
    }Current;
    struct Node *head;  // Pointer to Head
    struct Node *ptr;   
        // Pointer for travelling through Queue
    static int NumOfNodes;
        // Keeps track of Number of nodes
public:
    PriorityQueue(void);
    int Maximum(void);
    int Minimum(void);
    void Insert(int);
    int Delete(int);
    void Display(void);
    int Search (int);
    ~PriorityQueue(void);
};
// First Nodes Created With Constructor
int PriorityQueue::NumOfNodes=1;
// Constructor
PriorityQueue::PriorityQueue(void)
{
    Current.Previous=NULL;
    std::cout<<"Enter First Element of Queue"<<std::endl;
    std::cin>>Current.Data;
    Current.Next=NULL;
    head=&Current;
    ptr=head;
}
// Function Finding Maximum Priority Element
int PriorityQueue::Maximum(void)
{
    int Temp;
    ptr=head;
    Temp=ptr->Data;

    while(ptr->Next!=NULL)
    {
        if(ptr->Data>Temp)
            Temp=ptr->Data;
        ptr=ptr->Next;
    }
    if(ptr->Next==NULL && ptr->Data>Temp)
        Temp=ptr->Data;
    return(Temp);
}
// Function Finding Minimum Priority Element
int PriorityQueue::Minimum(void)
{
    int Temp;
    ptr=head;
    Temp=ptr->Data;

    while(ptr->Next!=NULL)
    {
        if(ptr->Data<Temp)
            Temp=ptr->Data;
        ptr=ptr->Next;
    }
    if(ptr->Next==NULL && ptr->Data<Temp)
        Temp=ptr->Data;
    return(Temp);
}
// Function inserting element in Priority Queue
void PriorityQueue::Insert(int DT)
{
    struct Node *newnode;
    
    newnode=new Node;

    newnode->Data=DT;

    while(ptr->Next!=NULL)
        ptr=ptr->Next;
    if(ptr->Next==NULL)
    {
        newnode->Next=ptr->Next;
        ptr->Next=newnode;
    }
    NumOfNodes++;
}
// Function deleting element in Priority Queue
int PriorityQueue::Delete(int DataDel)
{
    struct Node *mynode,*temp;

    ptr=head;
    
    if(NumOfNodes==1)
    {
        std::cout<<"Cannot Delete the only Node"<<std::endl;
        return FALSE;
    }
    if(ptr->Data==DataDel)
    {
        /***  Checking condition for deletion of first node  ***/
        temp=ptr;
        ptr=ptr->Next;
        ptr->Previous=NULL;
        //delete temp;
        head=ptr;
        NumOfNodes--;
        return(TRUE);
    }
    else
    {
        while(ptr->Next->Next!=NULL)
        {
            /***  Checking condition for deletion of   ***/
            /*** all nodes except first and last node  ***/
            if(ptr->Next->Data==DataDel)
            {
                mynode=ptr;
                temp=ptr->Next;
                mynode->Next=mynode->Next->Next;
                mynode->Next->Previous=ptr;
                delete temp;
                NumOfNodes--;
                return(TRUE);
            }
            ptr=ptr->Next;
        }
        if(ptr->Next->Next==NULL && ptr->Next->Data==DataDel)
        {
            /***  Checking condition for deletion of last node  ***/
            temp=ptr->Next;
            delete temp;
            ptr->Next=NULL;
            NumOfNodes--;
            return(TRUE);
        }
    }
    return(FALSE);
}
// Function Searching element in Priority Queue
int PriorityQueue::Search(int DataSearch)
{
    ptr=head;

    while(ptr->Next!=NULL)
    {
        if(ptr->Data==DataSearch)
            return ptr->Data;
        ptr=ptr->Next;
    }
    if(ptr->Next==NULL && ptr->Data==DataSearch)
        return ptr->Data;
    return(FALSE);
}
// Function Displaying elements of Priority Queue
void PriorityQueue::Display(void)
{
    ptr=head;
    std::cout<<"Priority Queue is as Follows:-"<<std::endl;
    while(ptr!=NULL)
    {
        std::cout<<ptr->Data<<std::endl;
        ptr=ptr->Next;
    }
}
// Destructor of Priority Queue
PriorityQueue::~PriorityQueue(void)
{
    struct Node *temp;                      /* Temporary variable */
    while(head->Next!=NULL)
    {
        temp=head->Next;
//    delete head;
        head=temp;
    }
    if(head->Next==NULL)
        delete head;
}
//Main Function
int main()
{
    PriorityQueue PQ;
    int choice;
    int DT;

    while(1)
    {
        std::cout<<"Enter your choice"<<std::endl;
        std::cout<<"1. Insert an element"<<std::endl;
        std::cout<<"2. Display a priorty Queue"<<std::endl;
        std::cout<<"3. Delete an element"<<std::endl;
        std::cout<<"4. Search an element"<<std::endl;
        std::cout<<"5. Exit"<<std::endl;
        std::cin>>choice;
        switch(choice)
        {
        case 1:
            std::cout<<"Enter a Data to enter Queue"<<std::endl;
            std::cin>>DT;
            PQ.Insert(DT);
            break;
        case 2:
            PQ.Display();
            break;
        case 3:
            {
                int choice;
                std::cout<<"Enter your choice"<<std::endl;
                std::cout<<"1. Maximum Priority Queue"<<std::endl;
                std::cout<<"2. Minimum Priority Queue"<<std::endl;
                std::cin>>choice;
                switch(choice)
                {
                case 1:
                    PQ.Delete(PQ.Maximum());
                    break;
                case 2:
                    PQ.Delete(PQ.Minimum());
                    break;
                default:
                    std::cout<<"Sorry Not a correct choice"<<std::endl;
                }
            }
            break;
        case 4:
            std::cout<<"Enter a Data to Search in Queue"<<std::endl;
            std::cin>>DT;
            if(PQ.Search(DT)!=FALSE)
                std::cout<<DT<<" Is present in Queue"<<std::endl;
            else
                std::cout<<DT<<" is Not present in Queue"<<std::endl;
            break;
        case 5:
            exit(0);
        default:
            std::cout<<"Cannot process your choice"<<std::endl;
        }
    }
return 0;
}

#include <list>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <QVector>

using namespace std;
//iitbOrderedSet class definition.The declared functions have been implemented below the class.

template <class valueType>
struct TreeNode 		// a TreeNode has pointers to left, right node, an integer key1 is key stored in node which is its
{				// key value and key2 indicates the key of its parent
	int key1;		// value1 is 1 if it is a left node of its parent
	int key2;		// and -1 if it is a right node of its parent, 0 for the root
	valueType value1;
	TreeNode *left;
	TreeNode *right;	
};

struct PAIR			
{	
	int first;		// stores the pos
	int second;		// stores the depth
	int third;		// stores whether right child or not(1 for right,-1 for left)
};

template <class valueType>
class iitbOrderedSet 
{
 private:
  TreeNode <valueType> *home;	
 public:
  QVector<int> myvector;
  iitbOrderedSet();
  bool isEmpty() const;					// returns true if empty
  
  QVector<int> print_inorder() ;			//print keys in order

  void inorder(TreeNode <valueType> *,int,int,int) ;
  int insert(int key); 					//returns depth of node inserted
  void remove(int key);					// remove the element which has key "key"
  
  PAIR isPresent(int key); 				//return true if present in the set
  PAIR findMin();					// finds the minimum element in the BST and return an object of PAIR
  PAIR findMax();					// finds the maximum element in the BST and return an object of PAIR 
  
};

template <class valueType>
iitbOrderedSet <valueType>::iitbOrderedSet()					// Default Constructor
{
	home = NULL;
}

template <class valueType>				
bool iitbOrderedSet <valueType>::isEmpty() const				// returns true if set is empty
{
	return (home == NULL);
}

template <class valueType>
QVector<int> iitbOrderedSet <valueType>::print_inorder() 			// print keys in order
{
	myvector.clear();
        iitbOrderedSet <valueType>::inorder(home,1,-1,0);
	cout<<endl;
	return myvector;
}

template <class valueType>
void iitbOrderedSet <valueType>::inorder(TreeNode <valueType> *ptr,int pos,int depth,int c ) 
{					// prints the elements inorder and assign them position and depth which would be useful in drawing
					// them ,pushing all the relevant information in a vector 
	if(ptr!=NULL)
	{
		pos--;depth++;
           	iitbOrderedSet <valueType>::inorder( ptr->left ,pos,depth,c);   
		myvector.push_back(pos);
		myvector.push_back(depth);
		myvector.push_back(ptr->key1);
		myvector.push_back(ptr->value1);
		myvector.push_back(ptr->key2);
		pos+=2;
           	iitbOrderedSet <valueType>::inorder( ptr->right,pos,depth,c);
		depth--;
	}
	
}


template <class valueType>
int iitbOrderedSet <valueType>::insert(int key)			// inserts a key with a value in the dictionary set
{
    TreeNode <valueType> *ptr2 = new TreeNode <valueType> ;	// finding the parentNode of node where key has to be to be inserted
    TreeNode <valueType> *parentNode;
    ptr2->key1 = key;
    ptr2->left = NULL;
    ptr2->right = NULL;
    parentNode = NULL;
    int count = 0;
    if(iitbOrderedSet <valueType>::isEmpty()) 
	{
	ptr2->key2 = 10000; 
	ptr2->value1 = 0;
	home = ptr2;
	}
    else
     {     
      TreeNode <valueType> *currentNode;			
      currentNode = home;
      
    while(currentNode)
    {
        parentNode = currentNode;
        if(ptr2->key1 > currentNode->key1) 
		{currentNode = currentNode->right;
		 count++;
		}
        else 
		{currentNode = currentNode->left;
		 count++;
		}
    }

    if(ptr2->key1 < parentNode->key1)
       	{
	ptr2->value1=-1;
	ptr2->key2=parentNode->key1;
	parentNode->left = ptr2;	
	}
    else
	{
	ptr2->value1=1;
	ptr2->key2=parentNode->key1;
       	parentNode->right = ptr2;
	}
  }
	
	return count;
}

template <class valueType>
void iitbOrderedSet <valueType>::remove(int key)			  //remove a key from the set
{
    bool found = false;
    if(iitbOrderedSet <valueType>::isEmpty())				  // if empty then return
    {
        return;
    }
    TreeNode <valueType> *currentNode;
    TreeNode <valueType> *parentNode;
    currentNode = home;
    parentNode = NULL;
    while(currentNode != NULL)
    {
         if(currentNode->key1 == key)					// if element found then set found to true and break
         {
            found = true; 
            break;
         }
         else
         {
             parentNode = currentNode;
             if(key > currentNode->key1) 
		{currentNode = currentNode->right;}
             else 
		{currentNode = currentNode->left;}
         }
    }
    if(!found)								// if found is false(i.e. element not found) then return
    {
        return;								
    }


    // We have here 3 following cases cases :

    // Case 1 : if node to be deleted has only one child
    if((currentNode->left == NULL && currentNode->right != NULL) || (currentNode->left != NULL && currentNode->right == NULL))
    {
       if(currentNode->left == NULL && currentNode->right != NULL)			 // right child present, no left child
       {
	if (parentNode != NULL)						// if not root then
	{
           if(parentNode->left == currentNode)
           {
             parentNode->left = currentNode->right;
	     (parentNode->left)->value1=-1;
	     (parentNode->left)->key2=parentNode->key1;
             delete currentNode;
           }
           else
           {
             parentNode->right = currentNode->right;
	     (parentNode->right)->value1=1;
	     (parentNode->right)->key2=parentNode->key1;
             delete currentNode;
           }
	}
	else								// if root then
	{
		home = currentNode->right;
		home->key2 = 10000;
		home->value1= 0;
		
	}
       }
       else 							      			  // left child present, no right child
       {
	 if (parentNode != NULL)					// if not root then
	{
          if(parentNode->left == currentNode)
           {
             parentNode->left = currentNode->left;
	     (parentNode->left)->value1=-1;
	     (parentNode->left)->key2=parentNode->key1;
             delete currentNode;
           }
           else
           {
             parentNode->right = currentNode->left;
	     (parentNode->right)->value1=1;
	     (parentNode->right)->key2=parentNode->key1;
             delete currentNode;
           }
	}
	 else								// if root then
	{
		home = currentNode->left;
		home->key2 = 10000;
		home->value1= 0;
	}
	
	
       }
     return;
    }

    // Case 2 : if node to be deleted has no child
    if( currentNode->left == NULL && currentNode->right == NULL)
    {
	if(parentNode!=NULL){						// if not root then
	        if(parentNode->left == currentNode) 
		{parentNode->left = NULL;}
        	else 
		{parentNode->right = NULL;}
		delete currentNode;
		return;
	}
	else{								// if root then
		home=NULL;
	}	
    }


    // Case 3 : if node to be deleted has two children
    									// replace node with smallest value in right subtree
    if (currentNode->left != NULL && currentNode->right != NULL)
    {
        TreeNode <valueType> *ptr1;					// ptr1 is the right child of currentNode node
        ptr1 = currentNode->right;
        if((ptr1->left == NULL) && (ptr1->right == NULL)) 		// if right child of current node has no children
        {
            currentNode->key1 = ptr1->key1;
	    (currentNode->left)->key2 = currentNode->key1;
            delete ptr1;
            currentNode->right = NULL;
        }
        else 								// right child has children
        {
            								// if the node's right child has a left child
            								// Move all the way down left to locate smallest element

            if((currentNode->right)->left != NULL)
            {
                TreeNode <valueType> *lcurr;
                TreeNode <valueType> *lcurrp;
                lcurrp = currentNode->right;
                lcurr = (currentNode->right)->left;
                while(lcurr->left != NULL)
                {
                   lcurrp = lcurr;
                   lcurr = lcurr->left;
                }
		currentNode->key1 = lcurr->key1;
		(currentNode->right)->key2 = currentNode->key1;
		if (currentNode->left != NULL) 
			(currentNode->left)->key2 = currentNode->key1;
                delete lcurr;
                lcurrp->left = NULL;
           }
	   								// if the node's right child has a right child
          							        // we have to find the largest element in right subtree
           else				
           {
               TreeNode <valueType> *tmp;
               tmp = currentNode->right;
               currentNode->key1 = tmp->key1;
	       currentNode->right = tmp->right;
	       (currentNode->left)->key2=currentNode->key1;
               delete tmp;
           }

        }
		 return;
    }

}

template <class valueType>
PAIR iitbOrderedSet <valueType>::isPresent(int key)			//return true if key present in the set
{
    int u=0;
    int v=0;
    int w=0;
    PAIR *p = new PAIR;
    bool keyfound = false;
  
    TreeNode <valueType> *currentNode;
    currentNode = home;
    while(currentNode != NULL)
    {
         if(currentNode->key1 == key)					// if element found then set found to true and break
         {
            keyfound = true;
            break;
         }
         else
         {
             if(key > currentNode->key1)
		 { currentNode = currentNode->right;
		   u++;
		   v++;
		   w=1;
		 }
             else
		 { currentNode = currentNode->left;
		   u--;
		   v++;
		   w=-1;
		 }
         }
    }
    if(keyfound)				// if element is found then assign the data to the PAIR object and return the object
	{
	 p->first = u;
	 p->second = v;
	 p->third = w;
	 return *p;
	}
   else {
	 p->first = -2;		// else return junk data so that the case would be removed while comparison(in other functions) 
	 p->second = -2;
	 p->third = -2;
	 return *p;
        }

}

template <class valueType>
PAIR iitbOrderedSet <valueType>::findMin()
{
	int u=0;	
	int v=0;
	int w=0;
	PAIR *p = new PAIR;
	TreeNode <valueType> *ptr = home;
	while (ptr->left)		// the leftmost element of the left subtree is the smallest element
	{				// finding that and returning a PAIR object containing the required data
	 	u--;
		v++;
		ptr=ptr->left;	 
		w=-1;
	}
	 p->first = u;
	 p->second = v;
	 p->third = w;
	 return *p;
}

template <class valueType>
PAIR iitbOrderedSet <valueType>::findMax()
{
	int u=0;	
	int v=0;
	int w=0;
	PAIR *p = new PAIR;
	TreeNode <valueType> *ptr = home;
	while (ptr->right)		// the rightmost element of the right subtree is the maximum element
	{				// finding that and returning a PAIR object containing the required data
	 	u++;
		v++;
		w=1;
		ptr=ptr->right;	 
	}
	 p->first = u;
	 p->second = v;
	 p->third = w;
	 return *p;
}


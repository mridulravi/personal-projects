#include <iostream>
#include <vector>
#include <cstdlib>
#define Nmax 50
//#include <Event.h>
using namespace std;

template <typename Comparable>

class BinaryHeap
{
  public: 
	explicit BinaryHeap ( int capacity = 100 );
	explicit BinaryHeap ( const vector<Comparable> & indices);
	
	bool isEmpty() const;
	const Comparable & findmin() const;

	const Comparable & insert(const Comparable & x);
	void deleteMin();
	
	void makeEmpty();
	bool isEmpty();
	void display();
	bool contains(int k);
	void displaypos();
  private:
	int currentSize;
	vector<Comparable> array;
	int position[Nmax];
	void buildHeap();
	void percolateDown ( int hole);
};


template <typename Comparable>
const Comparable & BinaryHeap<Comparable>::insert(const Comparable & x)
{	
	if(currentSize == array.size() - 1)
		array.resize(array.size()*2);
	
	int hole = ++currentSize;
	
	
	position[x]=hole;
	for(;hole >1 && x < array[hole/2]; hole/=2)
		{array[hole]=array[hole/2];position[array[hole]]=hole;}
	array[hole] = x;
	position[array[hole]]=hole;
	return x;
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
	if (isEmpty())
	     exit(1);
	
	position[array[currentSize]]=position[array[1]];
	position[array[1]]=-1;
	
	array[1] = array[currentSize--];

	if (currentSize>=1)
	BinaryHeap::percolateDown(1);

}



template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown (int hole)
{
	int child;
	Comparable tmp = array [hole];
	int tmppos = position[array[hole]];
	
	for (; hole*2 <= currentSize; hole = child)
	{
		child = hole*2;
		if (child != currentSize && array [child+1] <array[child])
			child++;
		if (array[child] < tmp)
			{array[hole]=array[child];
			 position[array[hole]]=hole;}
		else
			break;
	}
	array [hole] = tmp;
	position[array[hole]]=hole;
	
}


template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap (const vector<Comparable> & indices)
   : array(indices.size() + 10), currentSize ( indices.size())
{	
	for (int i = 0; i < indices.size(); i++)
		array[i+1] = indices [i];
	BinaryHeap::buildHeap(); 
	for (int j=0;j<Nmax;j++)
		position[j] = -1;
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{	
	for ( int j=currentSize/2 ; j>0 ; j--)
		BinaryHeap::percolateDown(j);
}

template <typename Comparable>
bool BinaryHeap<Comparable>::isEmpty()
{
	if (currentSize == 0)
		return true;
	else
		return false; 
}


template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap (int t)
{
	
}


template <typename Comparable>
void BinaryHeap<Comparable>::display ()
{
	for (int k = 1; k <= currentSize; k++)
		cout<<array[k]<<"  ";
}


template <typename Comparable>
const Comparable & BinaryHeap<Comparable>::findmin() const
{	

		return array[1];
}


template <typename Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
	array.clear();
	currentSize=0;
	for (int j=0;j<Nmax;j++)
		position[j] = -1;
}


template <typename Comparable>
bool BinaryHeap<Comparable>::contains(int k)
{ return position[k] != -1; }


template <typename Comparable>
void BinaryHeap<Comparable>::displaypos()
{  
	for (int j=0;j<Nmax;j++)
		cout<<j<<"=  "<<position[j]<<endl;

}

#include "trie.h"
#include <iostream>
#include <cstdlib>
#include <string>
trie::trie()			
{
	TreeNode *InitialPtr = new TreeNode;
	InitialPtr->flag = false;
	InitialPtr->aPtr = NULL;
	InitialPtr->bPtr = NULL;
	InitialPtr->cPtr = NULL;
	InitialPtr->dPtr = NULL;
	InitialPtr->ePtr = NULL;
	InitialPtr->fPtr = NULL;
	InitialPtr->gPtr = NULL;
	InitialPtr->hPtr = NULL;
	InitialPtr->iPtr = NULL;
	InitialPtr->jPtr = NULL;
	InitialPtr->kPtr = NULL;
	InitialPtr->lPtr = NULL;
	InitialPtr->mPtr = NULL;
	InitialPtr->nPtr = NULL;
	InitialPtr->oPtr = NULL;
	InitialPtr->pPtr = NULL;
	InitialPtr->qPtr = NULL;
	InitialPtr->rPtr = NULL;
	InitialPtr->sPtr = NULL;
	InitialPtr->tPtr = NULL;
	InitialPtr->uPtr = NULL;
	InitialPtr->vPtr = NULL;
	InitialPtr->wPtr = NULL;
	InitialPtr->xPtr = NULL;
	InitialPtr->yPtr = NULL;
	InitialPtr->zPtr = NULL;
	home = InitialPtr;
}

TreeNode& trie::root()	
{
	return *home;
}

TreeNode* trie::insert(TreeNode *tmpPtr,char e)
{
	if      (e=='a' || e=='A')	
		return setNULL(tmpPtr,tmpPtr->aPtr,e);
	else if (e=='b' || e=='B')
		return setNULL(tmpPtr,tmpPtr->bPtr,e);
	else if (e=='c' || e=='C')
		return setNULL(tmpPtr,tmpPtr->cPtr,e);
	else if (e=='d' || e=='D')
		return setNULL(tmpPtr,tmpPtr->dPtr,e);
	else if (e=='e' || e=='E')	
		return setNULL(tmpPtr,tmpPtr->ePtr,e);	
	else if (e=='f' || e=='F')	
		return setNULL(tmpPtr,tmpPtr->fPtr,e);	
	else if (e=='g' || e=='G')	
		return setNULL(tmpPtr,tmpPtr->gPtr,e);
	else if (e=='h' || e=='H')
		return setNULL(tmpPtr,tmpPtr->hPtr,e);
	else if (e=='i' || e=='I')
		return setNULL(tmpPtr,tmpPtr->iPtr,e);
	else if (e=='j' || e=='J')
		return setNULL(tmpPtr,tmpPtr->jPtr,e);
	else if (e=='k' || e=='K')	
		return setNULL(tmpPtr,tmpPtr->kPtr,e);
	else if (e=='l' || e=='L')	
		return setNULL(tmpPtr,tmpPtr->lPtr,e);
	else if (e=='m' || e=='M')	
		return setNULL(tmpPtr,tmpPtr->mPtr,e);	
	else if (e=='n' || e=='N')
		return setNULL(tmpPtr,tmpPtr->nPtr,e);
	else if (e=='o'|| e=='O')	
		return setNULL(tmpPtr,tmpPtr->oPtr,e);
	else if (e=='p'|| e=='P')	
		return setNULL(tmpPtr,tmpPtr->pPtr,e);	
	else if (e=='q'|| e=='Q')
		return setNULL(tmpPtr,tmpPtr->qPtr,e);	
	else if (e=='r'|| e=='R')	
		return setNULL(tmpPtr,tmpPtr->rPtr,e);	
	else if (e=='s'|| e=='S')	
		return setNULL(tmpPtr,tmpPtr->sPtr,e);
	else if (e=='t' || e=='T')	
		return setNULL(tmpPtr,tmpPtr->tPtr,e);
	else if (e=='u' || e=='U')	
		return setNULL(tmpPtr,tmpPtr->uPtr,e);
	else if (e=='v' || e=='V')	
		return setNULL(tmpPtr,tmpPtr->vPtr,e);	
	else if (e=='w' || e=='W')
		return setNULL(tmpPtr,tmpPtr->wPtr,e);
	else if (e=='x' || e=='X')
		return setNULL(tmpPtr,tmpPtr->xPtr,e);
	else if (e=='y' || e=='Y')
		return setNULL(tmpPtr,tmpPtr->yPtr,e);
	else if (e=='z' || e=='Z')
		return setNULL(tmpPtr,tmpPtr->zPtr,e);
	else
		return home;
}

TreeNode* trie::searchFor(TreeNode *srchPtr,char q)
{
	if (q == 'a' || q == 'A')			
		return setSearch(srchPtr,srchPtr->aPtr);	
	else if (q == 'b' || q == 'B')	
		return setSearch(srchPtr,srchPtr->bPtr);
	else if (q == 'c' || q == 'C')
		return setSearch(srchPtr,srchPtr->cPtr);
	else if (q == 'd' || q == 'D')
		return setSearch(srchPtr,srchPtr->dPtr);
	else if (q == 'e' || q == 'E')
		return setSearch(srchPtr,srchPtr->ePtr);
	else if (q == 'f' || q == 'F')
		return setSearch(srchPtr,srchPtr->fPtr);
	else if (q == 'g' || q == 'G')
		return setSearch(srchPtr,srchPtr->gPtr);
	else if (q == 'h' || q == 'H')
		return setSearch(srchPtr,srchPtr->hPtr);
	else if (q == 'i' || q == 'I')
		return setSearch(srchPtr,srchPtr->iPtr);
	else if (q == 'j' || q == 'J')
		return setSearch(srchPtr,srchPtr->jPtr);
	else if (q == 'k' || q == 'K')
		return setSearch(srchPtr,srchPtr->kPtr);
	else if (q == 'l' || q == 'L')
		return setSearch(srchPtr,srchPtr->lPtr);
	else if (q == 'm' || q == 'M')
		return setSearch(srchPtr,srchPtr->mPtr);
	else if (q == 'n' || q == 'N')
		return setSearch(srchPtr,srchPtr->nPtr);
	else if (q == 'o' || q == 'O')
		return setSearch(srchPtr,srchPtr->oPtr);
	else if (q == 'p' || q == 'P')
		return setSearch(srchPtr,srchPtr->pPtr);
	else if (q == 'q' || q == 'Q')
		return setSearch(srchPtr,srchPtr->qPtr);
	else if (q == 'r' || q == 'R')
		return setSearch(srchPtr,srchPtr->rPtr);
	else if (q == 's' || q == 'S')
		return setSearch(srchPtr,srchPtr->sPtr);
	else if (q == 't' || q == 'T')
		return setSearch(srchPtr,srchPtr->tPtr);
	else if (q == 'u' || q == 'U')
		return setSearch(srchPtr,srchPtr->uPtr);
	else if (q == 'v' || q == 'V')
		return setSearch(srchPtr,srchPtr->vPtr);
	else if (q == 'w' || q == 'W')
		return setSearch(srchPtr,srchPtr->wPtr);
	else if (q == 'x' || q == 'X')
		return setSearch(srchPtr,srchPtr->xPtr);
	else if (q == 'y' || q == 'Y')
		return setSearch(srchPtr,srchPtr->yPtr);
	else if (q == 'z' || q == 'Z')
		return setSearch(srchPtr,srchPtr->zPtr);
	else 
		return NULL;
}

void trie::preorder(std::string enterdStr, TreeNode *PrePtr)
{
	std::string tmpStr = enterdStr;
	tmpStr.append(1,PrePtr->element);
	if (PrePtr->flag == true)
		std::cout << tmpStr<< std::endl;
	if (PrePtr->aPtr != NULL)
		preorder  (tmpStr, PrePtr->aPtr);
	if (PrePtr->bPtr != NULL)
		preorder  (tmpStr, PrePtr->bPtr);
	if (PrePtr->cPtr != NULL)
		preorder  (tmpStr, PrePtr->cPtr);
	if (PrePtr->dPtr != NULL)
		preorder  (tmpStr, PrePtr->dPtr);
	if (PrePtr->ePtr != NULL)
		preorder  (tmpStr, PrePtr->ePtr);
	if (PrePtr->fPtr != NULL)
		preorder  (tmpStr, PrePtr->fPtr);
	if (PrePtr->gPtr != NULL)
		preorder  (tmpStr, PrePtr->gPtr);
	if (PrePtr->hPtr != NULL)
		preorder  (tmpStr, PrePtr->hPtr);
	if (PrePtr->iPtr != NULL)
		preorder  (tmpStr, PrePtr->iPtr);
	if (PrePtr->jPtr != NULL)
		preorder  (tmpStr, PrePtr->jPtr);
	if (PrePtr->kPtr != NULL)
		preorder  (tmpStr, PrePtr->kPtr);
	if (PrePtr->lPtr != NULL)
		preorder  (tmpStr, PrePtr->lPtr);
	if (PrePtr->mPtr != NULL)
		preorder  (tmpStr, PrePtr->mPtr);
	if (PrePtr->nPtr != NULL)
		preorder  (tmpStr, PrePtr->nPtr);
	if (PrePtr->oPtr != NULL)
		preorder  (tmpStr, PrePtr->oPtr);
	if (PrePtr->pPtr != NULL)
		preorder  (tmpStr, PrePtr->pPtr);
	if (PrePtr->qPtr != NULL)
		preorder  (tmpStr, PrePtr->qPtr);
	if (PrePtr->rPtr != NULL)
		preorder  (tmpStr, PrePtr->rPtr);
	if (PrePtr->sPtr != NULL)
		preorder  (tmpStr, PrePtr->sPtr);
	if (PrePtr->tPtr != NULL)
		preorder  (tmpStr, PrePtr->tPtr);
	if (PrePtr->uPtr != NULL)
		preorder  (tmpStr, PrePtr->uPtr);
	if (PrePtr->vPtr != NULL)
		preorder  (tmpStr, PrePtr->vPtr);
	if (PrePtr->wPtr != NULL)
		preorder  (tmpStr, PrePtr->wPtr);
	if (PrePtr->xPtr != NULL)
		preorder  (tmpStr, PrePtr->xPtr);
	if (PrePtr->yPtr != NULL)
		preorder  (tmpStr, PrePtr->yPtr);
	if (PrePtr->zPtr != NULL)
		preorder  (tmpStr, PrePtr->zPtr);
}

// setNULL is a function which based on the charecter to be inserted takes as arguments
// the current pointer, its corresponding children node, and element to be inserted
TreeNode* trie::setNULL(TreeNode *ToBeSet, TreeNode *elePtr, char ele)
{
		if (elePtr == NULL)			   // if current node does not have a child with element to be inserted
		{	TreeNode *nodePtr = new TreeNode;  // create a new node, put element into it and make it a child of currentnode
			nodePtr->element = ele;
	                nodePtr->aPtr = NULL;
	                nodePtr->bPtr = NULL;
	                nodePtr->cPtr = NULL;
	                nodePtr->dPtr = NULL;
	                nodePtr->ePtr = NULL;
	                nodePtr->fPtr = NULL;
	                nodePtr->gPtr = NULL;
	                nodePtr->hPtr = NULL;
	                nodePtr->iPtr = NULL;
	                nodePtr->jPtr = NULL;
	                nodePtr->kPtr = NULL;
	                nodePtr->lPtr = NULL;
	                nodePtr->mPtr = NULL;
	                nodePtr->nPtr = NULL;
	                nodePtr->oPtr = NULL;
	                nodePtr->pPtr = NULL;
	                nodePtr->qPtr = NULL;
	                nodePtr->rPtr = NULL;
	                nodePtr->sPtr = NULL;
	                nodePtr->tPtr = NULL;
	                nodePtr->uPtr = NULL;
	                nodePtr->vPtr = NULL;
	                nodePtr->wPtr = NULL;
	                nodePtr->xPtr = NULL;
	                nodePtr->yPtr = NULL;
	                nodePtr->zPtr = NULL;		
			if (tolower(ele) == 'a') ToBeSet->aPtr=nodePtr;
			if (tolower(ele) == 'b') ToBeSet->bPtr=nodePtr;
			if (tolower(ele) == 'c') ToBeSet->cPtr=nodePtr;
			if (tolower(ele) == 'd') ToBeSet->dPtr=nodePtr;
			if (tolower(ele) == 'e') ToBeSet->ePtr=nodePtr;
			if (tolower(ele) == 'f') ToBeSet->fPtr=nodePtr;
			if (tolower(ele) == 'g') ToBeSet->gPtr=nodePtr;
			if (tolower(ele) == 'h') ToBeSet->hPtr=nodePtr;
			if (tolower(ele) == 'i') ToBeSet->iPtr=nodePtr;
			if (tolower(ele) == 'j') ToBeSet->jPtr=nodePtr;
			if (tolower(ele) == 'k') ToBeSet->kPtr=nodePtr;
			if (tolower(ele) == 'l') ToBeSet->lPtr=nodePtr;
			if (tolower(ele) == 'm') ToBeSet->mPtr=nodePtr;
			if (tolower(ele) == 'n') ToBeSet->nPtr=nodePtr;
			if (tolower(ele) == 'o') ToBeSet->oPtr=nodePtr;
			if (tolower(ele) == 'p') ToBeSet->pPtr=nodePtr;
			if (tolower(ele) == 'q') ToBeSet->qPtr=nodePtr;
			if (tolower(ele) == 'r') ToBeSet->rPtr=nodePtr;
			if (tolower(ele) == 's') ToBeSet->sPtr=nodePtr;
			if (tolower(ele) == 't') ToBeSet->tPtr=nodePtr;
			if (tolower(ele) == 'u') ToBeSet->uPtr=nodePtr;
			if (tolower(ele) == 'v') ToBeSet->vPtr=nodePtr;
			if (tolower(ele) == 'w') ToBeSet->wPtr=nodePtr;
			if (tolower(ele) == 'x') ToBeSet->xPtr=nodePtr;
			if (tolower(ele) == 'y') ToBeSet->yPtr=nodePtr;
			if (tolower(ele) == 'z') ToBeSet->zPtr=nodePtr;
			ToBeSet=nodePtr;
			return ToBeSet;				// return a reference to the newly added node
		}
		else						// else no new node needs to be created
		{	if (tolower(ele) == 'a') ToBeSet=ToBeSet->aPtr;
			if (tolower(ele) == 'b') ToBeSet=ToBeSet->bPtr;
			if (tolower(ele) == 'c') ToBeSet=ToBeSet->cPtr;
			if (tolower(ele) == 'd') ToBeSet=ToBeSet->dPtr;
			if (tolower(ele) == 'e') ToBeSet=ToBeSet->ePtr;
			if (tolower(ele) == 'f') ToBeSet=ToBeSet->fPtr;
			if (tolower(ele) == 'g') ToBeSet=ToBeSet->gPtr;
			if (tolower(ele) == 'h') ToBeSet=ToBeSet->hPtr;
			if (tolower(ele) == 'i') ToBeSet=ToBeSet->iPtr;
			if (tolower(ele) == 'j') ToBeSet=ToBeSet->jPtr;
			if (tolower(ele) == 'k') ToBeSet=ToBeSet->kPtr;
			if (tolower(ele) == 'l') ToBeSet=ToBeSet->lPtr;
			if (tolower(ele) == 'm') ToBeSet=ToBeSet->mPtr;
			if (tolower(ele) == 'n') ToBeSet=ToBeSet->nPtr;
			if (tolower(ele) == 'o') ToBeSet=ToBeSet->oPtr;
			if (tolower(ele) == 'p') ToBeSet=ToBeSet->pPtr;
			if (tolower(ele) == 'q') ToBeSet=ToBeSet->qPtr;
			if (tolower(ele) == 'r') ToBeSet=ToBeSet->rPtr;
			if (tolower(ele) == 's') ToBeSet=ToBeSet->sPtr;
			if (tolower(ele) == 't') ToBeSet=ToBeSet->tPtr;
			if (tolower(ele) == 'u') ToBeSet=ToBeSet->uPtr;
			if (tolower(ele) == 'v') ToBeSet=ToBeSet->vPtr;
			if (tolower(ele) == 'w') ToBeSet=ToBeSet->wPtr;
			if (tolower(ele) == 'x') ToBeSet=ToBeSet->xPtr;
			if (tolower(ele) == 'y') ToBeSet=ToBeSet->yPtr;
			if (tolower(ele) == 'z') ToBeSet=ToBeSet->zPtr;
			return ToBeSet;
		}
}

// Based on the character to be searched and current positon of search pointer this function returns
// reference to searched node if it exists otherwise NULL
TreeNode* trie::setSearch(TreeNode *ToBeSearched,TreeNode *srchele)	
{
		if (srchele == NULL)
		{
			return NULL;
		}
		else
		{
			ToBeSearched=srchele;
			return ToBeSearched;
		}
}

#include "hilbert.hh"

vector<wff*> proof_vec;
vector<pair<int, int> > printing_vector;
vector<int> axiom2_indices; // stores indices of all rules obt by axiom2
vector<wff*> rhs_axiom2; // stores rhs gen by axiom 2 ( to ensure axiom2 not called on it again))

wff::wff(wff *a, wff *b, char c)
{
		lhs = a;
		rhs = b;
		val = c;
}

void wff::implement_dt()
{
	
	
	if(rhs==NULL)		//Will apply the f transformation using axiom 3
	{
		
		
		if(val!='f')
		{
			int itr=0;
			for(itr=0;itr<proof_vec.size();itr++)
			{
				proof_vec[itr]->print();
				cout<<",";
			}
			
			cout<<"(";
			print();
			cout<<"->f)";
		
			cout<<"\t Derives\t";
			cout<<"f\n";
			
			
			// push alphabet->f into vector
			wff* l = new wff(NULL,NULL,val);
			wff* r = new wff(NULL,NULL,'f');
			wff* new_node = new wff(l,r,val);
			proof_vec.push_back(new_node);
			printing_vector.push_back(make_pair(-1, -1) );
			
		}
			
			
			////////////////////////////////////////
			cout<<endl<<endl;
			// first print all existing values in vector, these are the hypotheses			
			for(int i = 0; i<proof_vec.size(); i++)
			{
				cout<<"L" << i <<": ";
				proof_vec[i]->print();
				cout<< "\t\t hypothesis"<<endl;
				if(proof_vec[i]->lhs==NULL && proof_vec[i]->val=='f')
				{
					cout<<"Hence proved using hypothesis " << i <<endl;
					exit(0); 
				}
			}
			

			// call function which will look for modus ponens, axioms etc....
			int count = 0;
			int temp_count = 0;
			//int num_consecutive_axiom2 = 0;
			while(true)
			{
				if(count > 500)
				{
					cout<< "This is most probably not a theorem\n";
					exit(1);
				}
				
				if(temp_count>=20)
				{
					// ask for human help
					cout << "\n\nJust verify that proof is on right track, if not then give help, otherwise enter 8";
					ask_human_help();				
					temp_count = 0;
				}
				
				/*if(num_consecutive_axiom2 > 5)
				{
					//human help
					ask_human_help();
					num_consecutive_axiom2 = 0;
					continue;
				}*/
				
				check_if_proved();
				pair<int, int> res = check_modus_ponens();
				// first is index of the "bigger" with which we can apply modus ponens
				int first = res.first;
				int second = res.second;
				if(first >= 0)
				{
					// can apply modus ponens again
					//num_consecutive_axiom2 = 0;
					wff* match1 = proof_vec[first];
					wff* match2 = proof_vec[second];
					apply_modus_ponens(match1,match2,first,second);
				}
				else
				{
					//ask_human_help();
					// axioms
					bool flag1 = try_axiom1_1();
					
					if(!flag1)
					{
//						cout << "break1.0\n";
						bool flag1_2 = try_axiom1_2();
						if(flag1_2)
						{
							count++;
							temp_count++;
							continue;
						}
//						cout << "break1.1\n";
						bool flag2 = try_axiom2();
						if(!flag2)
						{
							//num_consecutive_axiom2 = 0;
							bool flag3 = try_axiom3();
							if(!flag3)
							{
								if(!try_axiom3_2() )
								{
									// human help
									
									bool flag4 = try_brute_force();
//									if(flag4)
//									{
//										count++;
//										temp_count++;
//										continue;
//									}
									ask_human_help();
									//continue;
								}
							}
						}
						/*else
						{
							num_consecutive_axiom2++ ;
						}*/
					}
					
					/*else
					{
						num_consecutive_axiom2 = 0;
					}*/
				}
				count++;	
				temp_count++;
			} 
			
			///////////////////////////////////////
		
		
		
	}
	else
	{
		int itr=0;
		for(itr=0;itr<proof_vec.size();itr++)
		{
			proof_vec[itr]->print();
			cout<<", ";
		}
		
		//print LHS
		lhs->print();
		cout<<"\t Derives\t";
		rhs->print();
		cout<<endl;
		proof_vec.push_back(lhs);
		printing_vector.push_back(make_pair(-1, -1) );
		rhs->implement_dt();
	}
}

void wff::print()
{
	if(rhs==NULL)
	{
		cout<<val;
		return;
	}

	cout<<"(";
	lhs->print();
	cout<<"->";		
	rhs->print();
	cout<<")";
	return;
}

///////////////////////////////////////////////////////////////

void apply_modus_ponens(wff* a, wff* b,int i1,int i2)
{
	// assume that b = a.lhs , so we need to add a.rhs to the vector
	proof_vec.push_back(a->rhs);
	printing_vector.push_back(make_pair(i1, i2) );
	print_modus_ponens(i1,i2);
	//check_if_proved(); //checks if we are done
	
	//assume that if we can apply modus ponens, it is always good
	/*pair<int, int> res = check_modus_ponens(); // first is index of the "bigger" with which we can apply modus ponens
	int first = res.first;
	int second = res.second;
	if(first >= 0)
	{
		// can apply modus ponens again
		wff* match1 = proof_vec[first];
		wff* match2 = proof_vec[second];
		apply_modus_ponens(match1,match2,first,second);
	}
	else{
		// axioms
	}*/
}

////////////////////////////////////////////////////////////////
void print_entire_proof()
{
	// Now use the printing_vector to find the list of statements actually used, and then print only the useful statements

//	cout << printing_vector.size() << "				" << proof_vec.size() << endl;

	vector<bool> check_vector(printing_vector.size(), false);

	check_vector[printing_vector.size() - 1] = true;

	for(int i = printing_vector.size()-1;i>=0;i--)
	{
		if(check_vector[i])
		{
			int t1 = printing_vector[i].first;
			int t2 = printing_vector[i].second;
			if(t1!=-1)
			{
				check_vector[t1] = true;	
			}
			if(t2 != -1)
			{
				check_vector[t2] = true;
			}
		}
	}
	
	cout << "\n\n***********************************************************************************\n\n";
	cout << " The entire proof is \n";
	int count = 0;
	for(int i =0;i<proof_vec.size();i++)
	{
		if(check_vector[i])
		{
			cout << "L" << count << ":\t";
			proof_vec[i]->print();
			cout << "\t\t\t\t\t(L" << i <<" in proof with reasons)";
			cout << endl;
			count++;
		}
	}
	cout << "\n\n***********************************************************************************\n\n";
}
//////////////////////////////////////////////////////////////////

void check_if_proved()
{
	wff* last = proof_vec[proof_vec.size()-1];
	if(last->rhs==NULL && last->val == 'f')
	{
		// print the whole proof
		
		// write a function which will write the proof of the whole vector

		print_entire_proof();		
				
		cout<<"Hence proved"<<endl;
		exit(0);
	}
}

////////////////////////////////////////////////////////////////

void print_modus_ponens(int i1,int i2)
{
	// assume that the new thing to be printed is at end of vector
	wff* new_deduction = proof_vec[proof_vec.size()-1];
	cout<<"L" <<proof_vec.size()-1 <<": ";
	new_deduction->print();
	cout<<"\t\t by modus ponens between lines " << i1 <<" and " << i2 <<endl; 
}

//////////////////////////////////////////////////////////////

pair<int,int> check_modus_ponens()
{
	for(int i = 0; i<proof_vec.size(); i++ )
	{
		for(int j = 0; j<proof_vec.size(); j++ )
		{
			if(i != j)
			{
				if(wff_equals(proof_vec[i]->lhs, proof_vec[j]))
				{
					if(!is_in_vector(proof_vec[i]->rhs)){
						pair<int,int> p;
						p.first = i;
						p.second = j;
						return p;
					}
				}
			}
			
		}
	}
	pair<int,int> p;
	p.first = -1;
	p.second = -1;
	return p;
}

///////////////////////////////////////////////////////////////

bool wff_equals(wff* a, wff* b)
{
	if(a==NULL || b==NULL)
		return false;
	
	if(a->rhs == NULL && b->rhs != NULL)
		return false;
	if(b->rhs == NULL && a->rhs != NULL)
		return false;	
	
	if(a->rhs == NULL && b->rhs ==NULL && a->val == b->val)
		return true;
	if(a->rhs != NULL && b->rhs != NULL && wff_equals(a->lhs, b->lhs) && wff_equals(a->rhs, b->rhs))
		return true;	
		
	return false;	
}

//////////////////////////////////////////////////////////////

bool is_in_vector(wff * a) 
{ 
	vector<wff *>::iterator itr; 
	for(itr = proof_vec.begin(); itr!=proof_vec.end();itr++) 
	{ 
		if(wff_equals(a, (*itr))) 
		{ 
			return true; 
		} 
	} 
	return false; 
}
//////////////////////////////////////////////////////////////
	
bool try_axiom1_1()
{
	// search that whether any hypothesis(H1) is R.H.S of L.H.S. of any other hypothesis(H2), if so then apply axiom 1
	vector<wff *>::iterator itr1, itr2;
	int count1, count2;	
	
	
	for(itr1 = proof_vec.begin(), count1 = 0;itr1!=proof_vec.end();itr1++,count1++ )
	{
		// check whether it is RHS of LHS of any other hypothesis
		for(itr2 = proof_vec.begin(), count2=0; itr2 != proof_vec.end() ; itr2++,count2++)
		{
			if(itr2 != itr1)
			{
				if( (*itr2)->lhs != NULL)
				{
					if(wff_equals(*itr1, (*itr2)->lhs->rhs ) )
					{
						// apply axiom 1
						
						// A will be *itr1 and B will be (*itr2)->lhs->lhs
						
						wff * a = (*itr1);
						wff * b = (*itr2)->lhs->lhs;
						wff * c = new wff(b, a, 'A');
						wff * temp = new wff(a, c, 'A');
						
						// applying axiom 1
						if(!is_in_vector(temp))
						{
							proof_vec.push_back(temp);
							printing_vector.push_back(make_pair(-1, -1) );
							cout << "L" << proof_vec.size() - 1 << ": ";
							temp->print();
							cout<<"\t\t Applying Axiom1 with A as ";
							a->print();
							cout << " and B as ";
							b->print();
							cout<< endl;
							return true;
						}
					}				
				}
			}
		}
	}
	return false;
}

bool try_axiom1_2()
{
	// if the LHS of any hypothesis is of the form A->(B->A), then apply it
	for(int i = 0;i<proof_vec.size();i++)
	{
		bool check = false;
		wff *lhs =NULL, * lhs_lhs=NULL, *lhs_rhs=NULL, *lhs_rhs_lhs=NULL, *lhs_rhs_rhs=NULL;
		if(proof_vec[i]->lhs)			// i.e. not NULL
		{	
//			cout << "break2.0\n";
			lhs = proof_vec[i]->lhs;
			if(lhs->lhs)
			{
				lhs_lhs = lhs->lhs;						// lhs_lhs = a
//				cout << "break2.1\n";
			}
			if(lhs->rhs)
			{
				lhs_rhs = lhs->rhs;
				if(lhs_rhs->lhs)
				{
					lhs_rhs_lhs = lhs_rhs->lhs;			// lhs_rhs_lhs = b
//					cout << "break2.2\n";
				}
				if(lhs_rhs->rhs)
				{
					lhs_rhs_rhs = lhs_rhs->rhs;			// lhs_rhs_rhs = c
//					cout << "break2.3\n";
				}
			}
			
			if( (lhs_lhs) && (lhs_rhs_lhs) && (lhs_rhs_rhs) )
			{
//				cout << "break2.4\n";
				if(wff_equals(lhs_lhs, lhs_rhs_rhs) )	// checking whether a = c
				{
//					cout << "break2.5\n";
					check = true;
				}
			}
		}
		
		// check whether check is true
		
		if(check)
		{
			// apply axiom1 with A as lhs_lhs and B as lhs_rhs_lhs
			wff * rhs = new wff(lhs_rhs_lhs, lhs_lhs, 'A');
			wff * res = new wff(lhs_lhs, rhs, 'A');
			if(is_in_vector(res))
			{
				continue;
			}
			
			proof_vec.push_back(res);
			printing_vector.push_back(make_pair(-1, -1) );
			// print A and B with axiom no also
			cout << "L" << proof_vec.size() - 1 << ": ";
			res->print();
			cout<<"\t\t Applying Axiom1 with A as ";
			lhs_lhs->print();
			cout << " and B as ";
			lhs_rhs_lhs->print();
			cout<< endl;			
			return true;
		}
	
	}
	return false;
}


/////////////////////////////////////////////////////////////

bool try_axiom3()
{
	vector<wff *>::iterator itr;
	
	for(itr = proof_vec.begin(); itr!= proof_vec.end() ; itr++)
	{
		// check whether this(*itr) hypothesis is of the form ( (A->f)->f), if so apply axiom 3
		
		// this if checks whether the rightmost is 'f'
		if( (*itr)->rhs != NULL && (*itr)->rhs->rhs == NULL && (*itr)->rhs->val == 'f')
		{		
			// this if checks whether LHS is of the form A->f
			if((*itr)->lhs != NULL && (*itr)->lhs->lhs != NULL && (*itr)->lhs->rhs!=NULL && (*itr)->lhs->rhs->rhs == NULL && (*itr)->lhs->rhs->val == 'f' )
			{
					// apply axiom 3
					
					wff * a = new wff(NULL, NULL, 'f');
					wff * t1 = new wff( (*itr)->lhs->lhs, a, 'A');
					wff * t2 = new wff(t1, a, 'A');
					wff * t3 = new wff(t2, (*itr)->lhs->lhs, 'A');
					
					if(!is_in_vector(t3))
					{	
						proof_vec.push_back(t3);
						printing_vector.push_back(make_pair(-1, -1) );
						cout << "L" << proof_vec.size() - 1 << ": ";
						t3->print();
						cout<<"\t\t Applying Axiom3 with A as ";
						(*itr)->lhs->lhs->print();
						cout<<endl;
						return true;
					}	
			}	
		}
	}
	
	return false;
}

bool try_axiom3_2()
{
	// check whether this lhs of (*itr) hypothesis is of the form ( ((A->f)->f)->A), if so apply axiom 3

	for(int i = 0;i<proof_vec.size();i++)
	{
		if(proof_vec[i]->lhs && proof_vec[i]->lhs->lhs && proof_vec[i]->lhs->rhs && proof_vec[i]->lhs->lhs->lhs && proof_vec[i]->lhs->lhs->rhs && proof_vec[i]->lhs->lhs->lhs->lhs && proof_vec[i]->lhs->lhs->lhs->rhs)
		{
			// check for the equalities
			wff * f1 = new wff(NULL, NULL, 'f');
		
			if(wff_equals(proof_vec[i]->lhs->lhs->lhs->lhs, proof_vec[i]->lhs->rhs)  && wff_equals(proof_vec[i]->lhs->lhs->lhs->rhs, f1) && wff_equals(f1, proof_vec[i]->lhs->lhs->rhs) )
			{
				// apply axiom3 with A as proof_vec[i]->lhs->rhs
				wff * res = new wff(proof_vec[i]->lhs->lhs, proof_vec[i]->lhs->rhs, 'a');
				if(is_in_vector(res))
				{
					continue;
				}
				proof_vec.push_back(res);
				printing_vector.push_back(make_pair(-1, -1) );
				// print
				cout << "L" << proof_vec.size() - 1 << ": ";
				res->print();
				cout<<"\t\t Applying Axiom3 with A as ";
				proof_vec[i]->lhs->rhs->print();
				cout<<endl;
				return true;
			}
		}
	
	}
	return false;
}


///////////////////////////////////////////////////////////////////////

bool try_axiom2()
{
	// will keep being called recursively if nothing else can be applied, hence num_consecutive_axiom2 variable.
	
	// check if node is of form A -> (B-> C)  i.e rhs->rhs is not null 
	vector<wff *>::iterator itr;
	//cout<<"check1"<<endl;
	int i =0;
	for(itr = proof_vec.begin(); itr!= proof_vec.end() ; itr++, i++)
	{
		if(in_rhs_axiom2((*itr)))
		{
			continue;
		}
		if((*itr)->lhs != NULL && (*itr)->rhs->rhs != NULL)
		{
			if(in_axiom_vec(i))
			{
				continue;
			}
			// can apply axiom 2
			 
			wff* a = new wff((*itr)->lhs, (*itr)->rhs->lhs,'A');
			wff* b = new wff((*itr)->lhs, (*itr)->rhs->rhs,'A');
			wff* c = new wff (a,b,'A');
			wff* d = new wff( (*itr), c, 'A');
			
			if(!is_in_vector(d))
			{
				//cout<<"check2"<<endl;
				wff* e= (*itr)->lhs;
				wff* f = (*itr)->rhs->lhs;
				wff* g = (*itr)->rhs->rhs;
				proof_vec.push_back(d);
				printing_vector.push_back(make_pair(-1, -1) );
				cout << "L" << proof_vec.size() - 1 << ": ";
				d->print();
				cout<<"\t\t Applying Axiom2 with A as ";
				e->print();
				cout<< " and B as ";
				f->print();
				cout<< " and C as ";
				g->print();
				//cout<<"\t\t applying axiom 2";
				cout<<endl;
				axiom2_indices.push_back(proof_vec.size()-1);
				rhs_axiom2.push_back(c);
				return true;
			} 
		}
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////////
// user should give the correct expressions ( for A, B,C) with parentheses
void ask_human_help()
{
	cout << "\n\nPlease enter the no corresponding to your choice\n";
	cout << "1) Apply transitivty\n2) Apply Contraposition\n3) Apply De Morgan's 1st law ( ~(P^Q) -> ~P v ~Q)\n4) Apply De Morgan's 2nd law ( ~(P v Q) -> ~P ^ ~Q)\n5) Apply F->P\n6) Some other statement\n7) Apply axioms\n8) Continue\n\n";
	int choice;
	cin >>choice;

	switch(choice)
	{
		case 1:
			{
				string a11, b11, c11;
				cout<<"Enter A\n";
				cin >>a11;
				cout<<"Enter B\n";
				cin >>b11;
				cout<<"Enter C\n";
				cin >>c11;
			
				wff * choice1_a = string_to_wff(a11);
				wff * choice1_b = string_to_wff(b11);
				wff * choice1_c = string_to_wff(c11);
			
				// now execute a child process, which will prove transitivity on it
			
				wff *lhs = new wff(choice1_a, choice1_b, 'A');
				wff *temp2 = new wff(choice1_b, choice1_c, 'B');
				wff *temp3 = new wff(choice1_a, choice1_c, 'C');
			
				wff * rhs = new wff(temp2, temp3, 'D');
				wff * final = new wff(lhs, rhs, 'E');			
			
				if(!fork())
				{
					// inside child process
					cout << "\n\n***************************************************************************\n";
					cout << "Proving Transitivity\n\n";
			
					// clear proof_vec, axiom2_indices, rhs_axiom2
					proof_vec.clear();
					printing_vector.clear();
					axiom2_indices.clear();
					rhs_axiom2.clear();
				
					final->implement_dt();
			
					exit(0);
				}
				wait(NULL);
				cout << "\n\n***************************************************************************\n\n\n";
				// push back in proof_vec
				proof_vec.push_back(final);
				printing_vector.push_back(make_pair(-1, -1) );
				// do printing
				
				cout << "L" << proof_vec.size() - 1 << ": ";
				final->print();
				cout<<"\t\t Applying transitivity with A as ";
				choice1_a->print();
				cout<< " and B as ";
				choice1_b->print();
				cout<< " and C as ";
				choice1_c->print();
				//cout<<"\t\t applying axiom 2";
				cout<<endl;
				
				return;
			}
		case 2:
			{
				// contraposition
				
				string a, b;
				cout<<"Enter A\n";
				cin >>a;
				cout<<"Enter B\n";
				cin >>b;
			
				wff *a1 = string_to_wff(a);
				wff *b1 = string_to_wff(b);
				
				wff * lhs = new wff(a1, b1, 'A');
				wff * f = new wff(NULL, NULL, 'f');
				wff * temp1 = new wff(b1, f, 'A');
				wff * temp2 = new wff(a1, f, 'A');
				wff *rhs = new wff(temp1, temp2, 'A');
				
				wff * final = new wff(lhs, rhs, 'A');
			
				if(!fork())
				{
					// inside child process
					cout << "\n\n***************************************************************************\n";
					cout << "Proving Contraposition\n\n";
			
					// clear proof_vec, axiom2_indices, rhs_axiom2
					proof_vec.clear();
					printing_vector.clear();
					axiom2_indices.clear();
					rhs_axiom2.clear();
				
					final->implement_dt();
			
					exit(0);
				}
				wait(NULL);
				cout << "\n\n***************************************************************************\n\n\n";
				// push back in proof_vec
				proof_vec.push_back(final);
				printing_vector.push_back(make_pair(-1, -1) );
				// do printing
				
				cout << "L" << proof_vec.size() - 1 << ": ";
				final->print();
				cout<<"\t\t Applying contraposition with A as ";
				a1->print();
				cout<< " and B as ";
				b1->print();
				cout<<endl;
				
				
				return;
			}
		case 3:
			{
				// case 3 : De Morgan's first law ~(P^Q) -> ~P v ~Q
				string a, b;
				cout<<"Enter A\n";
				cin >>a;
				cout<<"Enter B\n";
				cin >>b;
			
				wff *a1 = string_to_wff(a);
				wff *b1 = string_to_wff(b);
				
				wff * f1 = new wff(NULL,NULL,'f');
				
				wff* temp1 = new wff(a1, f1, 'A');
				wff* temp2 = new wff(b1, f1, 'A');			
								
				wff* temp3 = new wff(a1, temp2, 'A');
				wff* temp4 = new wff(temp3, f1, 'A');
				wff* lhs = new wff(temp4, f1, 'A');
				
				wff* temp5 = new wff(temp1, f1, 'A');
				wff* rhs = new wff(temp5, temp2, 'A');
				
				wff* final = new wff(lhs, rhs, 'A');
						
				if(!fork())
				{
					// inside child process
					cout << "\n\n***************************************************************************\n";
					cout << "Proving De Morgan's first law : ~(P ^ Q) -> (~P v ~Q)  (\n\n";
			
					// clear proof_vec, axiom2_indices, rhs_axiom2
					proof_vec.clear();
					printing_vector.clear();
					axiom2_indices.clear();
					rhs_axiom2.clear();
				
					final->implement_dt();
			
					exit(0);
				}
				wait(NULL);
				cout << "\n\n***************************************************************************\n\n\n";
				// push back in proof_vec
				proof_vec.push_back(final);
				printing_vector.push_back(make_pair(-1, -1) );
				// do printing
				
				
				cout << "L" << proof_vec.size() - 1 << ": ";
				final->print();
				cout<<"\t\t Applying de morgan's first law with A as ";
				a1->print();
				cout<< " and B as ";
				b1->print();
				cout<<endl;
				
				return;
			}
		case 4:
			{
				// Right now we don't know how to prove it, therefore we are not doing it, // we are able to prove it now
				// case 3 : De Morgan's second law ~(P v Q) -> ~P ^ ~Q
				
				string a, b;
				cout<<"Enter A\n";
				cin >>a;
				cout<<"Enter B\n";
				cin >>b;
			
				wff *a1 = string_to_wff(a);
				wff *b1 = string_to_wff(b);
				
				wff * f = new wff(NULL,NULL,'f');
				
				wff * temp1 = new wff(a1, f, 'A');			// P->F
				wff * temp2 = new wff(temp1, b1, 'A');		// (P->F)->Q
				wff * lhs = new wff(temp2, f, 'A');			// ((P->F)->Q))->F
				
				wff * temp4 = new wff(b1, f, 'A');			// Q->F
				wff * temp5 = new wff(temp4, f, 'A');		//((Q->F)->F)
				wff * temp6 = new wff(temp1, temp5, 'A');	// ((P->F) -> ((Q->F)->F) ) 
				wff * rhs = new wff(temp6, f, 'A');			// ((P->F) -> ((Q->F)->F) )->F
				
				wff * final = new wff(lhs, rhs, 'A');
					
				if(!fork())
				{
					// inside child process
					cout << "\n\n***************************************************************************\n";
					cout << "Proving De Morgan's second law : ~(P v Q) -> (~P ^ ~Q)  (\n\n";
			
					// clear proof_vec, axiom2_indices, rhs_axiom2
					proof_vec.clear();
					printing_vector.clear();
					axiom2_indices.clear();
					rhs_axiom2.clear();
				
					final->implement_dt();
			
					exit(0);
				}
				wait(NULL);
				cout << "\n\n***************************************************************************\n\n\n";
				// push back in proof_vec
				proof_vec.push_back(final);
				printing_vector.push_back(make_pair(-1, -1) );
				// do printing
				
				
				cout << "L" << proof_vec.size() - 1 << ": ";
				final->print();
				cout<<"\t\t Applying de morgan's second law with A as ";
				a1->print();
				cout<< " and B as ";
				b1->print();
				cout<<endl;
				
				return;	
							
				
							
				return;
			}
		case 5:
			{	
				// Apply F->P
				string a;
				cout << "Enter P\n";
				cin >> a;
				
				wff * f = new wff(NULL, NULL, 'f');
				wff * a1 = string_to_wff(a);				
				
				wff * final = new wff(f, a1, 'A');
				
				if(!fork())
				{
					// inside child process
					cout << "\n\n***************************************************************************\n";
					cout << "Proving F->P\n\n";
			
					// clear proof_vec, axiom2_indices, rhs_axiom2
					proof_vec.clear();
					printing_vector.clear();
					axiom2_indices.clear();
					rhs_axiom2.clear();
				
					final->implement_dt();
			
					exit(0);
				}
				wait(NULL);
				cout << "\n\n***************************************************************************\n\n\n";
				// push back in proof_vec
				proof_vec.push_back(final);
				printing_vector.push_back(make_pair(-1, -1) );
				// do printing
				
				
				cout << "L" << proof_vec.size() - 1 << ": ";
				final->print();
				cout<<"\t\t Applying F->P with P as ";
				a1->print();
				cout<<endl;
				
				
				return;
			}
		case 6:
			{
				// Any statement
				
				int status;
				string a;
				cout << "Enter the expression which you want to check is true or not\n";
				cin >> a;
				
				wff * final = string_to_wff(a);
				
				if(!fork())
				{
					// inside child process
					cout << "\n\n***************************************************************************\n";
					cout << "Proving\n\n";
			
					// clear proof_vec, axiom2_indices, rhs_axiom2
					proof_vec.clear();
					printing_vector.clear();
					axiom2_indices.clear();
					rhs_axiom2.clear();
				
					final->implement_dt();
			
					exit(0);
				}
				wait(&status);
				
				if(status==0)
				{
					cout << "\n\n***************************************************************************\n\n\n";
					// push back in proof_vec
					proof_vec.push_back(final);
					printing_vector.push_back(make_pair(-1, -1) );
					// do printing
				}
				else
				{
					cout << "We were not able to prove that it was a theorem\n";
					cout << "\n\n***************************************************************************\n\n\n";
				}
				return;
			}
		case 7:
			{
				break;
			}
		case 8:
			{
				return;
			}
		default:
			{	
				cout << "You enter an invalid choice\n\n";
				return;
			}
	}

	cout<<"Which axiom should be applied ?" << endl;
	int axiom_num;
	cin>> axiom_num;
	if(axiom_num == 1)
	{
		
		string a, b;
		cout << "Enter A\n";
		cin >> a;
		cout << "Enter B\n" ;
		cin >>b;
		
		wff* a1 = string_to_wff(a);
		wff* b1 = string_to_wff(b);
		
		wff* rhs = new wff(b1, a1, 'A');
		wff* new_rule = new wff ( a1, rhs, 'A');
		
		proof_vec.push_back(new_rule);
		printing_vector.push_back(make_pair(-1, -1) );
		
		cout << "\n\n";
		cout << "L" << proof_vec.size() - 1 << ": ";
		new_rule->print();
		cout<<"\t\t Applying Axiom1 with A as ";
		a1->print();
		cout<< " and B as ";
		b1->print();
		
		cout<< endl;
	}
	
	else if (axiom_num == 2)
	{
		string a, b, c;
		cout << "\n\nEnter A\n";
		cin >> a;
		cout << "Enter B\n";
		cin >>b;
		cout << "Enter C\n";
		cin >> c;
		wff* a1 = string_to_wff(a);
		wff* b1 = string_to_wff(b);
		wff* c1 = string_to_wff(c);
		
		wff* t1 = new wff(b1, c1, 'A'); // B->C
		wff* lhs = new wff(a1, t1, 'A'); // A->(B->C)
		
		wff* t2 = new wff(a1, b1, 'A'); // A->B
		wff* t3 = new wff(a1, c1, 'A'); // A->C
		wff* rhs = new wff(t2, t3, 'A'); // (A->B) -> (A->C)
		
		wff* new_rule = new wff(lhs, rhs, 'A');
		proof_vec.push_back(new_rule);
		printing_vector.push_back(make_pair(-1, -1) );
		
		cout << "\n\n";
		cout << "L" << proof_vec.size() - 1 << ": ";
		new_rule->print();
		cout<<"\t\t Applying Axiom2 with A as ";
		a1->print();
		cout<< " and B as ";
		b1->print();
		cout<< " and C as ";
		c1->print();
		
		cout<< endl;
		axiom2_indices.push_back(proof_vec.size()-1);
		rhs_axiom2.push_back(rhs);
	}
	
	else if (axiom_num == 3)
	{
		string a;
		cout << "Enter A\n";
		cin >> a;
		
		wff* a1 = string_to_wff(a);
		wff* f1 = new wff(NULL, NULL, 'f'); // f
		wff* t1 = new wff(a1, f1, 'A'); //A->f
		wff* lhs = new wff(t1, f1, 'A'); // (A->f)->f
		
		
		
		wff* new_rule = new wff ( lhs, a1, 'A');
		
		proof_vec.push_back(new_rule);
		printing_vector.push_back(make_pair(-1, -1) );
		
		cout << "\n\n";
		cout << "L" << proof_vec.size() - 1 << ": ";
		new_rule->print();
		cout<<"\t\t Applying Axiom3 with A as ";
		a1->print();
		
		cout<< endl;
	}
	
	else
	{
		cout << "invalid axiom number" << endl;
		exit(0);
	}
	
}

/////////////////////////////////////////////////////////////////////////


wff * string_to_wff(string str)
{
	// remove all the spaces 
	
	string str1;
	for(int i=0;i<str.length();i++)
	{
		if(str[i]!=' ')
		{
			str1.push_back(str[i]);
		}
	}

	// call the helper function with string and given index
	return helper(str1);

}



bool check_if_valid_char(char a)
{
	if ( ((int)a>=65 && (int)a<=90) || a=='f' )
	{
		return true;
	}
	return false;
}

wff * helper(string str)
{
	// base case
	if(str.length() == 1)
	{
		if(check_if_valid_char(str[0]))
		{
			wff * t = new wff(NULL, NULL, str[0]);
			return t;	
		}
		else
		{
			cout << "Invalid expression\n";
			exit(1);
		}
	}

	wff *lhs, *rhs, *final;

	// ignore first and last bracket
	string str1 = str.substr(1, str.length() -2);
	// now use str1 further

	// if the first char is '(', then find its matching parenthesis, and this whole will be the lhs
	int i = 0;
	if(str1[0] == '(')
	{
		int index = find_matching(str1);
		string str2 = str1.substr(0, index+1);
		i = index+1;
		lhs = helper(str2);
	}
	else
	{
		if(check_if_valid_char(str1[0]))
		{
			i++;
			lhs = new wff(NULL, NULL, str1[0]);
		}
		else
		{
			cout<< "Invalid expression\n";
			exit(1);
		}
	}
	
	// expect -> sign
	if(str1[i] == '-' && str1[i+1] == '>')
	{
		i+=2;
	}
	else
	{
		cout<< "Invalid expression\n";
		exit(1);
	}		
	
	// now we will see RHS 
	
	string str3 = str1.substr(i, string::npos);
	
	rhs = helper(str3);
	
	final = new wff(lhs, rhs, 'a');
	return final;
}

int find_matching(string str)
{
	//find the index at which matching ')' for the first and return the index, if not found then throw an error
	int count = 1;
	for(int i =1; i<str.length();i++)
	{
		if(str[i] == '(')
		{
			count++;
		}
		else if(str[i] == ')')
		{
			count--;
		}

		if(count == 0)
		{
			return i;
		}
	}
}

////////////////////////////////////////////

bool in_axiom_vec(int i)
{
	for(int j = 0; j< axiom2_indices.size();j++)
	{
		if(axiom2_indices[j]==i)
			return true;
	}
	return false;
}

///////////////////////////////////////////////

bool in_rhs_axiom2 ( wff * w)
{
	for(int i=0; i< rhs_axiom2.size();i++)
	{
		if(wff_equals(w, rhs_axiom2[i]))
			return true;
	}
	return false;
}

///////////////////////////////////////////////

bool in_vec(wff *a , vector<wff *> & vec)
{
	for(int i =0;i<vec.size();i++)
	{
		if(wff_equals(a, vec[i]) )
		{
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////

bool try_brute_force()
{
	// extract out literals and expressions of the form P->Q from the recent 10 axioms and push them in temp vector
	cout << "\n#########################\n";
	cout << "Applying Brute force\n\n";
	
	vector<wff *> temp;
	
	for(int i = proof_vec.size() -1; i>=0 && proof_vec.size() - i < 11;i--)
	{
		// call a function vec which will return all the wff's
		vector <wff *> * t = extract_out_literals(proof_vec[i]);
		if(t == NULL)
		{
			continue;
		}
		for(int j =0;j<t->size();j++)
		{
			if(!in_vec( (*t)[j], temp) )
			{
				temp.push_back( (*t)[j] );
			}
		}
		free(t);
	}
	
	for(int i = proof_vec.size() -1; i>=0 && proof_vec.size() - i < 11;i--)
	{
		// call a function vec which will return all the wff's
		vector <wff *> * t = extract_wff_of_depth_one(proof_vec[i]);
		if(t == NULL)
		{
			continue;
		}
		for(int j =0;j<t->size();j++)
		{
			if(!in_vec( (*t)[j], temp) )
			{
				temp.push_back( (*t)[j] );
			}
		}
		free(t);
	}
	
	vector<wff *> vec_axioms;
	
	// Now temp has the required thing, now apply all the axioms using this and push it in another vector
	
	// Applying axiom1
	for(int i =0;i<temp.size();i++)
	{
		wff *a = temp[i];
		wff *b;
		for(int j=0;j<temp.size();j++)
		{
			b = temp[j];
			wff * rhs = new wff(b, a, 'A');			// (b->a)
			wff * final = new wff(a, rhs, 'A');		// (a-> (b->a))
			if(!in_vec(final, vec_axioms) )
			{
				vec_axioms.push_back(final);
			}
//			vec_axioms.push_back(new wff(a, new wff(b, a, 'A'), 'A') );
		} 
	}
	
	int axiom1_count = vec_axioms.size();
	
	// Applying axiom2	
	for(int i =0;i<temp.size();i++)
	{
		wff *a = temp[i];
		wff *b, *c;
		for(int j=0;j<temp.size();j++)
		{
			b = temp[j];
			for(int k =0;k<temp.size();k++)
			{
				c = temp[k];
				wff * temp1 = new wff(b, c, 'A');			// (b->c)
				wff * lhs = new wff(a, temp1, 'A');			// (a->(b->c))
				wff * temp2 = new wff(a, b, 'A');			// (a->b)
				wff * temp3 = new wff(a, c, 'A');			// (a->c)
				wff * rhs = new wff(temp2, temp3, 'A');		//((a->b)->(a->c))
				wff * final = new wff(lhs, rhs, 'A');		// ( (a->(b->c)) -> ((a->b)->(a->c)) )
				if(!in_vec(final, vec_axioms) )
				{
					vec_axioms.push_back(final);
				}
//				vec_axioms.push_back(new wff(new wff(a,new wff(b, c, 'A') ,'A'), new wff(new wff(a, b, 'A'),new wff(a, c, 'A'),'A'),'A' ) );
				
			}			
		} 
	}
	
	int axiom2_count = vec_axioms.size();
	
	// Applying axiom3
	for(int i =0;i<temp.size();i++)
	{
		wff *a = temp[i];
		wff *f = new wff(NULL, NULL, 'f');			// f
		wff *t1 = new wff(a, f, 'A');				// (a->f)
		wff *t2 = new wff(t1, f, 'A');				// ( (a->f) -> f) 
		wff * final = new wff(t2, a, 'A');			// ( ( (a->f) -> f) -> a )
		if(!in_vec(final, vec_axioms) )
		{
			vec_axioms.push_back(final);	
		}
	}
	
	int axiom3_count = vec_axioms.size();
	
//	for(int i =0;i<vec_axioms.size();i++)
//	{
//		vec_axioms[i]->print();
//		cout<< endl;
//	}
	// Now check whether any of this is helpful for us, if so, then apply it and break from here
	
//	cout<<"Size of vec_axioms is "<<vec_axioms.size() << endl;
	
	// Now select all those with which modus Ponens can be applied and then push it in the proof_vec
	
	bool check = false;
	for(int i =0;i<proof_vec.size();i++)
	{
		// check whether modus_ponens can be applied with anything in proof_vec
		for(int j=0;j<vec_axioms.size();j++)
		{
			// check whether proof_vec[i] is lhs of anything of vec_axioms, if so, then we can apply modus ponens
			if(wff_equals(proof_vec[i], vec_axioms[j]->lhs))
			{
				if(!is_in_vector(vec_axioms[j]->rhs) )
				{
					proof_vec.push_back(vec_axioms[j]);
					printing_vector.push_back(make_pair(-1, -1) );
					cout << "L" << proof_vec.size() - 1 << ": ";
					// First print about the axiom applied
					if(j<axiom1_count)
					{
						vec_axioms[j]->print();
						cout << "\t\tApplying axiom1 with A as ";
						vec_axioms[j]->lhs->print();
						cout << " and B as ";
						vec_axioms[j]->rhs->lhs->print();
						cout << endl;
					}
					else if(j<axiom2_count)
					{
						vec_axioms[j]->print();
						cout << "\t\tApplying axiom2 with A as ";
						vec_axioms[j]->lhs->lhs->print();
						cout << " and B as ";
						vec_axioms[j]->lhs->rhs->lhs->print();
						cout << " and C as ";
						vec_axioms[j]->lhs->rhs->rhs->print();
						cout << endl;
					}
					else
					{
						vec_axioms[j]->print();
						cout << "\t\tApplying axiom3 with A as ";
						vec_axioms[j]->rhs->print();
						cout << endl;
					}

					proof_vec.push_back(vec_axioms[j]->rhs);
					printing_vector.push_back(make_pair(i, proof_vec.size() - 2) );
					
					check = true;
					cout << "L" << proof_vec.size() - 1 << ": ";
					vec_axioms[j]->rhs->print();
					cout << "\t\tby modus ponens between lines " << i << " and "<<proof_vec.size() - 2;
					cout << endl;
				}
			}
					
			if(wff_equals(vec_axioms[j], proof_vec[i]->lhs))
			{
				if(!is_in_vector(proof_vec[i]->rhs) )
				{
					proof_vec.push_back(vec_axioms[j]);
					printing_vector.push_back(make_pair(-1, -1) );
					cout << "L" << proof_vec.size() - 1 << ": ";
					// First print about the axiom applied
					if(j<axiom1_count)
					{
						vec_axioms[j]->print();
						cout << "\t\tApplying axiom1 with A as ";
						vec_axioms[j]->lhs->print();
						cout << " and B as ";
						vec_axioms[j]->rhs->lhs->print();
						cout << endl;
					}
					else if(j<axiom2_count)
					{
						vec_axioms[j]->print();
						cout << "\t\tApplying axiom2 with A as ";
						vec_axioms[j]->lhs->lhs->print();
						cout << " and B as ";
						vec_axioms[j]->lhs->rhs->lhs->print();
						cout << " and C as ";
						vec_axioms[j]->lhs->rhs->rhs->print();
						cout << endl;
					}
					else
					{
						vec_axioms[j]->print();
						cout << "\t\tApplying axiom3 with A as ";
						vec_axioms[j]->rhs->print();
						cout << endl;
					}
				
					proof_vec.push_back(proof_vec[i]->rhs);
					printing_vector.push_back(make_pair(i, proof_vec.size() - 2) );
					
					check = true;
					cout << "L" << proof_vec.size() - 1 << ": ";
					proof_vec[i]->rhs->print();
					cout << "\t\tby modus ponens between lines " << i << " and "<<proof_vec.size() - 2;
					cout << endl;
				}
			}
		}
	}
	cout << "\n\n#########################\n\n";
	
	return check;
}

// extract out literals

vector<wff *> * extract_out_literals(wff * a)
{
	if(!a)
	{
		return NULL;
	}

	vector<wff *> * t = new vector<wff *>();
	vector<wff *> * l1,* l2;
	
	if(a->lhs == NULL && a->rhs == NULL)
	{
		t->push_back(a);
		return t;
	}

	l1 = extract_out_literals(a->lhs);
	l2 = extract_out_literals(a->rhs);
	
	if(l1 && l2)
	{
		t->reserve(l1->size() + l2->size() );
		t->insert(t->end(), l1->begin(), l1->end());
		t->insert(t->end(), l2->begin(), l2->end());
		free(l1);
		free(l2);
		return t;		
	}
	else if(l1)
	{	
		t->reserve(l1->size());
		t->insert(t->end(), l1->begin(), l1->end());
		free(l1);
		return t;
	}
	else if(l2)
	{	
		t->reserve(l2->size());
		t->insert(t->end(), l2->begin(), l2->end());
		free(l2);
		return t;
	}
	else{
		return NULL;
	}
}

// extract out expressions of the form P->Q

vector<wff *> * extract_wff_of_depth_one(wff *a)
{
	if(!a)
	{
		return NULL;
	}

	vector<wff *> * t = new vector<wff *>();
	
	if(a->lhs !=NULL && a->rhs!=NULL && a->lhs->lhs == NULL && a->rhs->rhs == NULL)
	{
		t->push_back(a);
		return t;
	}
	
	vector<wff *> *l1, *l2;
	l1 = extract_wff_of_depth_one(a->lhs);
	l2 = extract_wff_of_depth_one(a->rhs);

	if(l1 && l2)
	{
		t->reserve(l1->size() + l2->size() );
		t->insert(t->end(), l1->begin(), l1->end());
		t->insert(t->end(), l2->begin(), l2->end());
		free(l1);
		free(l2);
		return t;		
	}
	else if(l1)
	{	
		t->reserve(l1->size());
		t->insert(t->end(), l1->begin(), l1->end());
		free(l1);
		return t;
	}
	else if(l2)
	{	
		t->reserve(l2->size());
		t->insert(t->end(), l2->begin(), l2->end());
		free(l2);
		return t;
	}
	else{
		return NULL;
	}

}

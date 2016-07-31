#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////
bool isPalindrome(vector <float> v){
	int i=1, j= v.size() -1;
	for(;i<j;i++,j--){
		if(v[i] != v[j])
			return false;
	}
	return true;
	
}

bool isMajority(vector <float> v){
	int numones =0, numzeroes =0;
	for(int i=1; i< v.size(); i++){
		if(v[i] == 1) 
			numones++;
		else numzeroes++;	
	}
	if(numones > numzeroes) return true;
	else return false;
}

bool numberOfOnesIsEven(vector <float> v){
	int numones = 0;
	for(int i=1; i< v.size(); i++){
		if(v[i] == 1) 
			numones++;
	}
	if(numones %2 ==0) return true;
	else return false;		
}
///////////////////////////////////////////////////////////

int dotProduct( vector <float> v1, vector <float> v2){
	int answer=0;
	for(int i=0;i< v1.size(); i++){
		answer+= v1[i]*v2[i];
	}
	return answer;
}

vector <float> negation( vector <float> v){
	vector <float> v1;
	v1.resize(v.size());
	for(int i=0; i< v.size(); i++)
		v1[i] = -v[i];
	return v1;	
}

// This is modified add, this returns c*v1 + v2
vector <float> add(vector <float> v1, vector <float> v2){
	float c = 2.5 ;
	vector <float> v;
	v.resize(v1.size());
	for(int i=0;i< v1.size(); i++){
		v[i] = c*v1[i] + v2[i];
	}
	return v;
}

vector < vector <float> > generate (int n){
	vector <vector <float> > table;
	table.resize(pow(2,n));
	
	for (int j = 0; j< table.size() ; j++){
		table[j].push_back(-1);
		for(int i=n-1; i>=0; i--){
			table[j].push_back((j>>i) & 1);
		}			
	}	
	return table;
}

void print(vector <float> x){
	cout<<"< ";
	for(int i =0;i<x.size();i++){
		cout<<x[i]<<" ";
	}
	cout<<">\n";
}


void perceptron(vector < vector <float> > x){
	//cout<<"The size of x is "<<x.size()<<endl;
	int numSteps = 0;
	bool check = false, isPresent = false;
	vector <vector <float> > cycle;	// this is for cycle checking
	vector <float> w(x[0].size(), 0);
	cout<<"Initial w is : ";
	print(w);
	while(true){
		check = false;	
		for(int i=0;i<x.size();i++){
			//cout<<"i is "<<i<<"  and the value of dot-product is "<<dotProduct(x[i], w)<<endl;
			if(dotProduct(x[i], w) <= 0){
				numSteps++;
				// if the case fails then modify w and start the algo again
				w = add(x[i], w);
				cout<<"w is : ";
				print(w);
				
				check = true;
				break;
				// now we have to again start from the beginning of this loop
			}
		}
		if(!check){
			// we have reached the end point
			cout<<"No of steps are "<<numSteps<<endl; 
			cout<<"Final w is : ";
			print(w);
			return;
		}
		// check in cycle whether this value of w has already been arrived at, if so then show that cycle is reached
		isPresent = false;
		for(int i =0;i<cycle.size();i++){
			if(cycle[i] == w){
				isPresent = true;
				break;
			}
		}
		
		if(isPresent){
			cout<<"Cycle is present, the given function cannot be computed by perceptron\n";
			return;
		}
		else{
			cycle.push_back(w);	
		}
	}
}



int main(){
	int operation;
	cout << "enter operation : 1 for 2-input NAND \n 2 for 2-input NOR \n 3 for 2-input XOR \n 4 for 5-input palindrome \n 5 for 5-input majority \n 6 for 6-input parity \n";
	cin >> operation;  
	vector< vector <float> > vectors;
	
	cout<<"The output format will be as follows: < theta, w1, w2, ...., wn >\n";
				
	
	switch (operation){
		case 1 :
			// NAND 2-input
			vectors= generate (2);
			for(int i=0; i< vectors.size(); i++){
				//print(vectors[i]);
				if((int)vectors[i][1] & (int)vectors[i][2]){
					vectors[i] = negation(vectors[i]);
					//cout<<"i is "<<i<<"	";
					//print(vectors[i]);
				}
			}
			// working correctly till this point
			perceptron(vectors);	
			break; 
		
		case 2 :
			// NOR 2-input
			vectors= generate (2);
			for(int i=0; i< vectors.size(); i++){
				if((int)vectors[i][1] | (int)vectors[i][2]){
					vectors[i] = negation(vectors[i]);
				}
			}
			perceptron(vectors);	
		
		break;
		
		case 3 :
			// XOR 2-input
			vectors= generate (2);
			for(int i=0; i< vectors.size(); i++){
				if(!((int)vectors[i][1] ^ (int)vectors[i][2])){
					vectors[i] = negation(vectors[i]);
				}
			}
			perceptron(vectors);	
		break;
		
		case 4 :
			// 5-input palindrome
			vectors= generate (5);
			for(int i=0; i< vectors.size(); i++){
				//print(vectors[i]);
				if(!isPalindrome(vectors[i])){
					vectors[i] = negation(vectors[i]);
					//print(vectors[i]);
				}
			}
			perceptron(vectors);
		break;
		
		case 5 :
			//5-input majority
			vectors= generate (5);
			for(int i=0; i< vectors.size(); i++){
				if(!isMajority(vectors[i])){
					vectors[i] = negation(vectors[i]);
				}
			}
			perceptron(vectors);
		break;
		
		case 6 :
			// 6-input parity
			vectors= generate (6);
			for(int i=0; i< vectors.size(); i++){
				if(!numberOfOnesIsEven(vectors[i])){
					vectors[i] = negation(vectors[i]);
				}
			}
			perceptron(vectors);
		break;
		
		default: 
		cout<< "wrong input\n";
	}
  
 	return 0; 	
}

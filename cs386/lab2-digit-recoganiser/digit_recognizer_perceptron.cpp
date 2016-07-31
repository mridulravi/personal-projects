#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

int dotProduct( vector <float> v1, vector <float> v2){
	int answer=0;
	for(int i=0;i< v1.size(); i++)
		answer+= v1[i]*v2[i];
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
	float c = 1 ;
	vector <float> v;
	v.resize(v1.size());
	for(int i=0;i< v1.size(); i++)
		v[i] = c*v1[i] + v2[i];
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


vector<float> perceptron(vector < vector <float> > x){
	int numSteps = 0;
	bool check = false, isPresent = false;
	vector <vector <float> > cycle;	// this is for cycle checking
	vector <float> w(x[0].size(), 0);
	vector <float> error(x[0].size(), -1);
	//cout<<"Initial w is : ";
	//print(w);
	while(true){
		check = false;	
		for(int i=0;i<x.size();i++){
			//cout<<"i is "<<i<<"  and the value of dot-product is "<<dotProduct(x[i], w)<<endl;
			if(dotProduct(x[i], w) <= 0){
				numSteps++;
				// if the case fails then modify w and start the algo again
				w = add(x[i], w);
				//cout<<"w is : ";
				//print(w);
				
				check = true;
				break;
				// now we have to again start from the beginning of this loop
			}
		}
		if(!check){
			// we have reached the end point
			//cout<<"No of steps are "<<numSteps<<endl; 
			//cout<<"Final w is : ";
			//print(w);
			return w;
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
			//cout<<"Cycle is present, the given function cannot be computed by perceptron\n";
			return error;
		}
		else{
			cycle.push_back(w);	
		}
	}
}

bool check( vector<int> pos, vector< float> vec){
	// count no of ones in the input vector
	int count=0;
	for(int i=0;i<vec.size();i++){
		if(vec[i]==1){
			count++;
		}	
	}
	if(count!=pos.size()){
		return false;
	}
	for(int i=0; i< pos.size();i++){
		if(vec[pos[i] ] ==0)
			return false;
	}
	return true;
}


int main(){

	vector< vector <float> > vectors;
	vector< vector <float> > weights;
	
	vectors = generate(7);
	weights.resize(10);
	
	int zeroPos[] = {2,3,4,5,6,7};
	int onePos[] = {4,5};
	int twoPos[] = {1,3,4,6,7};
	int threePos[] = {1,3,4,5,6};
	int fourPos[] = {1,2,4,5};
	int fivePos[] = {1,2,3,5,6};
	int sixPos[] = {1,2,3,5,6,7};
	int sevenPos[] = {3,4,5};
	int eightPos[] = {1,2,3,4,5,6,7};
	int ninePos[] = {1,2,3,4,5,6};
	
	vector<int> zero (zeroPos, zeroPos + sizeof(zeroPos)/ sizeof(int) );
	vector<int> one (onePos, onePos + sizeof(onePos)/ sizeof(int) );
	vector<int> two (twoPos, twoPos + sizeof(twoPos)/ sizeof(int) );
	vector<int> three (threePos, threePos + sizeof(threePos)/ sizeof(int) );
	vector<int> four (fourPos, fourPos + sizeof(fourPos)/ sizeof(int) );
	vector<int> five (fivePos, fivePos + sizeof(fivePos)/ sizeof(int) );
	vector<int> six (sixPos, sixPos + sizeof(sixPos)/ sizeof(int) );
	vector<int> seven (sevenPos, sevenPos + sizeof(sevenPos)/ sizeof(int) );
	vector<int> eight (eightPos, eightPos + sizeof(eightPos)/ sizeof(int) );
	vector<int> nine (ninePos, ninePos + sizeof(ninePos)/ sizeof(int) );
	
	
	//prepare perceptron for 0
	
	for(int i=0; i< vectors.size(); i++){
		if(!check(zero, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[0] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 1
	for(int i=0; i< vectors.size(); i++){
		if(!check(one, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[1] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 2
	for(int i=0; i< vectors.size(); i++){
		if(!check(two, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[2] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 3
	for(int i=0; i< vectors.size(); i++){
		if(!check(three, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[3] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 4
	for(int i=0; i< vectors.size(); i++){
		if(!check(four, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[4] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 5
	for(int i=0; i< vectors.size(); i++){
		if(!check(five, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[5] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 6
	for(int i=0; i< vectors.size(); i++){
		if(!check(six, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[6] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 7
	for(int i=0; i< vectors.size(); i++){
		if(!check(seven, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[7] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 8
	for(int i=0; i< vectors.size(); i++){
		if(!check(eight, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[8] = perceptron(vectors);
	vectors = generate(7);
	
	//prepare perceptron for 9
	for(int i=0; i< vectors.size(); i++){
		if(!check(nine, vectors[i]))
			vectors[i] = negation(vectors[i]);
	}
	weights[9] = perceptron(vectors);

	// take input from user		
	cout<<"Enter the state of all the 7 segments (1 for on and 0 for off):\n";
	vector<float> input;
	input.resize(8);
	input[0] = -1;
	for (int i = 1; i< input.size(); i++)
		cin>>input[i];
	
	// print whether the input segment display is a 0 or not, 1 or not ....
	for (int i = 0; i< 10; i++)
	{
		if (dotProduct(input, weights[i]) > 0) 
			cout << "This is " << i <<"\n";
		else 
			cout << "This is Not "<< i <<"\n";
	} 
	for(int i=0; i<10; i++){
		print(weights[i]);
	}	
	
	
}

















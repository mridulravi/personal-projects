// This implementation is for 2-input XOR, we will implement the general case later on

#include<iostream>
#include<vector>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
using namespace std;

// in our code, the outermost layer will be 0, i.e. layers with smaller index are higher in the neural network

class Neuron{
	
	public:
	vector<double> incomingWeights;			// stores the weights of all the incoming edges to this neuron
											// will store the weight for dummy neuron(which will always be -1) also
	vector<double> incomingDeltaW;			// this is for stroring the value of all the delta W's for all the incoming edges on this neuron
	double output;				// stores the output of this neuron
	double deltaValue;			// stores the delta value of this neuron
};

class Layer{
	public:
	vector<Neuron> neuronList;				// each layer has many neurons in it which are stored in this vector
};

bool isPalindrome(vector <double> v){
	int i=0, j= v.size() -1;
	for(;i<j;i++,j--){
		if(v[i] != v[j])
			return false;
	}
	return true;
	
}

bool isMajority(vector <double> v){
	int numones =0, numzeroes =0;
	for(int i=0; i< v.size(); i++){
		if(v[i] == 1) 
			numones++;
		else numzeroes++;	
	}
	if(numones > numzeroes) return true;
	else return false;
}

double dotProduct( vector <double> v1, vector <double> v2){
	double answer=0;
	for(int i=0;i< v1.size(); i++)
		answer+= v1[i]*v2[i];
	return answer;
}

// negates a vector
vector <double> negation( vector <double> v){
	//vector <double> v1;
	//v1.resize(v.size());
	for(int i=0; i< v.size(); i++)
		v[i] = -v[i];
	return v;	
}

// This is modified add, this returns c*v1 + v2
vector <double> add(vector <double> v1, vector <double> v2){
	double c = 1 ;
	for(int i=0;i< v1.size(); i++)
		v1[i] = c*v1[i] + v2[i];
	return v1;
}

// generates the truth table for n inputs
vector < vector <double> > generate (int n){
	vector <vector <double> > table;
	table.resize(pow(2,n));
	
	for (int j = 0; j< table.size() ; j++){
		for(int i=n-1; i>=0; i--){
			table[j].push_back((j>>i) & 1);
		}			
	}	
	return table;
}

// prints the vector passed to it as input
void print(vector <double> x){
	cout<<"< ";
	for(int i =0;i<x.size();i++){
		cout<<x[i]<<" ";
	}
	cout<<">\n";
}

// generates a random number between 0 an d 10
double randomNumber(){
	int temp = rand() %10 + 1;
	return (temp/5.0) -1.0;
}

// returns the value of the sigmoid function at input n
double sigmoid(double n)
{
	double res=exp(-n);
	res=1/(1+res);
	return res;
}

// returns the output of that neuron
double compute_output(int posNeuron, int layerNo, vector<Layer> & layer){
	// go to one lower layer( higher index), see its output and compute the dot product
	// first is -1 by default
	vector<double> inputs;
	inputs.push_back(-1);
	for(int i =0;i<layer[layerNo+1].neuronList.size();i++){
		inputs.push_back(layer[layerNo+1].neuronList[i].output);
	}
	return sigmoid(dotProduct(inputs,layer[layerNo].neuronList[posNeuron].incomingWeights) );	
}

// returns the delta value for that neuron
double compute_delta(int posNeuron, int layerNo, vector<Layer> & layer, vector<double> & targetOutput, int patternIndex){
	double target_output, neuronOutput; 	
	target_output = targetOutput[patternIndex];
	neuronOutput = layer[layerNo].neuronList[posNeuron].output;
	if(layerNo == 0){
		// (t-o)*o*(1-o)
		return ( (target_output-neuronOutput) *(neuronOutput) * (1 - neuronOutput) );
	}
	else{
		double temp =0.0;
		for(int i=0;i<layer[layerNo-1].neuronList.size();i++){
			temp += layer[layerNo-1].neuronList[i].incomingWeights[posNeuron+1] * layer[layerNo-1].neuronList[i].deltaValue;
		}
		temp *= neuronOutput * (1 - neuronOutput);
		return temp;
	}
}


//l is a vector of layers which is in turn vector of neurons named neuronList, output, deltaValue
//Each neuron has incomingWeights parameter

//In incoming weights, w0 is corresponding to -1 and from w1 we start calculating by multiplying from outputs of the lower layer
//Assuming that oj of the lowest level neuron is set to the input
void ffnn(vector < vector <double> > & pattern, vector<Layer> & l,vector<double> & output, double eta, double threshold)
{

	int itr=pattern.size();	//no. of patterns
	int levels=l.size();	//No. of layers
	double E;
		
	int index=0;		//maintain the index of the pattern for which we're improving the weight after checking E
	
	int i,j,k,res;
	while(true)
	{
		E=0;
		//Calculate E from all the patterns
		for(i=0;i<itr;i++)
		{
			//Set output at lowermost level
			for(j=0;j<l[levels-1].neuronList.size();j++)
			{
				l[levels-1].neuronList[j].output=pattern[i][j];		// for the lowermost level, i.e. input layer, the input itself will be the output as well			
			}
			
			//Bottom-Up
			for(j=levels-2;j>=0;j--)	//Since lowest level is input junction
			{
				for(k=0;k<l[j].neuronList.size();k++)
				{
					l[j].neuronList[k].output=compute_output(k, j, l);	//k is the neuron at which we are computing the output and j is the layer in which that neuron belongs
				}
			}
			
			//Now we've calculated the outputs for each neurons
			//Now we add the squared error for this pattern from the outputs of the outermost layer
			// we are using l[0], because it is the outermost layer
			for(k=0;k<l[0].neuronList.size();k++)
				E+=0.5*(output[i]-l[0].neuronList[k].output)*(output[i]-l[0].neuronList[k].output);
				
		}
		cout<<"Value of E is "<<E<<endl;
		//If error is desirable then we break from while loop()
		if(E<=threshold)
		{
			cout<<"Value of E is "<<E<<endl;
			for(j=0;j<levels-1;j++)
			{
				for(k=0;k<l[j].neuronList.size();k++)
				{
					for(i=0;i<l[j].neuronList[k].incomingWeights.size();i++)
						cout<<l[j].neuronList[k].incomingWeights[i]<<"  ";
					cout<<"			";
				}
				cout<<endl;
			}		
			break;
		}
		
		//When error is not desirable, i.e. higher then threshold
		else
		{
			//Calculating output for a particular pattern with index
			//Set output of lowermost level
			for(j=0;j<l[levels-1].neuronList.size();j++)
			{
				l[levels-1].neuronList[j].output=pattern[index][j];
			}
			
			//Bottom-Up
			for(j=levels-2;j>=0;j--)	//Since lowest level is input junction
			{
				for(k=0;k<l[j].neuronList.size();k++)
				{
					l[j].neuronList[k].output=compute_output(k, j, l);	//k is the neuron at which we are computing the output and j is the layer in which that neuron belongs
				}
			}
			
			//Traversing each layer from top to bottom
			for(j=0;j<levels-1;j++)
			{
				//Traversing each neuron in a layer
				for(k=0;k<l[j].neuronList.size();k++)
				{
					double temp = compute_delta(k, j, l, output, index);
					l[j].neuronList[k].deltaValue= temp;
					
					//Traversing each edge of a neuron
					for(i=0;i<l[j].neuronList[k].incomingWeights.size();i++)
					{	
						if(i==0)		//For threshold, because 1st weight is -1 for each neuron
							l[j].neuronList[k].incomingDeltaW[i]=eta*(temp)*(-1);
						else
							l[j].neuronList[k].incomingDeltaW[i]=eta*(temp)*(l[j+1].neuronList[i-1].output);
							
							// we have already set the size of incoming weights in a neuron according to the next layer, so this will work correctly
					}
					
				}
			}
			
			//Modifying edge weight
			for(j=0;j<levels-1;j++)
			{
				for(k=0;k<l[j].neuronList.size();k++)
				{
					for(i=0;i<l[j].neuronList[k].incomingWeights.size();i++)
						l[j].neuronList[k].incomingWeights[i]+=l[j].neuronList[k].incomingDeltaW[i];
				}
			}
			//Next time we will train on the next pattern
			index = (index+1)%pattern.size();
		}
		
	}
}

int main(){
	// initialize time seed
	srand(time(NULL));

	vector<Layer> layers;
	double E, learningRate, lowerMark=0.1, upperMark=0.9;
	double threshold;
	int numLayers;
	vector<double> input;
	vector<vector <double> > pattern;
	vector<double> targetOutput;	
	vector<int> numNeuronsEachLayer;			// it will be resized to numLayers
	cout<<"Enter error percentage\n";
	cin>>threshold;
	cout<<"Enter learning rate\n";
	cin>>learningRate;
	//cout<<"Enter the lowermark and upperMark respectively\n";
	//cin>>lowerMark>>upperMark;
	//cout<<"Enter the no. of Layers\n";
	//cin>>numLayers;
	numLayers=3;
	layers.resize(numLayers);
	numNeuronsEachLayer.resize(numLayers);
	//cout<<"Enter the no. of neurons in each layer\n";
	//for(int i=0;i<numLayers;i++){
	//	cin>>numNeuronsEachLayer[i];
		//printf("No of layers in %d is %d\n",i ,numNeuronsEachLayer[i]); 
	//}
	numNeuronsEachLayer[0]=1;
	numNeuronsEachLayer[1]=2;
	numNeuronsEachLayer[2]=5;
	//printf("Number of neurons in output layer is %d\n",num
	// because the user entered the value of threshold in percentage
	threshold = ((double)numNeuronsEachLayer[0]*threshold)/100.0;
	cout<<"Threshold is "<<threshold<<endl;
	//exit(0);
	// Resizing all the necessary vectors
	
	for(int i=0;i<numLayers;i++){
		layers[i].neuronList.resize(numNeuronsEachLayer[i]);			// setting the size of the neuronlist of each layer equal to the value specified by the user
	}

	
	for(int i=0;i<numLayers-1;i++){
		for(int j=0;j<numNeuronsEachLayer[i];j++){
			layers[i].neuronList[j].incomingWeights.resize(numNeuronsEachLayer[i+1]+1);
			layers[i].neuronList[j].incomingDeltaW.resize(numNeuronsEachLayer[i+1]+1);
		}
	}
	
	// Resizing done	

	//Initializing random weights between 0 and 1.0 to all the links
	for(int i=0;i<numLayers-1;i++){
		for(int j=0;j<numNeuronsEachLayer[i];j++){
			for(int k=0;k<layers[i].neuronList[j].incomingWeights.size();k++){
				layers[i].neuronList[j].incomingWeights[k] = randomNumber();
			//	layers[i].neuronList[j].incomingWeights[k] = i+j+k/3;
				cout<<layers[i].neuronList[j].incomingWeights[k]<<" ";
			}
			cout<<"			";
		}
		cout<<endl;
	}	
	cout<<"#####################################################################\n";
	cout<<endl<<endl;

// Only this piece of code is dependent on the fact we are doing it for XOR, rest of the code is generic, i.e. for different functions only this portion(generating target output) will change
/////////////////////////////////////////////////////////////////////	
	pattern = generate(5);

	// compute target output vector
	targetOutput.resize(pattern.size());
	for(int i=0;i<pattern.size();i++){
		if(isPalindrome(pattern[i])){
			targetOutput[i] = 1;
//			print(pattern[i]);
		}
		else{
			targetOutput[i] = 0;
		}
		
	}
//	exit(0);
/////////////////////////////////////////////////////////////////////
	long double diff;
	double time_sec, time_usec;
	struct timeval tm;
	gettimeofday(&tm, NULL);
	time_sec = tm.tv_sec;
	time_usec = tm.tv_usec;
	//----------------------
	ffnn(pattern, layers, targetOutput, learningRate, threshold);
	//----------------------
	gettimeofday(&tm, NULL);
	time_sec = tm.tv_sec - time_sec;
	time_usec = tm.tv_usec - time_usec;
	diff = (time_sec * 1000000) + time_usec;
	
	cout<<"#####################################################################";
	cout<<"Time taken for convergence is "<<diff<<" microseconds"<<endl<<endl<<endl;
	cout<<"#####################################################################\n";
	cout<<endl<<endl<<endl;
	/*
	//Printing final weights
	for(int i=0;i<numLayers-1;i++){
		for(int j=0;j<numNeuronsEachLayer[i];j++){
			for(int k=0;k<layers[i].neuronList[j].incomingWeights.size();k++){
				cout<<layers[i].neuronList[j].incomingWeights[k]<<" ";
			}
			cout<<"			";
		}
		cout<<endl;
	}	
	cout<<"#####################################################################\n";
	cout<<endl<<endl;
	*/
	vector<int> inputPattern(layers[layers.size() - 1].neuronList.size());
	while(true){
		cout<<"Enter the pattern that you want to test\n";
		for(int i =0;i<	inputPattern.size();i++){
			cin>>inputPattern[i];
		}
	
		for(int j=0;j<layers[layers.size() - 1].neuronList.size();j++)
		{
			layers[layers.size()-1].neuronList[j].output=inputPattern[j];		// for the lowermost level, i.e. input layer, the input itself will be the output as well			
		}
	
		//Bottom-Up
		for(int j=layers.size()-2;j>=0;j--)	//Since lowest level is input junction
		{
			for(int k=0;k<layers[j].neuronList.size();k++)
			{
				layers[j].neuronList[k].output=compute_output(k, j, layers);	//k is the neuron at which we are computing the output and j is the layer in which that neuron belongs
			}
		}
	
		for(int i=0;i<layers[0].neuronList.size();i++){
			cout<<"Output i is ";
			if(layers[0].neuronList[i].output>upperMark){
				cout<<"1\n";
			}
			else if(layers[0].neuronList[i].output<lowerMark){
				cout<<"0\n";
			}
			else{
				cout<<"Cannot determine the output\n";
			}
			cout<<layers[0].neuronList[i].output<<endl;
		}
		
# if 0
		cout<<"#####################################################################\n";
		cout<<endl<<endl<<endl;
		//Printing final weights
		for(int i=0;i<numLayers-1;i++){
			for(int j=0;j<numNeuronsEachLayer[i];j++){
				for(int k=0;k<layers[i].neuronList[j].incomingWeights.size();k++){
					cout<<layers[i].neuronList[j].incomingWeights[k]<<" ";
				}
				cout<<"			";
			}
			cout<<endl;
		}	
		cout<<"#####################################################################\n";
		cout<<endl<<endl;		
# endif
		
	}
	return 0;
}

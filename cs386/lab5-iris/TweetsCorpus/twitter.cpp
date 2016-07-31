// This implementation is for 2-input XOR, we will implement the general case later on

#include<iostream>
#include<vector>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string>
#include<string.h>
#include<map>
#include<stdlib.h>
#include<fstream>
using namespace std;

// in our code, the outermost layer will be 0, i.e. layers with smaller index are higher in the neural network

class Neuron{
	
	public:
	vector<double> previousDeltaW;
	vector<double> incomingWeights;			// stores the weights of all the incoming edges to this neuron
											// will store the weight for dummy neuron(which will always be -1) also
	vector<double> incomingDeltaW;			// this is for stroring the value of all the delta W's for all the incoming edges on this neuron
	double output;							// stores the output of this neuron
	double deltaValue;						// stores the delta value of this neuron
};

class Layer{
	public:
	vector<Neuron> neuronList;				// each layer has many neurons in it which are stored in this vector
};

vector<string> parseLine(string line);

bool isNumber( string word) 
{
	bool isDigit = true;
	for(int i=0; i<word.size(); i++){
		int a = word[i];
		if( a < 48 || a > 57) {isDigit = false; break;} 
	}
	return isDigit;
}

string convertToLowerCase( string word)
{
	for(int i=0; i<word.size(); i++){
		if( (int) word[i] >= 65 && (int) word[i] <= 90)
		{
			word[i] += 32;
		}
	}
	return word;
}

double dotProduct( vector <double> v1, vector <double> v2){
	double answer=0;
	for(int i=0;i< v1.size(); i++)
		answer+= v1[i]*v2[i];
	return answer;
}

// negates a vector
vector <double> negation( vector <double> v){
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
	int temp = (rand() %11) + 1;
	return (temp - 6.0);
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
	// go to one lower layer( higher index), see its output and compute the dot product of these outputs with the incoming weights for the given neuron, then the simoid of this value is returned
	vector<double> inputs;
	// first is -1 by default
	inputs.push_back(-1);
	for(int i =0;i<layer[layerNo+1].neuronList.size();i++){
		inputs.push_back(layer[layerNo+1].neuronList[i].output);
	}
	return sigmoid(dotProduct(inputs,layer[layerNo].neuronList[posNeuron].incomingWeights) );	
}

// returns the delta value(delta j) for that neuron
double compute_delta(int posNeuron, int layerNo, vector<Layer> & layer, vector< vector<double> > & targetOutput, int patternIndex){
	double target_output, neuronOutput; 	
	target_output = targetOutput[patternIndex][posNeuron];
	neuronOutput = layer[layerNo].neuronList[posNeuron].output;
	if(layerNo == 0){
		// (t-o)*o*(1-o)
		return ( (target_output-neuronOutput) *(neuronOutput) * (1 - neuronOutput) );
	}
	else{
		// if it is not the outermost layer, then we will have to use the delta values of upper layer with the edge weights
		// here we are assuming that, if we are calculating this for any layer, then delta values for all the layers above it has already been calculated and stored in it 
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
long int ffnn(vector < vector <double> > & pattern, vector<Layer> & l,vector<vector <double> >& output, double eta, double threshold, double momentumFactor)
{
	long int noIterations = 0;
	int itr=pattern.size();	//no. of patterns
	int levels=l.size();	//No. of layers
	double E;
		
	int index=0;		//maintain the index of the pattern for which we're improving the weight after checking E
	
	int i,j,k,res;
	while(true)
	{
		noIterations++;
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
			// here we will compute the output for all the neurons and store them in the neurons
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
				E+=0.5*(output[i][k]-l[0].neuronList[k].output)*(output[i][k]-l[0].neuronList[k].output);
				
		}
		cout<<"Value of E is "<<E<<endl;
		//If error is desirable then we break from while loop()
		if(E<=threshold)
		{
			return noIterations;	
		}
		
		//When error is not desirable, i.e. higher then threshold
		else
		{
			//Calculating output for a particular pattern with index
			//Set output of lowermost level
			for(j=0;j<l[levels-1].neuronList.size();j++)
			{
				l[levels-1].neuronList[j].output=pattern[index][j];				// for lowermost level, i.e. input layer, the input will be th output itself
			}
			
			//Bottom-Up
			// computing the output for all the neurons except in input layer for the given pattern
			for(j=levels-2;j>=0;j--)	//Since lowest level is input junction
			{
				for(k=0;k<l[j].neuronList.size();k++)
				{
					l[j].neuronList[k].output=compute_output(k, j, l);	//k is the neuron at which we are computing the output and j is the layer in which that neuron belongs
				}
			}
			
			//Traversing each layer from top to bottom
			// computing delta value and storing them in neurons
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
					
						l[j].neuronList[k].previousDeltaW[i] = l[j].neuronList[k].incomingDeltaW[i];
						
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
						l[j].neuronList[k].incomingWeights[i]+=l[j].neuronList[k].incomingDeltaW[i] + (momentumFactor * l[j].neuronList[k].previousDeltaW[i]);
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

	vector<Layer> layers;				// stores the layers
	double E, learningRate, lowerMark=0.1, upperMark=0.9, momentumFactor;
	double threshold;					// error percentage entered by user is stored in it							
	int numLayers;
	vector<vector <double> > pattern;	// stores all the patterns on which we will train the neural network
	vector<vector<double> > targetOutput;		// stores the output for the patterns in "pattern" vector
	vector<int> numNeuronsEachLayer;			// it will be resized to numLayers
	
// constructing a map which stores string with their index 
/////////////////////////////////////////////////////////
	int index=1;
	map<string, int> input;
	fstream fp;
	string str;
	fp.open("words");
	if(fp.is_open())
	{
		while(getline(fp, str) )
		{
			if(input[str] == 0)
			{
				input[str] = index++;
			}
			else
			{
				cout<<str<<" is already present\n";
			}
		}
	}
	fp.close();
	index--;
	
////////////////////////////////////////////////////////
	cout<<"The size of feature vector is "<<index<<endl;
	cout<<"Enter the no. of Layers\n";
	cin>>numLayers;
	layers.resize(numLayers);
	numNeuronsEachLayer.resize(numLayers);
	cout<<"Enter the no. of neurons in each layer\n";
	for(int i=0;i<numLayers;i++){
		cin>>numNeuronsEachLayer[i];
	}
	
	// Resizing all the necessary vectors
	for(int i=0;i<numLayers;i++){
		layers[i].neuronList.resize(numNeuronsEachLayer[i]);			// setting the size of the neuronlist of each layer equal to the value specified by the user
	}
	
	for(int i=0;i<numLayers-1;i++){
		for(int j=0;j<numNeuronsEachLayer[i];j++){
			layers[i].neuronList[j].incomingWeights.resize(numNeuronsEachLayer[i+1]+1);
			layers[i].neuronList[j].previousDeltaW.resize(numNeuronsEachLayer[i+1]+1);
			layers[i].neuronList[j].incomingDeltaW.resize(numNeuronsEachLayer[i+1]+1);
		}
	}
	// Resizing done	

	vector<double> featureVector(index, 0);


// For positive tweets
//###############################################################
	//cout<<"Enter the file name for positive tweets\n";
	//cin>>str;
	str = "twitter_positive";
	
	fp.open(str.c_str());
	
	int count = 0;
	vector<double> outputPositive;
	outputPositive.push_back(1);
	outputPositive.push_back(0);	
	outputPositive.push_back(0);		
	if(fp.is_open())
	{
		while(getline(fp, str))
		{
			// Parse str and break it in words, let vector<string> vec stores it		
			vector<string> vec = parseLine(str);
			map<string,int>::iterator it;
			for(int i =0;i<vec.size();i++)
			{
				it = input.find(vec[i]);
				if(it!=input.end() )
				{
					featureVector[(*it).second - 1] = 1;
				}
			}
			pattern.push_back(featureVector);
			targetOutput.push_back(outputPositive);	
			featureVector.assign(index, 0);			// to make all elements 0	
/*
			count++;
			if(count>=50)
			{
				count = 0;
				break;
			}
*/			
		}
	}
	// so now the feature vector has the complete values
	
	fp.close();
//######################################################################
	
	
// For negative tweets
//###############################################################
	//cout<<"Enter the file name for negative tweets\n";
	//cin>>str;
	str = "twitter_negative";
	
	fp.open(str.c_str());
	
	// read all the sentences, and then train on them

	vector<double> outputNegative;
	outputNegative.push_back(0);
	outputNegative.push_back(1);	
	outputNegative.push_back(0);		
	if(fp.is_open())
	{
		while(getline(fp, str))
		{
			// Parse str and break it in words, let vector<string> vec stores it		
			vector<string> vec = parseLine(str);
			map<string,int>::iterator it;	
			for(int i =0;i<vec.size();i++)
			{
				it = input.find(vec[i]);
				if(it!=input.end() )
				{
					featureVector[(*it).second - 1] = 1;
				}
			}
			pattern.push_back(featureVector);
			targetOutput.push_back(outputNegative);	
			featureVector.assign(index, 0);			// to make all elements 0	
/*
			count++;
			if(count>=50)
			{
				count = 0;
				break;
			}
*/
		}
	}
	// so now the feature vector has the complete values
	
	fp.close();
//######################################################################

// For objective(neutral) tweets
//###############################################################
	//cout<<"Enter the file name for objective tweets\n";
	//cin>>str;
	
	str = "twitter_objective";
	
	fp.open(str.c_str());
	
	// read all the sentences, and then train on them

	vector<double> outputNeutral;
	outputNeutral.push_back(0);
	outputNeutral.push_back(0);	
	outputNeutral.push_back(1);		
	if(fp.is_open())
	{
		while(getline(fp, str))
		{
			// Parse str and break it in words, let vector<string> vec stores it		
			vector<string> vec = parseLine(str);
			map<string,int>::iterator it;	
			for(int i =0;i<vec.size();i++)
			{
				it = input.find(vec[i]);
				if(it!=input.end() )
				{
					featureVector[(*it).second - 1] = 1;
				}
			}
			pattern.push_back(featureVector);
			targetOutput.push_back(outputNeutral);	
			featureVector.assign(index, 0);			// to make all elements 0	
/*
			count++;
			if(count>=50)
			{
				count = 0;
				break;
			}
*/
		}
	}
	// so now the feature vector has the complete values
	
	fp.close();
//######################################################################
	cout<<"Size of target output is "<<targetOutput.size()<<endl;
	cout<<"pattern and targetOutput computed\n\n";
	
// So now pattern and output has been calculated, now 

	threshold = 5;
	momentumFactor = 0.0;
	cout<<"Enter learning rate\n";
	cin>>learningRate;
	//learningRate = 0.6;
	threshold = ((double)numNeuronsEachLayer[0]*threshold)/100.0;
	for(int i=0;i<numLayers-1;i++){
		for(int j=0;j<numNeuronsEachLayer[i];j++){
			for(int k=0;k<layers[i].neuronList[j].incomingWeights.size();k++){
				layers[i].neuronList[j].incomingWeights[k] = randomNumber();
			//	layers[i].neuronList[j].incomingWeights[k] = (i+j+k)/3;
				layers[i].neuronList[j].previousDeltaW[k] = 0;
				layers[i].neuronList[j].incomingDeltaW[k] = 0;
			}
		}
	}	
	
	cout<<"Random weights assigned\n";
	cout<<"Now calling function ffnn\n\n";
	
	long int noIterations = ffnn(pattern, layers, targetOutput, learningRate, threshold, momentumFactor);
	cout<<threshold<<","<<noIterations<<endl;
	
	
// Now ask the user to enter inputs and test it
	return 0;
}

// Parse line function
///////////////////////////////////////////////////////////////////////////////////

vector<string> parseLine(string line)
{
	vector<string> wordList;			
	int pos = line.find("\t");
	string words = line.substr(pos + 1, line.size() - pos - 1);
	char cwords [ words.size() + 1];
	strcpy(cwords, words.c_str());
	
	// get all words in line (separated by space)
	const char * p;
	for(p = strtok(cwords, " ") ; p ; p = strtok(NULL,  " "))
	{
		string word = (string) p;
		word = convertToLowerCase(word);

		while(true) 
		{
			if(word.length() == 0)
			{
				break;
			}
			// remove chars such as ? , . :   at start and end
			int last = word.size()-1;
			if(word[0] == '?' || word[0] == '.' || word[0] == ',' || word[0] == ';' ||
			word[0] == '\"' || word[0] == '\'' || word[0] == '(' || word[0] == ')' || word[0] == '[' || word[0] == ']' || word[0] == '_' || word[0] == '!' || word[0] == '-' || word[0] == ':' || word[0] == '=' || word[0] == '|' || word[0] == '&')
				word.erase(0,1);
			else if (word[last] == '?' || word[last] == '.' || word[last] == ',' || word[last] == ';' ||
			word[last] == '\"' || word[last] == '\'' || word[last] == '\n' || word[last] == '(' || word[last] == ')' || word[last] == '[' || word[last] == ']' || word[last] == '_' || word[last] == '!' || word[last] == '-' || word[last] == ':' || word[last] == '=' || word[last] == '|' || word[last] == '&')
				word.erase(last,1);
			else
				break;		  
	
		}
		
		// remove all occurrences of !, #, _, . (, ), [, ] from the word
		
		
		bool pushInVector = true;

		if(word.empty()) pushInVector = false; // sring is now empty
		// don't put certain common words, symbols, numbers in the vector of words
		if( 	word[0] == '@' || word[0] == '#') pushInVector = false;
		
		if( 	pushInVector && (word.size() > 5 && !word.compare(0,5,"http:"))) pushInVector = false;
		
		if (	pushInVector && (!(word.compare("?")) || !(word.compare(",")) ||
			!(word.compare(".")) || !(word.compare(";")) || !(word.compare("'")) || !(word.compare("*"))
			|| !(word.compare("the")) || !(word.compare("is")) || !(word.compare("a"))
			|| !(word.compare("an")) || !(word.compare("this")) || !(word.compare("that"))
			|| !(word.compare("are")) || !(word.compare("my")) 
			|| !(word.compare("with")) || !(word.compare("i'm")) || !(word.compare("he"))	
			|| !(word.compare("she")) || !(word.compare("seen")) || !(word.compare("of"))
			|| !(word.compare("our")) || !(word.compare("was")) || !(word.compare("am"))
			|| !(word.compare("was")) || !(word.compare("to")) || !(word.compare("me"))
			|| !(word.compare("for")) || !(word.compare("from")) || !(word.compare("has"))
			|| !(word.compare("have")) || !(word.compare("had")) || !(word.compare("it"))
			|| !(word.compare("be")) || !(word.compare("you"))
			|| !(word.compare("you'll")) || !(word.compare("and")) || !(word.compare("or"))
			|| !(word.compare("been")) || !(word.compare("must")) || !(word.compare("might"))
			|| !(word.compare("may")) || !(word.compare("would")) || !(word.compare("should"))
			|| !(word.compare("does")) || !(word.compare("do")) || !(word.compare("will"))
			|| !(word.compare("shall")) || !(word.compare("can"))
		)
			) 
			pushInVector = false;
		
		// add other words as well, which you want not to present in the file
			
		if(pushInVector && isNumber(word)) pushInVector = false;

		if(pushInVector) 
		{
			// put the word in vector, first convert to lowercase
			wordList.push_back(word);
		}	
	}
	return wordList;
}

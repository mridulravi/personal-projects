// This implementation is iris dataset

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
map<string, int> stop_words;

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

double dotProduct( vector <double> & v1, vector <double> & v2){
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


double randomNumber(){
	int temp = (rand() %10) + 1;				// generates a random number between 1 and 10
	//return ((temp/2.5) - 2);
	//return ((temp/10.0) - 0.5);
	return ((temp/20.0) - 0.25);
}

double randomNeighbour()
{
	int temp = (rand() % 10) + 1;
	//return ((temp/
	return 0.0;
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
			Neuron myNode = layer[layerNo-1].neuronList[i];
			//temp += layer[layerNo-1].neuronList[i].incomingWeights[posNeuron+1] * layer[layerNo-1].neuronList[i].deltaValue;
			temp += myNode.incomingWeights[posNeuron+1] * myNode.deltaValue;
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
	
	int lastIndex = -1;
	int countIndex = 0;	
	
	bool reset = false;
	
	int i,j,k,res;
	while(true)
	{
		reset = false;
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
				
			if( E > threshold)
			{
				cout<<"No of patterns iterated on "<<i<<"	error:"<<E<<endl;
				break;
			
			}	
			
/*			if(E > threshold)
			{	
				cout<<"No of patterns iterated on "<<i<<"	error:"<<E<<endl;
				
				if(lastIndex == i )
				{
					countIndex++;
				}
				else
				{
					lastIndex = i;
					countIndex = 0;
				}
			
				if(countIndex > 16000)
				{
					lastIndex = -1;
					countIndex = 0;
					
					cout<<"\n\n\nReseting weights\n\n\n";
					
					// randomize weights now and start again
					reset = true;
					
					for(int i=0;i<l.size() - 1;i++){
						for(int j=0;j<l[i].neuronList.size();j++){
							for(int k=0;k<l[i].neuronList[j].incomingWeights.size();k++){
								l[i].neuronList[j].incomingWeights[k] = randomNumber();
							//	layers[i].neuronList[j].incomingWeights[k] = (i+j+k)/3;
								l[i].neuronList[j].previousDeltaW[k] = 0;
								l[i].neuronList[j].incomingDeltaW[k] = 0;
							}
						}
					}	
				}
			
				break;
			}		
*/		
		}
		//cout<<"Value of E is "<<E<<endl;
		//If error is desirable then we break from while loop()
		
		if(reset)
		{
			continue;
		}
		
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
	double E, learningRate, lowerMark=0.2, upperMark=0.8, momentumFactor;
	double threshold;					// error percentage entered by user is stored in it							
	int numLayers;
	vector<vector <double> > pattern;	// stores all the patterns on which we will train the neural network
	vector<vector<double> > targetOutput;		// stores the output for the patterns in "pattern" vector
	vector<int> numNeuronsEachLayer;			// it will be resized to numLayers

////////////////////////////////////////////////////////
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

	string str;
	fstream fp;
	vector<double> featureVector(4);;

// For iris-setosa
//###############################################################
	cout<<"Enter data file\n";
	cin >> str;
	//str = "iris.data3";
	
	int count_s = 0;
	int count_vc = 0;
	int count_vi = 0;
	fp.open(str.c_str());
	
	int countLine = 0;
	string delimiter = ",";
	
	vector<double> outputSetosa, outputVersicolor, outputVirginica;
	outputSetosa.push_back(1);
	outputSetosa.push_back(0);	
	outputSetosa.push_back(0);
	outputVersicolor.push_back(0);
	outputVersicolor.push_back(1);
	outputVersicolor.push_back(0);		
	outputVirginica.push_back(0);
	outputVirginica.push_back(0);
	outputVirginica.push_back(1);		
	if(fp.is_open())
	{
		while(getline(fp, str))
		{
			countLine++;
			// read each line, break it by "," and push it in the feature vector
			
			int pos;
			int count = 0;
			while( (pos = str.find(delimiter)) != string::npos)
			{
				string temp = str.substr(0, pos);
				featureVector[count] = atof(temp.c_str() );
				str.erase(0, pos + delimiter.length() );
				count++;
				if(count >=4)
				{
					break;
				}
			}
			//print(featureVector);
			pattern.push_back(featureVector);
			if(str == "Iris-setosa")
			{
				targetOutput.push_back(outputSetosa);
				count_s++;
			}
			else if(str == "Iris-versicolor")
			{
				targetOutput.push_back(outputVersicolor);
				count_vc++;
			}
			else if(str == "Iris-virginica")
			{
				targetOutput.push_back(outputVirginica);
				count_vi++;
			}
		}
	}
	
	fp.close();
//######################################################################

	cout <<"Number of Setosa inputs "<<count_s<<endl;	
	cout <<"Number of Versi-color inputs "<<count_vc<<endl;
	cout <<"Number of Virginica inputs "<<count_vi<<endl;
	
//######################################################################
	cout<<"Size of target output is "<<targetOutput.size()<<endl;
	cout<<"pattern and targetOutput computed\n\n";
	
// So now pattern and output has been calculated, now 

	cout<<"Enter threshold\n";
	cin>>threshold;
	//threshold = 5;
	cout<<"Enter momentum factor \n";
	cin >> momentumFactor;
//	momentumFactor = 0.0;
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
	cout<<"Threshold is: "<<threshold<<", No of Iterations:"<<noIterations<<endl;

////////////////////////////////////////////////////////////////////////////
// Now measure accuracy

// open iris.check file and measure accuracy
	cout<<"Enter check file\n";
	cin >> str;
//	str = "iris.check3";
	fp.open(str.c_str());
	
	countLine = 0;
	int correct = 0;
	
	if(fp.is_open() )
	{
		while(getline(fp, str) )
		{
			countLine++;
			// read each line, break it by "," and push it in the feature vector
			
			int pos;
			int count = 0;
			while( (pos = str.find(delimiter)) != string::npos)
			{
				string temp = str.substr(0, pos);
				featureVector[count] = atof(temp.c_str() );
				str.erase(0, pos + delimiter.length() );
				count++;
				if(count >=4)
				{
					break;
				}
			}
			
			// now compute output
			
			// for numLayers - 1th layer, the input will be the output
			
			for( int j = 0; j < layers[numLayers - 1].neuronList.size();j++)
			{
				// now here the input will be the output as well
				layers[numLayers - 1].neuronList[j].output = featureVector[j];
			}
			
			for(int i = numLayers - 2;i>=0;i--)				// this will loop over all the layers
			{
				for(int j = 0;j<layers[i].neuronList.size();j++)		// loop over neurons in a layer
				{
					layers[i].neuronList[j].output = compute_output(j, i, layers);
				}
			}
			
			// so now we have the output with us

			double temp1 = layers[0].neuronList[0].output;
			double temp2 = layers[0].neuronList[1].output;
			double temp3 = layers[0].neuronList[2].output;
			
			if(temp1 >= temp2 && temp1 >=temp3)
			{
				if(countLine<=10)
				{
					correct++;
				}
				
			}
			else if(temp2>=temp1 && temp2 >= temp3)
			{
				if(countLine<=20 && countLine>10)
				{
					correct++;
				}
			}
			else
			{
				if(countLine>20)
				{
					correct++;
				}
			}

		}
	}

	cout<<"Accuracy is "<<(double) correct / 30.0 << endl;

	fp.close();

	return 0;
}

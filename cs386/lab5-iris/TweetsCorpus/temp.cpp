#include<iostream>
#include<map>
#include<string>
#include<fstream>
using namespace std;

int main()
{
	int index=1;
	map<string, int> input;
	fstream fp;
	string str;
	fp.open("my_positive");
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

	fp.open("my_negative");
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

	fp.open("my_objective");
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
	
	cout<<"The size of input is "<<input.size()<<" : "<<index<<endl;
	
	// so now i have all the words, assume that they are distinct( i have ensured this)
	// so now my feature vector is complete
	
	
	// so now read a sentence, find the index of it in vector, reduce it by 1 and that is its position in feature vector
	//
	
	vector<int> featureVector(index, 0);
	//	featureVector.resize(index);

	// now read a sentence and parse it
	// suppose that the parsing function is there

// For positive tweets
//###############################################################
	cout<<"Enter the file name for positive tweets\n";
	cin>>str;
	
	fp.open(str.c_str());
	
	vector< vector<int> > pattern;
	vector< <vector<int> > targetOutput;
	// read all the sentences, and then train on them

	vector<int> outputPositive;
	outputPositive.push_back(1);
	outputPositive.push_back(0);	
	outputPositive.push_back(0);		
	if(fp.is_open())
	{
		while(getline(fp, str)
		{
			// Parse str and break it in words, let vector<string> vec stores it		
			vector<string> vec;
			map<string,int>::iterator it;	
			for(int i =0;i<vec.size();i++)
			{
				it = input.find(vec[i]);
				if(it!=input::end() )
				{
					featureVector[(*it).second - 1] = 1;
				}
			}
			patten.push_back(featureVector);
			targetOutput.push_back(outputPositive);	
			featureVector.assign(index, 0);			// to make all elements 0	
		}
	}
	// so now the feature vector has the complete values
	
	fp.close();
//######################################################################
	
	
// For negative tweets
//###############################################################
	cout<<"Enter the file name for negative tweets\n";
	cin>>str;
	
	fp.open(str.c_str());
	
	// read all the sentences, and then train on them

	vector<int> outputNegative;
	outputNegative.push_back(0);
	outputNegative.push_back(1);	
	outputNegative.push_back(0);		
	if(fp.is_open())
	{
		while(getline(fp, str)
		{
			// Parse str and break it in words, let vector<string> vec stores it		
			vector<string> vec;
			map<string,int>::iterator it;	
			for(int i =0;i<vec.size();i++)
			{
				it = input.find(vec[i]);
				if(it!=input::end() )
				{
					featureVector[(*it).second - 1] = 1;
				}
			}
			patten.push_back(featureVector);
			targetOutput.push_back(outputNegative);	
			featureVector.assign(index, 0);			// to make all elements 0	
		}
	}
	// so now the feature vector has the complete values
	
	fp.close();
//######################################################################

// For objective(neutral) tweets
//###############################################################
	cout<<"Enter the file name for objective tweets\n";
	cin>>str;
	
	fp.open(str.c_str());
	
	// read all the sentences, and then train on them

	vector<int> outputNeutral;
	outputNeutral.push_back(0);
	outputNeutral.push_back(0);	
	outputNeutral.push_back(1);		
	if(fp.is_open())
	{
		while(getline(fp, str)
		{
			// Parse str and break it in words, let vector<string> vec stores it		
			vector<string> vec;
			map<string,int>::iterator it;	
			for(int i =0;i<vec.size();i++)
			{
				it = input.find(vec[i]);
				if(it!=input::end() )
				{
					featureVector[(*it).second - 1] = 1;
				}
			}
			patten.push_back(featureVector);
			targetOutput.push_back(outputNeutral);	
			featureVector.assign(index, 0);			// to make all elements 0	
		}
	}
	// so now the feature vector has the complete values
	
	fp.close();
//######################################################################
	
// so now we have the patterns and the target output with us

// run ffnn

// now ask the user to enter tweets, and show them the output
	
	return 0;
}

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;
vector<string> wordList; // will store all the words from all the tweets in corpus

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

void insertWordsFromFileInVector(string filename)
{	
	ifstream file (filename.c_str());
	string line;
	if(file.is_open()){
		while(getline (file, line))
		{	
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
					word[last] == '\"' || word[last] == '\'' || word[last] == '\n' || word[last] == '(' || word[last] == ')' || word[last] == '[' || word[last] == ']' || word[last] == '_' || word[last] == '!' || word[last] == '-' || word[last] == ':' || word[last] == '=' || word[last] == '|' || word[last] == '&' )
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
					|| !(word.compare("were")) || !(word.compare("to")) || !(word.compare("me"))
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
		}
		file.close();
	}	
}

int main(){
	insertWordsFromFileInVector("twitter_positive");
	insertWordsFromFileInVector("twitter_negative");
	insertWordsFromFileInVector("twitter_objective");
	//cout<<endl <<endl;
	//cout<<	wordList.size() <<endl;
	for (int i=0; i<wordList.size(); i++){
		cout<<wordList[i] << "\n";
	}
}

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
using namespace std;

// initially we have 5 input lines in circuit.pl
int main()
{

	int no_of_inputs = 5;
	int val = pow(2, no_of_inputs);

	// We will need an output file which we will use to check the output with

	FILE * file;
	file = fopen("output", "r+");

	if(!file)
	{
		cout << "Cannot open output file\n";
		exit(0);
	}

	for(int i=0;i<val;i++)
	{
		FILE * fp;
		fp = fopen("circuit.pl", "r+");

		if(!fp)
		{
			cout << "File cannot be opened\n";
			exit(1);
		}

		// Now modify the first 5 lines of circuit.pl

		int inputs[no_of_inputs];
		int k=1;
		for(int j = no_of_inputs-1;j>=0;j--)
		{
//			cout << "i && k " << (i & k) << endl;
			inputs[j] = (i & k);
			if(inputs[j]!=0)
			{
				inputs[j] = 1;
			}
//			cout << j << "\t" << inputs[j]<<endl;
			k = k << 1;
//			cout << " k after shifting is " << k << endl;
		}
		
		// Now we have x1 in no_of_inputs[0] and so on
		
		// Now update in circuit.pl
		
		for(int k = 0;k<no_of_inputs;k++)
		{
			char buf[20];
			bzero(buf, 20);
			sprintf(buf, "signal(x%d, %d).\n",k+1,inputs[k]);  
//			cout << buf << endl;
			// Now buf has the required string
			fwrite(buf, 1, 15, fp);
		}
		
		fclose(fp);				// closing file
		
		// this is to run the query and store its output in a.txt file
		
		char buf[200];
		bzero(buf, 100);
		
		sprintf(buf, "swipl -q -s circuit.pl -g \"signal(x%d, A),open('a.txt', write, File), write(File, A), close(File).\" -t halt", no_of_inputs+1);

		system(buf);
		
//		system("swipl -q -s circuit.pl -g \"signal(x6, A),open('a.txt', write, File), write(File, A), close(File).\" -t halt");
		
		// Now a.txt file has the final value, check it with our output 

		char desired_output[2];
		bzero(desired_output, 2);
		fgets(desired_output, 10, file);

		// Open a.txt
		FILE * fp1;
		fp1 = fopen("a.txt", "r+");
		
		if(!fp1)
		{
			cout << "Cannot open a.txt\n";
			exit(1);
		}
		
		char output[2];
		bzero(output, 2);
		fgets(output, 2, fp1);
		int a1 = (int)desired_output[0];
		int a2 = (int)output[0];
		
//		cout << "a1 is " << a1 << endl;
//		cout << "a2 is " << a2 << endl;
		if(a1!=a2)
		{
			cout << a1 << "\t" << a2 << endl;
			cout << "The output does not match for value of i: " << i << "\n";
			exit(0);
		}
		
		fclose(fp1);
	}
	fclose(file);
	return 0;
}

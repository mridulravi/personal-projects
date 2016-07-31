#include <iostream>
#include <queue>
#include <fstream>

using namespace std;
int main ()
{queue<char> mystack;
 queue<int> mystacki;     			
 queue<int> mystackj; 
 char A[100][100];        			// A->Maze array
 int M[100][100];         			// M->Modified output array
 ofstream fileout;
 fileout.open("traceoutput");
 int N,i,j,flagi=0,flagj=0;
 cin >> N; 
   for (i = 1; i <= N; i++)
 { for (j = 1; j <= N; j++)
   { 
    cin >> A[i][j];
    if (A[i][j]=='0')
       M[i][j]=0;
    else if (A[i][j]=='#')
       M[i][j]=99999;
   }
   cout <<endl;
 }

 i=1;
 j=1;

   if (A[1][1] != '0'|| A[N][N]!='0')                             // Entrance blocked or exit blocked, No Path exits
	{
         fileout<<i<<","<<j<<endl;
         cout<< "No path"<<endl;
  	 fileout.close();
	 return 0;
	}
   if (A[i][j]=='0')
 	{ 
  	 mystack.push(A[i][j]);fileout<<i<<","<<j<<endl;
 	 mystacki.push(i);
 	 mystackj.push(j);
 	 A[1][1]='#';
 	}
while (i<=N && j<=N)                                     // this loop the makes the rat to look for its neighbours, if it is a 0, rat 
 {                                                       // goes to its 0 neighbour position.
	 if(A[i+1][j]=='0' && i<=N-1 && flagi != -1)                            // down neighbour
		{
		 if (i==N && j==N)                   
			{
			 break;
			}
		 else 
			{ 
			 i++;
			 mystack.push(A[i][j]);fileout<<i<<","<<j<<endl;
                	 mystacki.push(i);
			 mystackj.push(j);
			 flagi=1;flagj=0;
			}
		}
	 else if(A[i-1][j]=='0' && i>=2 && flagi != 1) 				// up neighbour
		{
		 if (i==N && j==N)
			{ 
			 break;
			}
		 else 
			{ 
		 	 i--;
		 	 mystack.push(A[i][j]);fileout<<i<<","<<j<<endl;
                	 mystacki.push(i);
			 mystackj.push(j);
			 flagi=-1;flagj=0;
			}
		}
	 else if(A[i][j-1]=='0' && j>=2 && flagj != 1)				// left neighbour
		{
		 if (i==N && j==N)
			{ 
			 break;
			}
		 else 
			{ 
		 	 j--;
		 	 mystack.push(A[i][j]);fileout<<i<<","<<j<<endl;
                	 mystacki.push(i);
			 mystackj.push(j);
			 flagj=-1;flagi=0;
			}
		}
	 else if(A[i][j+1]=='0' && j<=N-1 && flagj != -1)			// right neighbour
		{
		 if (i==N && j==N)
			{ 
			 break;
			}
		 else 
			{ 
			 j++;
		 	 mystack.push(A[i][j]);fileout<<i<<","<<j<<endl;
                	 mystacki.push(i);
			 mystackj.push(j);
			 flagj=1;flagi=0;
			}
		}
         else  						  // if none of the neighbours is 0 rat marks its current position
                {                                         // with # & rat goes to (1,1) position.
		 if (i==N && j==N)
			{ 
			 break;
			}
		 else 
			{
			A[i][j]='#';
			i=1; 
			j=1;
   			flagi=0;
			flagj=0;
		        }
		}
 }
 int k=1;
 fileout.close();
 int count = mystack.size();
  while (!mystack.empty())				// this creates the output maze with path
  {
     i=mystacki.front();
     j=mystackj.front();
     mystacki.pop();
     mystackj.pop();
     mystack.pop();
     M[i][j]=k;
     k++;
  }
 for (i = 1; i <= N; i++)                               // this prints the output maze with path
 { for (j = 1; j <= N; j++)
   { 
    if (M[i][j] != 99999)
  	{	if (M[i][j]/10==0)      
		cout<< M[i][j]<<"  ";
		else if (M[i][j]/10 >=1 && M[i][j]/10 <= 9)
		cout<< M[i][j]<<" ";
		else if (M[i][j]/10 >=10)
		cout<< M[i][j];
	}
    else 
      cout<< '#'<< "  ";
   }
   cout <<endl;
 }

 return 0;
}

































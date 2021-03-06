/*Implementation of rat in a maze through a stack*/

#include <iostream>
#include <stack>
#include <fstream>

using namespace std;
int main ()
{   stack<char> mystack;    			// Stack to keep track of elements visited
    stack<int> mystacki;     			// Stack to keep track of row of the element visited
    stack<int> mystackj;     			// Stack to keep track of column of the element visited
    char A[100][100];        			// A->Maze array
    int M[100][100];         			// M->Modified output array
    ofstream fileout;
    fileout.open("traceoutput");
    int N,i,j;
    cin >> N;                			// N-> Size of maze is N x N

    for (i = 1; i <= N; i++)
    {   for (j = 1; j <= N; j++)
        {
            cin >> A[i][j];
            if (A[i][j]=='0')				// since A is a char array and M is a int array, # in A is replaced by 99999 in M
                M[i][j]=0;
            else if (A[i][j]=='#')
                M[i][j]=99999;
        }
        cout <<endl;
    }

    i=1;
    j=1;

    if (A[1][1] != '0')                             // Entrance blocked, No Path exits
    {
        fileout<<i<<","<<j<<endl;
        cout<< "No path"<<endl;
        fileout.close();
        return 0;
    }

    if (A[i][j]=='0')
    {
        mystack.push(A[i][j]);
        fileout<<i<<","<<j<<endl;
        mystacki.push(i);
        mystackj.push(j);
        A[1][1]='#';
    }

    while (i<=N && j<=N)                                     // this loop the makes the rat to look for its neighbours, if it is a 0, rat
    {   // goes to its 0 neighbour position and makes it #, so as to mark it visited
        if(A[i+1][j]=='0' && i<=N-1)                                    // down neighbour
        {
            if (i==N && j==N)
            {
                break;
            }
            else
            {
                i++;
                mystack.push(A[i][j]);
                fileout<<i<<","<<j<<endl;
                mystacki.push(i);
                mystackj.push(j);
                A[i][j]='#';
            }
        }
        else if(A[i-1][j]=='0' && i>=2) 				// up neighbour
        {
            if (i==N && j==N)
            {
                break;
            }
            else
            {
                i--;
                mystack.push(A[i][j]);
                fileout<<i<<","<<j<<endl;
                mystacki.push(i);
                mystackj.push(j);
                A[i][j]='#';
            }
        }
        else if(A[i][j-1]=='0' && j>=2)				// left neighbour
        {
            if (i==N && j==N)
            {
                break;
            }
            else
            {
                j--;
                mystack.push(A[i][j]);
                fileout<<i<<","<<j<<endl;
                mystacki.push(i);
                mystackj.push(j);
                A[i][j]='#';
            }
        }
        else if(A[i][j+1]=='0' && j<=N-1)				// right neighbour
        {
            if (i==N && j==N)
            {
                break;
            }
            else
            {
                j++;
                mystack.push(A[i][j]);
                fileout<<i<<","<<j<<endl;
                mystacki.push(i);
                mystackj.push(j);
                A[i][j]='#';
            }
        }
        else  					   // if none of the neighbours is 0, popping occurs and rat goes to previous position
        {
            if (i==N && j==N)
            {
                break;
            }
            else
            {
                mystack.pop();
                mystacki.pop();
                mystackj.pop();
                if (!mystacki.empty())
                    i=mystacki.top();
                if (!mystackj.empty())
                    j=mystackj.top();
                if (i==1 && j ==1)              // if popping takes it to enterance of maze then no path exits
                {
                    cout<< "No path"<<endl;
                    fileout.close();
                    return 0;
                }

            }
        }
    }

    fileout.close();
    int count = mystack.size();

    while (!mystack.empty())				// this creates the output maze with path
    {
        i=mystacki.top();
        j=mystackj.top();
        mystacki.pop();
        mystackj.pop();
        mystack.pop();
        M[i][j]=count;
        count--;
    }

    for (i = 1; i <= N; i++)                               // this prints the output maze with path
    {   for (j = 1; j <= N; j++)
        {
            if (M[i][j] != 99999)
            {   if (M[i][j]/10==0)
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
// put your input and output file in checker1 directory and run the checker program using  ./checker input.txt output.txt

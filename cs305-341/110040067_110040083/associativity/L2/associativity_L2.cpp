#include<iostream>
#include<sys/time.h>
using namespace std;

int main(){

	int n=1024*1024;
	int a[n];
	
	for(int i=0;i<n;i++){
		a[i]=2;
	}
	// array populated
	
	int step=1;
	timeval time1, time2;
	long double t1=0.0;
	long int dummy=0;
		
	for(;step<2000;step*=2){
		t1=0.0;
		for(int i=0;i<500;i++){
		
			for(int k=0;k<5000;k++){
				for(int j=64*1024-1;j>=0;j-=16){
					dummy+=a[j];		
				}
			}
			// array accessed so that all the blocks from 1st to 512th are in L1, and 1st to 4096th are in L2
			
			dummy=0;
			int temp=step*16;
			int count=0;
			gettimeofday(&time1, NULL);
			
			// here we are using L1's size and its associativity, which we calculated in part a
			for(int j=512*16;count<40;j+=temp){
				a[j]++;
				count++;
			}
			gettimeofday(&time2,NULL);
			t1 += (time2.tv_sec-time1.tv_sec)*1000000+(time2.tv_usec-time1.tv_usec);
			
		}
		cout<<"step---- "<<step<<" time_per_access----- "<<t1/20000<<endl;
	}
	
	return 0;
}

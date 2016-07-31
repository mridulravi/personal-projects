#include<iostream>
#include<sys/time.h>
using namespace std;

int main(){
	int n=256;
	timeval tim;
	int dummy;
	double t1, t2;
	long double time=0;
	int tmp_index = 0;
	for(int i=0;i<18;i++){
		int a[n];
		for(int j=0;j<n;j++){
			a[j]=j;
		}
		
		long double sum=0;
		
			for(int j=0;j<100000;j++){
				gettimeofday(&tim, NULL);
				t1=tim.tv_sec*1000000+tim.tv_usec;
				
					for(int k=0;k<n;k+=16){
						a[k]=2;
					}
				
				gettimeofday(&tim, NULL);
				t2=tim.tv_sec*1000000+tim.tv_usec;
				sum+=t2-t1;		
			}
		
		time=sum/(n*100000.0/16);
		cout<<"size: "<<n*4/1024<<"KB			time:"<<time<<endl;
		// can output to a csv file for plotting
		
		if(n*4/1024 >= 1024){
			n+=tmp_index;
		}
		else{
			n*=2;
			tmp_index=n;
		}
	}
}


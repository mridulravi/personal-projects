#include<iostream>
#include<sys/time.h>
#include<time.h>
using namespace std;

inline void
clflush(volatile void *p)
{
    asm volatile ("clflush (%0)" :: "r"(p));
}

volatile int a[100];
	
int main(){
	
	int n=100;
	
	
	for(int i=0;i<n;i++){
		a[i]=i;	
	}
	
	int dummy;
	long double t1, t2;
	
	
	// Populating the array
	
	for(int i=0;i<100000;i++){
		for(int j=0;j<n;j++){
			dummy=a[j];
		}
	}
	
	// accessing it multiple times so that whole of the array is in cache
	
	timeval time1, time2;
	int strides=1;
	// first access an element then flush that line and then access element with stride, note the time
	
	for(; strides<=100;strides++){
		t2=0.0;
		
		for(int j=0;j<100000;j++){
			dummy = a[0];		
			clflush(a);
		
			gettimeofday(&time1, NULL);
			dummy = a[strides];
			gettimeofday(&time2, NULL);
			t2+= (time2.tv_sec-time1.tv_sec)*1000000+(time2.tv_usec-time1.tv_usec);		
				
		}
		cout<<strides*4<<" --- "<<t2/100000<<endl;
	}

	return 0;
}

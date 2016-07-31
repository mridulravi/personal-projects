#include<iostream>
#include<sys/time.h>
using namespace std;

int main(){
	timeval time1, time2;
	long double time=0;
	int n= (256+32)*1024/4;

	int a[n];
	for(int i=0;i<n;i++){
		a[i]=2;
	}

	// array created and populated
	
	int strides = 1;
	
	long int sum=0;
	
	for(;strides<=64;strides*=2){
		time=0.0;
		sum=0;
		
		gettimeofday(&time1, NULL);
		for(int i=0;i<n;i+=strides){
			sum = sum+a[i];
		}
		gettimeofday(&time2, NULL);
		
		time=(time2.tv_sec-time1.tv_sec)*1000000+(time2.tv_usec-time1.tv_usec);
		
		cout<<strides*4<<" --- "<<time*strides/n<<endl;
	}

}

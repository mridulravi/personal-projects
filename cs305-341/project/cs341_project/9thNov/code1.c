#include<stdio.h>

void fun(){
	char a[10];
	int i=0;
	char n;
	while(1){
		printf("Enter %d th element :\n",i);
		scanf("%c",&n);
		a[i] = n;
		printf(" %d th element is %c\n", i, a[i]);
		i++;
	}
}

int main(){
	fun();
}

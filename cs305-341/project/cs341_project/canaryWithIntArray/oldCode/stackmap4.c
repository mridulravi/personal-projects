// we will try to make a char array and see if canary comes into picture or not.

void fun1(int a, int b){
	char arr1[10];
}

int main(){
	int y,z;
	y=5;
	z=1;
	fun1(y,z);
} 


// see that for assembly code with char buffer, canary is used .

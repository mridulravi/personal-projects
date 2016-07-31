// want to prove/ disprove the theory that only a fixed number of params can be passed on stack (4)

void fun1(int a, int b, int c, int d, int e){
	int w;
	w=a;
}

int main(){
	int x,y,z;
	x=10;
	y=5;
	z=1;
	fun1(y,z,1,2,3);
}


// we can pass any number of params , but there is always a 1 word gap b/w local variables and params.
// why is this??? what is stored in that 1 word???

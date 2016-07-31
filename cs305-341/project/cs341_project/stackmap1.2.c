//check if sp is dec when no local variables (contd in stackmap 1.3 and 1.4)

void fun(){
	
}

int main(){
	
	fun();
}

// we think that if no var defiend, sp not dec (except when ra or ebp pushed onto stack)

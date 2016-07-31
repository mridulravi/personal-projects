#include <string.h>
#include <stdio.h>
#include <string.h>

char * curr_dir = "~/user/A/B/C/D/E/F/G/H/I/J/K/L";


// This function calculates the absolute_address given the relative_address as argument
// Assuming curr_dir to be given
char* convert_to_absolute_address(char* addr) {
	
	char c[1000];
	strcpy(c, addr);

	// No of ".." in relative_address is the no. of times we have to level_up 
    int level_up = 0;				
    char *tok = strtok(c, ".");
    while (tok != NULL)
    {
        level_up++;
        tok = strtok(NULL, ".");
    }

	// Calculate the depth of our curr_dir : ~/user/a  means  depth 3  
	strcpy(c, curr_dir);
    int depth = 1;
    tok = strtok(c, "/");
    while (tok != NULL)
    {
        depth++;
        tok = strtok(NULL, "/");
    }
    
    
    // Now we start to form the absolute_address by first going level_up upwards
    char dest[1000];
	strcpy(dest,"");
	strcpy(c, curr_dir);
    int up = depth - level_up;
    tok = strtok(c, "/");
    while (up != 1)
    {
        strcat(dest, tok);
        strcat(dest, "/");
        up--;
        tok = strtok(NULL, "/");
    }
    
    // Finally we go downwards in the directory tree
	strcpy(c, addr);
    tok = strtok(c, "./");
    while (tok != NULL)
    {
        strcat(dest, tok);
        strcat(dest, "/");
        tok = strtok(NULL, "./");
    }
    
    
    dest[strlen(dest)-1] = 0; 
    char * new_str = dest;
    return new_str;
}

int main(int argc, char **argv) {

	char * relative_address = "../../../../c/../d";
	char * absolute_address = convert_to_absolute_address(relative_address);
	printf("absolute_address:%s\n",absolute_address);
	return;
}



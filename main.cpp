#include "shorthand.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	shorthand::flag f("abc", argv[1]);
	
	if(f.check('a')){
		printf("You input an a!\n");
	}
	else if(f.check('b') && f.check('c')){
		printf("You input a \"b\" and a \"c\"!\n");
	}
	else if(f.check('c')){
		printf("You input a c!\n");
	}
	else if(f.check('b')){
		printf("You input a b!\n");
	}
	else{
		printf("Not a flag!\n");
	}
	
	
	return 0;
}

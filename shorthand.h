#include <string.h>
#include <stdio.h>

#ifndef SHORTHAND_H 
#define	SHORTHAND_H

namespace shorthand {
/*
*	USAGE: 
* 			shorthand::flag f( [const char*], [char*]);
*			if(f.check('c'))
* 				do c
* 			if ...
* 
* 			First argument is hardcoded and sets the flag list to compare input against. Second argument
* 			is the input using argv[i] or something like that. 
* 
* 	EXAMPLE:
* 
* 			shorthand::flag f("abcd", argv[1])
* 			if(f.check('a'))
* 				do A
* 			else if(f.check('b'))
* 				do B
* 			else if(f.check('c') && f.check('d'))
* 				flag combination "cd" or "dc"
* 			else
* 				no flags input at argv[1]
* ----------------------------------------------------------------------
* 			if argv[i] = "a", f.check('a') will return true,
* 			if it's "b" f.check('b') returns true, and if it's
* 			"c" or "d" in any combination ("cd" or "dc") then 
* 				f.check('c') && f.check('d')
* 			returns true. 
* 
* 			if argv[i] is "abcd", of course, only the first check
* 			will return true because it's an if..else if statement.
* 			
* 			watch out for that.
*/	
		class flag {
			private:
				char const *flag_list; //LIST OF FLAGS
				char *input_list; //USER INPUT TO CHECK
				
				int validate_flags(){
					if(flag_list==0||input_list==0){
						return 0;
					}
					else
						return 1;
				}
				
				int is_in_flag(char c){
					for(int i=0;flag_list[i]!='\0';i++){
						if(c == flag_list[i]){
							return 1;
						}
					}
					return 0;
				}
				
				int is_in_input(char c){
					for(int i=0;input_list[i]!='\0';i++){
						if(c == input_list[i]){
							return 1;
						}
					}
					return 0;
				}
// CONSTRUCTORS --------------------------------------------------------	
			public:				
				flag(){								//defaults to 0
					flag_list = 0;
					input_list = 0;
				}
				flag(char const *flags=0, char* input=0){  	//overloaded to accept initial values
					//printf("%s\n%s\n%s\n", flags, ignore, input);
					if(flags!=0&&input!=0){
						flag_list = flags;
						input_list = input;
					}
					else{
						flag_list = 0;
						input_list = 0;
					}
						
				}
				~flag(){};
// FUNCTIONS -----------------------------------------------------------	

				// finds checks character against lists
				int check(char c=0){
					if(c==0)
						return -1;
					if(validate_flags()){
						if(is_in_flag(c)&&is_in_input(c))
							return 1;
						else
							return 0;
					}
					return -1;
				}
		};
}

#endif

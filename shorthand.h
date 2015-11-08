#include <string>
#include <fstream>
#include <iostream>

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
					if(is_in_flag(c)&&is_in_input(c))
						return 1;
					else
						return 0;
					return -1;
				}
				
				int valid_input(){
					if(flag_list==0||input_list==0){ 			//if both lists are null, return FALSE (no lists)
						return 0;
					}
					else{
						for(int i=0;input_list[i]!='\0';i++){	//for each input char
							if(!is_in_flag(input_list[i]))		//if it's not a char in flag_list
							return 0;							//return FALSE (improper input)
						}
																//otherwise, return TRUE (both list are good)
						return 1;
					}
				}			
		};
		
		class file{
			private:
				class node{
					public:
						node(){ line.clear(); next = NULL;}
						~node(){}
						
						node *next;
						std::string line;
				};
			private:
				node *root;
				
			public:
				//functions to load lines to linked list, manipulate, and save to text files
				file(){root = new node();}
				~file(){}
				
				std::string line(int i){
					node *t = root;
					std::string s;
					for(i;i>0;i--)
						t=t->next;
					if(t!=NULL)
						return t->line;
					else
						return s.erase();
				}
				
				int load(char* s='\0'){
					if(s!='\0'){
						node *t = root;
						std::fstream f;
						std::string l;
						f.open(s, std::fstream::in);
						while(getline(f,l)){
							t->line = l;
							t->next = new node();
							t = t->next;
						}
						f.close();
						return 1;
					}
					return 0;
				}
						
				int save(char* s='\0'){
					if(s!='\0'){
						node *t = root;
						std::fstream f;
						f.open(s, std::fstream::out);
						while(t->next!=NULL){
							f << t->line << std::endl;
							t=t->next;
						}
						f.close();
						return 1;
					}
					return 0;
				}
				
				int print(){
					node *t = root;
					int i=0;
					while(t!=NULL){
						std::cout << i << ": " << t->line << std::endl;
						t = t->next; i++;
					}
					return 1;
				}		
		
				int insert( int i,char* s=0){
					node *t=root;
					node *f;
					if(i!=-1){
						for(int j=0;t->next!=NULL;j++){
							if(j==i&&s!=0){
								f->next = new node();
								f=f->next; 
								std::string k(s);
								f->line = k;			
								f->next = t;
								return 1;
							}
							f=t;
							t=t->next;
						}
					}
					else{
						f = root;
						while(f->next!=NULL)
							f=f->next;
						f->next = new node();
						f=f->next; 
						std::string k(s);
						f->line = k;
					}
				}
				
				int remove(int i){
						node *t=root;
						node *f;
						while(t!=NULL){
							if(i==0&&f!=NULL){
								f->next = t->next;
								delete t;
							}
							else if(f==NULL){
								//root = root->next;
								//f=root;
								//delete f;
							}
								
							f=t;
							t=t->next;
							i--;
						}
				}
				
				
		};
}



#endif

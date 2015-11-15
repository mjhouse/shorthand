#include <fstream>
#include <iostream>

#ifndef SHORTHAND_H 
#define	SHORTHAND_H

namespace sh {
/*
 * 	Flag:
 * 			Handles true/false flag checking against a hardcoded char array of flags.
 * 
 *	USAGE: 
 * 			shorthand::flag f( [const char*], [char*]);
 *			if(f.check('c'))
 * 				do c
 * 			if ...
 * 
 * 			First argument is hardcoded and sets the flag list to compare input against. Second argument
 * 			is the input using argv[i] or something like that. 
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
				flag(char const *flags, char* input){  	//overloaded to accept initial values
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

/*
 * File:
 * 			Less-messy file handling for manipulating text files.
 * 
 * USAGE: 
 * 			create a file object using "shorthand::file f;", and then use f.line(), f.load(), 
 * 			f.save(), f.print(), f.insert() and f.remove() to-
 * 				* return a string from a node
 * 				* load a file into the linked list
 * 				* save the linked list into a text file
 * 				* print the current list with line numbers
 * 				* insert a line
 * 				* and remove a line
 */
 
		class file{
			private:
// NODE ----------------------------------------------------------------
				class node{
					public:
						node(std::string s){ 
							line = s;
							next = NULL;
						}
						~node(){}
						
						node *next;
						std::string line;
						//int flag;
				};
			private:
				node *root;
				
			public:
// CONSTRUCTORS --------------------------------------------------------
				file(){
					root = new node();
				}
				~file(){
					delete root;
				}

				// LINE ------------------------------------------------			
				std::string line(int i=-1){
					std::string err;
					if(i>=0){
						node *t = root;
						for(i;i>0;i--)
							t=t->next;
						if(t!=NULL)
							return t->line;
						else
							return err.erase();
					}
					else
						return err.erase();
				}

				// LOAD ------------------------------------------------
				int load(char* s){
					if(s!=0){
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
				
				// SAVE ------------------------------------------------
				int save(char* s){
					if(s!=0){
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
				
				// PRINT -----------------------------------------------
				int print(){
					node *t = root;
					int i=0;
					while(t!=NULL){
						std::cout << i << ": " << t->line << std::endl;
						t = t->next; i++;
					}
					return 1;
				}		
				
				// INSERT ----------------------------------------------
				int insert( int i, char* s){
					if(i>=0&&s!=0){
						node *t=root; bool eof = false;
						while(i>0){
							if(t->next==NULL){
								t->next = new node();
								eof = true;
							}
							i--;
							t=t->next;
						}
						if(eof){
							std::string k(s); t->line = k;
							return 1;
						}
						else{
							node *j = new node(t->line);
							std::string k(s); t->line = k;
							j->next = t->next;
							t->next = j;
							return 1;
						}
					}
					return 0;
				}
				// SET_FLAG --------------------------------------------
				int set_flag(int f, int linenum){
					node *t=root;
					for(int i=0;t!=NULL;i++){
						if(i==linenum){
							t->flag = f;
							return 1;
						}
						t=t->next;
					}
					return 0;
				}
				// RETURN_FLAG -----------------------------------------
				int return_flag(int linenum){
					node *t=root;
					for(int i=0;t!=NULL;i++){
						if(i==linenum){
							return t->flag;
						}
						t=t->next;
					}
					return 0;
				}
				
				// REMOVE ----------------------------------------------
				int remove(int i){
					if(i>=0){
						node *t=root; node *b=NULL;
						while(i>0){
							if(t==NULL)
								return 0;
							if(i==1)
								b=t;
							i--;
							t=t->next;
						}
						if(t==root){
							root = root->next;
							delete t;
						}
						else{
							b->next = t->next;
							delete t;
						}
					}
					return 0;
				}
		};
}
#endif

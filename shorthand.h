#include <string.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#ifndef SHORTHAND_H 
#define	SHORTHAND_H

namespace shorthand {
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

/*
 * File:
 * 			Less-messy file handling for manipulating text files.
 * 
 * USAGE: 
 * 			create a file object using "shorthand::file f()", and then use f.line(), f.load(), 
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
						node(std::string s = std::string()){ 
							if(!s.empty())
								line = s; 
							else
								line.erase();
							next = NULL;
						}
						~node(){}
						
						node *next;
						std::string line;
				};
			private:
				node *root;
				
			public:
// CONSTRUCTORS --------------------------------------------------------
				file(){root = new node();}
				~file(){}
				
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
				
				// SAVE ------------------------------------------------
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
				int insert( int i=-1, char* s='\0'){
					if(i>0&&s!='\0'){
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
				
				// REMOVE ----------------------------------------------
				int remove(int i=-1){
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

/*
 * 	Exists:
 * 			Simple file existence check. Returns 1 for directory, 0 for file and -1 otherwise.
 * 	USAGE:
 * 			Give it a pathname in a character array (char *)
 */

		int exists(char *filepath){
			if(filepath!='\0'){
				struct stat *buf;
				buf = (struct stat *)malloc(sizeof(struct stat));
				
				if(stat(filepath,buf)==0){
					if(buf->st_size>0){
						if(S_ISDIR(buf->st_mode)){
							free(buf);
							return 1;
						}
						else if(S_ISREG(buf->st_mode)){
							free(buf);
							return 0;
						}
						else{
							free(buf);
							return -1;
						}
					}
					else{
						free(buf);
						return -1;
					}
				}
				free(buf);
				return -1;
			}
			else
				return -1;
		}

/*
 *	Copy:
 * 			recursively copies a directory structure to another location, aborts recursion if backup
 * 			location is a child of the input location.
 * 
 * 	USAGE:
 * 			first arg is char* to input path (directory to be backed up), second argument is char* to
 * 			output directory (location to copy structur too). 
 */
		
		int copy(char *in, char *out){
			if(exists(in)!=-1&&exists(in)==1&&exists(out)==1){ // both paths have to be dir
				struct dirent *entry;
				DIR *dirp = opendir(in);
				while(entry=readdir(dirp)){
					
					// Copy current path
					char *fp = (char *)malloc(sizeof(in)+sizeof(entry->d_name)+1);
					char *fo = (char *)malloc(sizeof(out)+sizeof(entry->d_name)+1);
					strcpy(fp,in);
					strcpy(fo,out);
					
					// Check for trailing "/" and add it if it's not there
					int j=0;
					for(int i=0;in[i]!='\0';i++)
						if(in[i+1]=='\0') j=i;
					if(fp[j]!='/')
						strcat(fp,"/");
					
					j=0;
					for(int i=0;out[i]!='\0';i++)
						if(out[i+1]=='\0') j=i;
					if(fo[j]!='/')
						strcat(fo,"/");
					
					
					// Add the file name if it isn't ".." or "."
					if(strcmp(entry->d_name, "..")!=0&&strcmp(entry->d_name, ".")!=0){
						strcat(fp, entry->d_name);
						strcat(fo, entry->d_name);
						if(exists(fp)==1){
							// IS DIR: duplicate directory structure at out
							mkdir(fo, 0700);
							if(strncmp(fp,fo,j)!=0){
								printf("DIR: %s\n", fp);
								copy(fp,fo);	
							}
						}
						else if(exists(fp)==0){
							// IS FILE: copy file
							//printf("FILE: %s\n", fp);
							std::ifstream i(fp, std::ios::binary);
							std::ofstream o(fo, std::ios::binary);
							o << i.rdbuf();
							o.close();i.close();
						}
					}
					// free memory allocated to fp
					free(fo);
					free(fp);
				}
				return 1;
			}
			else
				return -1;
		}


/*
 *	TODO:
 * 			1. make a simplified exec function 
 * 			2. make compression function
 * 			3. possibly push copy, exists, compression functions out into different header
 */

}
#endif

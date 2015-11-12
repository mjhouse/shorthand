#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string>

#ifndef UTIL_H
#define UTIL_H

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
		
		int exists(std::string filepath){
			return exists(filepath.c_str());
		}
		
// Findlen: finds length of string -------------------------------------	
		int findlen(char *s){
			for(int i=0;s[i]!=0;i++)
				if(s[i+1]==0) return i;
		}
		
// Last_slash: adds trailing slash -------------------------------------
		int last_slash(char *s){
			int j = findlen(s);
			if(s[j]!='/')
				strcat(s,"/");
			return 0;
		}
// Find_wc: returns word count of string -------------------------------
		int find_wc(char *s){
			int j=0; 
			for(int i=0;s[i]!='\0';i++){
				if(s[i+1]==' '&&s[i]!=' ')
					j++;
				if(s[i+1]=='\0'&&s[i]!=' ')
					j++;
			}
			return j;
		}

#endif

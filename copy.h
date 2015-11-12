#include "util.h"

#include <fstream>
#include <dirent.h>


#ifndef COPY_H
#define COPY_H

namespace sh {

/*
 *	Copy:
 * 			recursively copies a directory structure to another location, aborts recursion if backup
 * 			location is a child of the input location.
 * 
 * 	USAGE:
 * 			first arg is char* to input path (directory to be backed up), second argument is char* to
 * 			output directory (location to copy structur too). 
 */
 
 // COPY ---------------------------------------------------------------
int copy(char* i, char* o){
	char in[findlen(i)+1]; char out[findlen(o)+1];
	strcpy(in,i);
	strcpy(out,o);
	
	
	if(exists(in)==1&&exists(out)==1){ // both paths have to be dir
		struct dirent *entry;
		DIR *dirp = opendir(in);
		while(entry=readdir(dirp)){
			// Copy current path
			char *fp = (char *)malloc(sizeof(in)+sizeof(entry->d_name)+1);
			char *fo = (char *)malloc(sizeof(out)+sizeof(entry->d_name)+1);
			strcpy(fp,in);
			strcpy(fo,out);
			
			// Check for trailing "/" and add it if it's not there
			last_slash(fo);
			last_slash(fp);
			
			// Add the file name if it isn't ".." or "."
			if(strncmp(entry->d_name, ".",1)!=0){
				strcat(fp, entry->d_name);
				strcat(fo, entry->d_name);
				if(exists(fp)==1){
					// IS DIR: duplicate directory structure at out
					mkdir(fo, 0700);
					if(strncmp(fp,fo,findlen(fo))!=0){
						copy(fp,fo);							
					}
				}
				else if(exists(fp)==0){
					// IS FILE: copy file to out
					std::ifstream infile(fp, std::ios::binary);
					std::ofstream outfile(fo, std::ios::binary);
					outfile << infile.rdbuf();
					outfile.close();infile.close();
				}
			}
			// free memory allocated to fp
			free(fo);
			free(fp);
		}
		printf("%s\n",o);
		return 1;
	}
	else
		return -1;
}

// WRAPPERS ------------------------------------------------------------
int copy(std::string a, std::string b){
	return copy(a.c_str(),b.c_str());
}

}
#endif

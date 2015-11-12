#include "util.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef EXEC_H
#define EXEC_H

/*
 *  Exec/Run:
 * 
 * 			Simple wrapper for execvp()+fork() functions basically.
 * 			
 * 	USAGE:
 * 			pass char* or string equal to an executable name (or path to executable) and argv/char* arguments.
 */
 
// RUN ----------------------------------------------------------------
int run(char *s, char* argv[]){
	//EXEC
	pid_t pid = fork();
	if(pid==0){
		//CHILD
		execvp(s,argv);
	}
	else if(pid<0){
		//FAILED: ERROR
		return 0;
	}
	else{
		//PARENT
		int retstat;
		waitpid( pid, &retstat, 0);
		return 1;
	}
	return 0;
}

// EXEC ---------------------------------------------------------------
int exec(char *b, char* argv[]){

	if(exists(b)==-1){		// GO FIND IT
		char* paths = getenv("PATH"); int j=0;
		char p[findlen(paths)+1];
		strcpy(p, paths);
		
		char *tok;
		tok = strtok(p, ":");;
		while(tok!=NULL){
			char s[findlen(tok)+1];
			strcpy(s,tok);
			last_slash(&s[0]);
			strcat(s,b);
			if(exists(s)==0){
				//EXEC
				return run(s,argv);
			}
			tok = strtok( NULL, ":");
		}
		return 0;
	}
	else if(exists(b)==0){
		//EXEC
		return run(b,argv);
	}
	return 0;
}
		
// WRAPPERS ------------------------------------------------------------

// double char overloaded
int exec(char *b, char *c){
	char* args[find_wc(c)+1] = {0};
	char *tok = strtok(c," ");
	for(int i=0;tok!=NULL;i++){
		args[i] = (char *)malloc(sizeof(tok)+1);
		strcpy(args[i],tok);
		tok = strtok(NULL," ");
	}
	return exec(b, args);
}
// double string overloaded
int exec(std::string b, std::string c){
	return exec(b.c_str(),c.c_str());
}
		
#endif

#include <string.h>
#include <limits.h>

#include <stdlib.h>
#include <stdio.h>

#ifndef FILEIO_H 
#define	FILEIO_H

char *LAST_PATH;

namespace shorthand {
	class file {
		private:
		//NODE ---------------------------------------------------------
			class line{
				public:
					line(){ 
						content = 0;
						next = NULL;
					}
					~line(){}
					
					line *next;
					char* content;
					//int flag;
			};
			line *first;
		
		public:
			//file(){first = new line();};
			file(char *s){
				first = new line();
				line *t = first;
				FILE *stream;
				char *l = NULL;
				size_t len = 0;
				ssize_t read;

				stream = fopen((const char *)s, "r");
				if (stream == NULL){
					exit(EXIT_FAILURE);
				}
				else{
					LAST_PATH = (char *)malloc(sizeof(s)+1);
					strcpy(LAST_PATH,s);
				}
				
				while ((read = getline(&l, &len, stream)) != -1) {
					t->content = (char *)malloc(sizeof(l)+1);
					strcpy(t->content, l);
					t->next = new line();
					t = t->next;
				}

				free(l);
				fclose(stream);
			};
			~file(){
					delete first;
			};
			
			int save(char *s = 0){
				line *t = first; char *outloc;
				if(s!=0){
					outloc = (char *)malloc(sizeof(s)+1);
					strcpy(outloc,s);
				}
				else{
					outloc = (char *)malloc(sizeof(LAST_PATH)+1);
					strcpy(outloc,LAST_PATH);
				}
				FILE *out;
				out = fopen((const char *)outloc,"w");
				while(t->next!=NULL){
					fputs(t->content,out);
					t=t->next;
				}
				free(outloc);
				return 0;
			}
			
			int print(){
				line *t = first;
				while(t!=NULL&&t->content!=NULL){
					printf("%s",t->content);
					t=t->next;
				}
				printf("\n");
				return 0;
			}
			
		
		
		
		
	}; 
}

#endif

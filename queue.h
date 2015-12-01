#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

namespace shorthand {
//----------------------------------------------------------------------
/*
 * 	QUEUE:
 * 		Operates the same as stack, using the push() and pop() functions 
 * 		to add and return values. Acts in a FIFO manner rather than FILO.
 * 
 * 	USAGE:
 * 		declare: " shorthand::queue <TYPE>NAME "
 * 		1. "NAME.push(VALUE)" 	- 	adds a value to the queue 
 * 		2. "NAME.pop()" 	- 	returns a value from the front of the queue.
 * 		3. "NAME.count()"	-	returns an int equal to the number of elements.
 */
	template <typename T>
	class queue {
		private:
			class node {
				public:
				/* 	VALUE:
				 * 		stored value in element
				 * 	NEXT:
				 * 		pointer to next element
				 */
					T value;
					node *next;
				//------------------------------------------------------
				/* 	CONSTRUCTORS
				 */
					node(){
						value = {};
						next = NULL;
					}
					node(T v){
						value = v;
						next = NULL;
					}
					~node(){};
				//------------------------------------------------------
			};
//----------------------------------------------------------------------
/* 	NUM:
 * 		stores number of elements
 * 	HOME:
 * 		points to the front of the queue
 */
			int num;
			node *home;
//----------------------------------------------------------------------
		public:
//----------------------------------------------------------------------
/*	CONSTRUCTORS
 */
			queue(){
				home = NULL;
				num = 1;
			}
			~queue(){
				while(home!=NULL){
					node *t = home->next;
					delete home;
					home = t;
				}
			}		
//----------------------------------------------------------------------
/* 	PUSH:
 * 		calling with value adds element onto the back of the queue.
 */
			int push(T v){
				if(home!=NULL){
					node *t = home;
					while(t->next!=NULL){
						t=t->next;
					}
					t->next = new node(v);
					num++;
					return 1;
				}
				else{
					home = new node(v);
					num++;
					return 1;
				}
				return 0;
			}
//----------------------------------------------------------------------
/* 	POP:
 * 		returns element from front of queue.
 */
			T pop(){
				if(home!=NULL){
					T v = home->value;
					node *t = home;
					home = home->next;
					delete t;
					num--;
					return v;
				}
				else{
					return {};
				}
			}
//----------------------------------------------------------------------
/* 	ELEM:
 * 		returns number of elements in queue.
 */
			int count(){
				return num;
			}
//----------------------------------------------------------------------
	};//END QUEUE CLASS
}
#endif

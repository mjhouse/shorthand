#ifndef STACK_H
#define STACK_H

#include <iostream>

//#define NULL 0

namespace shorthand {

//----------------------------------------------------------------------
/* 	STACK:
 * 		a user-created stack of nodes, used via the push() and pop() functions,
 * 		operates exactly like it sounds, in a first-on-last-off manner (FILO).
 * 
 * 	USAGE:
 * 		declare: " shorthand::stack <TYPE>NAME "
 * 		1. "push(VALUE)" 	- 	adds a value to the stack 
 * 		2. "NAME.pop()" 	- 	returns a value from the top of the stack.
 * 		3. "NAME.elem()"	-	returns an int equal to the number of elements.
 */
	template<typename T>
	class stack {
		private:
//----------------------------------------------------------------------
/* 	NODE:
 * 		A single element in the stack
 */
			class node {
				public:
				/* 	VALUE:
				 * 		stored value in element
				 * 	PTR:
				 * 		pointer to next "lower" element
				 * 	FULL:
				 * 		bool, true if element is holding value, false otherwise
				 */
					T value;
					node *ptr;
					bool full;
				//------------------------------------------------------
				/* 	CONSTRUCTORS
				 */
					node(){
						value = {};
						ptr = NULL;
						full = false;
					}
					node(node* p, T v){
						value = v;
						ptr = p;
						full = true;
					}
					~node(){};
				//------------------------------------------------------
			};
//----------------------------------------------------------------------
/* 	NUM:
 * 		stores number of elements
 * 	HOME:
 * 		points to the "top" of the stack (last added element)
 */
			int num;
			node *home;
//----------------------------------------------------------------------
		public:
//----------------------------------------------------------------------
/* 	CONSTRUCTORS
 */
			stack(){
				num = 0;
				home = new node();
			}
			~stack(){
				delete home;
			}
//----------------------------------------------------------------------
/* 	PUSH:
 * 		Calling with value "pushes" element onto the head of the list,
 * 		or replaces the initial element (if this is the first push)
 */
			int push(T v){
				if(home->full){
					node *t = new node(home, v);
					t->ptr = home;
					home = t;
					num++;
					return 1;
				}
				else{
					home->value = v;
					home->full = true;
					num++;
					return 1;
				}
				return 0;
			}
//----------------------------------------------------------------------
/*	POP:
 * 		Calling returns "top" element (last added element), and removes it.
 */
			T pop(){
				T retVal = home->value;
				if(home->ptr != NULL){
					node *t = home;
					home = home->ptr;
					num--;
					delete t;
				}
				else{
					home->full = false;
					home->value = {};
					if(num>0){
						num--;
					}
				}
				return retVal;
			}
//----------------------------------------------------------------------
/* 	ELEM:
 * 		returns number of elements when called
 */
			int elem(){
				return num;
			}
//----------------------------------------------------------------------
	};//END STACK CLASS
	
	
//----------------------------------------------------------------------
/*
 * 	QUEUE:
 * 		Operates the same as stack, using the push() and pop() functions 
 * 		to add and return values. Acts in a FIFO manner rather than FILO.
 * 
 * 	USAGE:
 * 		declare: " shorthand::queue <TYPE>NAME "
 * 		1. "push(VALUE)" 	- 	adds a value to the queue 
 * 		2. "NAME.pop()" 	- 	returns a value from the front of the queue.
 * 		3. "NAME.elem()"	-	returns an int equal to the number of elements.
 */
 
	template <typename T>
	class queue {
		private:
			class node {
				public:
				/* 	VALUE:
				 * 		stored value in element
				 * 	PTR:
				 * 		pointer to next element
				 * 	FULL:
				 * 		bool, true if element is holding value, false otherwise
				 */
					T value;
					node *ptr;
					bool full;
				//------------------------------------------------------
				/* 	CONSTRUCTORS
				 */
					node(){
						value = {};
						ptr = NULL;
						full = false;
					}
					node(node* p, T v){
						value = v;
						ptr = p;
						full = true;
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
				home = new node();
				num = 0;
			}
			~queue(){
				delete home;
			}		
//----------------------------------------------------------------------
/* 	PUSH:
 * 		calling with value adds element onto the back of the queue.
 */
			int push(T v){
				node *t = home;
				if(home->full){
					while(t->ptr!=NULL){
						t=t->ptr;
					}
					t->ptr = new node(NULL,v);
					num++;
				}
				else{
					home->value = v;
					home->full = true;
					num++;
				}
				
				return 0;
			}
//----------------------------------------------------------------------
/* 	POP:
 * 		returns element from front of queue.
 */
			T pop(){
				T tmp = home->value;
				if(home->ptr!=NULL){
					node *t = home;
					home = home->ptr;
					delete t;
					num--;
				}
				else{
					home->value = {};
					home->full = false;
					if(num>0)
						num--;
				}
				return tmp;
			}
//----------------------------------------------------------------------
/* 	ELEM:
 * 		returns number of elements in queue.
 */
			int elem(){
				return num;
			}
//----------------------------------------------------------------------
	};//END QUEUE CLASS

/*
 * LIST:
 * 		singly linked list template.
 * 
 * USAGE:
 * 		init with "shorthhand::list <VALUE TYPE>NAME;"
 * 		1. "NAME.add(VALUE)"				-	adds value to end of list
 * 		2. "NAME.add(VALUE,POSITION)"	-	adds value at position, if position exists, else appends (same as #1)
 * 		3. "NAME.remove(POSITION)"		-	removes value at position, if position is a valid int, else returns 0
 * 		4. "NAME.count()"				-	returns int equal to number of elements
 */
	template <typename T>
	class list{
		private:
			class node{
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
/* 	NUMELEM:
 * 		stores number of elements
 * 	HOME:
 * 		points to the front of the queue
 */
			node *home;
			int numElem;
		public:
			list(){
				home = NULL;
			}
			~list(){
				//delete home;
			}
//----------------------------------------------------------------------
/* 	ADD:
 * 		adds a node to the end of the list
 */			
			int add(T v){
				node *t=home;
				if(t== NULL){
					home = new node(v); numElem++;
					return 1;
				}
				else{
					while(t->next!=NULL)
						t=t->next;
					t->next = new node(v); numElem++;
					//t->next->back = t;
					return 1;
				}
				return 0;
			}
//----------------------------------------------------------------------
/* 	OVERLOADED ADD:
 * 		inserts a node at position "pos"
 */						
			int add(T v, int pos){
				node *t=home;
				if(pos<0||pos>=numElem)
					return add(v);
				else if(pos==0){
					numElem++;
					home = new node(v);
					home->next = t;
					return 1;
				}
				
				while(t!=NULL&&pos>1){
					pos--;
					t=t->next;
				}
				numElem++;
				node *s = t->next;
				t->next = new node(v);
				t->next->next = s;
				
				return 1;
			}
//----------------------------------------------------------------------
/* 	REMOVE:
 * 		removes the node at position "pos"
 */			
			int remove(int pos){
				node *t=home;
				if(pos<0||pos>=numElem)
					return 0;
				else if(pos==0){
					numElem--;
					home = home->next;
					delete t;
					return 1;
				}
				
				while(t!=NULL&&pos>1){
					pos--;
					t=t->next;
				}
				numElem--;
				node *s = t->next;
				t->next = t->next->next;
				delete s;
				
				return 1;
			}
//----------------------------------------------------------------------
/* 	PRINT:
 * 		returns the value at position "pos"
 */			
			T print(int pos){
				node *t=home;
				while(t!=NULL){
					if(pos==0){
						return t->value;
					}
					pos--;
					t=t->next;
				}
				return {};
			}
//----------------------------------------------------------------------
/* 	COUNT:
 * 		returns the number of elements
 */	
			int count(){
				return numElem;
			}
	};//END LIST CLASS
}
#endif

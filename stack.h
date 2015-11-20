#ifndef STACK_H
#define STACK_H

#define NULL 0

namespace shorthand {

//----------------------------------------------------------------------
/* 	STACK:
 * 		a user-created list of nodes, used via the push() and pop() functions
 * 
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
	};
}
#endif

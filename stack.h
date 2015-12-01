#ifndef STACK_H
#define STACK_H

/*

A simple stack implementation

Copyright (C) 2015  Michael House

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */

#include <iostream>

namespace shorthand {
//----------------------------------------------------------------------
/* 	STACK:
 * 		a user-created stack of nodes, used via the push() and pop() functions,
 * 		operates exactly like it sounds, in a first-on-last-off manner (FILO).
 * 
 * 	USAGE:
 * 		declare: " shorthand::stack <TYPE>NAME "
 * 		1. "NAME.push(VALUE)" 	- 	adds a value to the stack 
 * 		2. "NAME.pop()" 	- 	returns a value from the top of the stack.
 * 		3. "NAME.count()"	-	returns an int equal to the number of elements.
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
				 * 	NEXT:
				 * 		pointer to next "lower" element
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
				num = 1;
				home = NULL;
			}
			~stack(){
				while(home!=NULL){
					node *t = home->next;
					delete home;
					home = t;
				}
			}
//----------------------------------------------------------------------
/* 	PUSH:
 * 		Calling with value "pushes" element onto the head of the list,
 * 		or replaces the initial element (if this is the first push)
 */
			int push(T v){
				if(home!=NULL){
					node *t = new node(v);
					t->next = home;
					home = t;
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
/*	POP:
 * 		Calling returns "top" element (last added element), and removes it.
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
				return {};
			}
//----------------------------------------------------------------------
/* 	ELEM:
 * 		returns number of elements when called
 */
			int count(){
				return num;
			}
//----------------------------------------------------------------------
	};//END STACK CLASS
} // END SHORTHAND NAMESPACE
#endif

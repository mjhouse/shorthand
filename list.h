#ifndef LIST_H
#define LIST_H

/*

A singly-linked list template

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
/*
 * LIST:
 * 		singly linked list template.
 * 
 * USAGE:
 * 		init with "shorthhand::list <VALUE TYPE>NAME;"
 * 		1. "NAME.add(VALUE)"				-	adds value to end of list
 * 		2. "NAME.add(VALUE,POSITION)"		-	adds value at position, if position exists, else appends (same as #1)
 * 		3. "NAME.remove(POSITION)"			-	removes value at position, if position is a valid int, else returns 0
 * 		4. "NAME.count()"					-	returns int equal to number of elements
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
					~node(){
						while(home!=NULL){
							node *t = home->next;
							delete home;
							home = t;
						}
					}
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
} // END SHORTHAND NAMESPACE
#endif

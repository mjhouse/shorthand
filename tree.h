#ifndef TREE_H
#define TREE_H

/*

A simple binary tree

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
 * NODE:
 * 		node class for binary tree
 * 
 */
			class node {
				public:
				/*	VALUE:
				 * 		contained int value
				 * 
				 * 	RIGHT:
				 * 		pointer to right child
				 * 
				 * 	LEFT:
				 * 		pointer to left child
				 */
					int value;
					node *right;
					node *left;
				//------------------------------------------------------
				/*	CONSTRUCTORS
				 */
					node(){
						value = 0;
						right = NULL;
						left = NULL;
					}
					
				// OVERLOADED
					node(int n){
						value = n;
						right = NULL;
						left = NULL;
					}
				//------------------------------------------------------
					~node(){}
			}; // END NODE CLASS
//----------------------------------------------------------------------
//----------------------------------------------------------------------
/*
 * TREE:
 * 		binary tree
 * 
 * USAGE:
 * 		init with "shorthhand::tree NAME;"
 * 		1. "NAME.insert(INT)"			-	inserts INT value into tree
 * 		2. "NAME.search(INT)"			-	returns node* pointing to given value
 * 		3. "NAME.remove(INT)"			-	removes node containing value INT
 * 		4. "NAME.print()"				-	prints tree in-order
 */
	class tree {
		private:
			//----------------------------------------------------------
			// INSERT: inserts into tree
			//----------------------------------------------------------
			
			int insert(int i, node *t){
				if(i<t->value){
					if(t->left!=NULL){
						insert(i,t->left);
					}
					else{
						t->left = new node(i);
						return 1;
					}
				}
				else{
					if(t->right!=NULL){
						insert(i,t->right);
					}
					else{
						t->right = new node(i);
						return 1;
					}
				}
			}
			//----------------------------------------------------------
			// SEARCH: returns pointer to node containing "i"
			//----------------------------------------------------------
			
			node* search(int i, node *t){
				if(t!=NULL){
					if(i==t->value)
						return t;
					else if(i>t->value)
						return search(i,t->right);
					else if(i<t->value)
						return search(i,t->left);
				}
				else
					return NULL;
			}
			
			//----------------------------------------------------------
			// REMOVE: removes node containing "i"
			//----------------------------------------------------------
			
			int remove(int i, node *t){
				if(t!=NULL){
					if(i==t->value){
						//REMOVE
						return 1;
					}
					else{
						if(i<t->value)
							return remove(i,t->left);
						else
							return remove(i,t->right);
					}
				}
				else{
					return 0;
				}
			}
			
			//----------------------------------------------------------
			// DESTROY: destroys all nodes below node "t"
			//----------------------------------------------------------
			
			void destroy(node *t){
				if(t!=NULL){
					destroy(t->right);
					destroy(t->left);
					delete t;
				}
			}
			
			//----------------------------------------------------------
			// PRINT: prints all nodes in-order
			//----------------------------------------------------------
			
			void print(node *t){
				if(t!=NULL){
					print(t->left);
					std::cout << t->value << std::endl;
					print(t->right);
				}
			}
			
			//----------------------------------------------------------
			/* ROOT: 
			 * 		points to root node
			 */
			node *root;
		public:
			//----------------------------------------------------------
			// CONSTRUCTORS
			tree(){
				root = NULL;
			}
			~tree(){
				destroy(root);
			}
//----------------------------------------------------------------------
//	USER FUNCTIONS
//----------------------------------------------------------------------

/* 	INSERT:
 * 		inserts value "i" into tree
 */	
			int insert(int i){
				if(root!=NULL){
					return insert(i, root);
				}
				else{
					root = new node(i);
					return 1;
				}
			}
//----------------------------------------------------------------------

/* 	SEARCH:
 * 		returns pointer to node containing "i"
 */	
			node* search(int i){
				return search(i,root);
			}
//----------------------------------------------------------------------

/* 	REMOVE:
 * 		removes node containing "i"
 */	
			int remove(int i){
				return remove(i,root);
			}
//----------------------------------------------------------------------

/* 	PRINT:
 * 		prints tree in-order
 */	
			void print(){
				if(root!=NULL)
					print(root);
				else
					std::cout << "empty" << std::endl;
			}
	}; // END TREE CLASS
} // END SHORTHAND NAMESPACE
#endif

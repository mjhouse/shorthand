#ifndef TREE_H
#define TREE_H

namespace shorthand {

/*
 * 
 * 
 * 
 */
	template<typename T>
	class tree {
		private:
			// NODE ----------------------------------------------------
			class node {
				public:
					T value;
					int index;
					node *right;
					node *left;
					
					node(){
						value = {};
						index =0;
						right = NULL;
						left = NULL;
					}
					
					node(T v, int n){
						value = v;
						index = n;
						right = NULL;
						left = NULL;
					}
					~node(){}
			};
			//----------------------------------------------------------
			//----------------------------------------------------------
			
			int insert(T v, int i, node *t){
				
			}
			
			//----------------------------------------------------------
			//----------------------------------------------------------
			
			
			node *root;
		public:
			tree(){
				root = NULL;
			}
			~tree(){
				destroy(root);
			}
			
			int insert(T v, int pos){
				if(root!=NULL){
					return insert(v, pos, root);
				}
				else{
					root = new node(v, pos);
				}
			}
			
//----------------------------------------------------------------------
//----------------------------------------------------------------------

			int pull(){
			}
			
			int drop(){
			}
			
			int list(){
			}
			
	};

}
#endif

#include <bits/stdc++.h> 
using namespace std;  

template <typename T>
struct node{
	T val;
	T *left;
	T *right;
	int height;
};
//typedef struct node node;

template <typename T>
class avl{
	public:
		struct node<T>* root=NULL; 
		struct node<T>* getNode(T key){
			struct node<T> *nd= new struct node<T>();
			nd->left=nd->right=NULL;
			nd->height=1;
			return nd;
		}

		void inorder(struct node<T> *root){
			if(root){
				inorder(root->left);
				cout<<root->val<<" ";
				inorder(root->right);
			}
		}


		struct node<T>* insert(struct node<T> *root, T key ){
			if(key < root->val || key==root->val){
				root->left=insert(root->left, key);
			}
			else if(key > root->val){
				root->right=insert(root->right, key);
			}
			else if(root==NULL){
				struct node<T> *newNode=getNode(key);
				return newNode;
			}
			int lHeight = (root->left) ? root->left->height : 0;
			int rHeight = (root->right) ? root->right->height : 0;
			root->height= max(lHeight , rHeight) + 1;

		}

};

int main(){
	avl<int> tree;
	//struct node <int>* root=NULL;
	int key;
	while(1){
		cin>>key;
		tree.root=tree.insert(tree.root,key);
		tree.inorder(tree.root);
	}
	return 0;
}
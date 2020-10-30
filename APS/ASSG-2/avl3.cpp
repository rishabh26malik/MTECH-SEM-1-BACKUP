#include <bits/stdc++.h> 
using namespace std;  

struct node{
	int val;
	struct node *left;
	struct node *right;
	struct node *parent;
	int height;
};
typedef struct node node;

int HEIGHT(node *root){
	if(!root)
		return 0;
	return max(HEIGHT(root->left),HEIGHT(root->right))+1;
}

node* getNode(int key){
	node *nd= (node*)malloc(sizeof(node));
	nd->left=nd->right=nd->parent=NULL;
	nd->height=1;
	nd->val=key;
	return nd;
}
void inorder(node *root){
	if(root){
		inorder(root->left);
		cout<<root->val<<","<<root->height<<"   ";
		inorder(root->right);
	}
}

int getHeight(node *root){
	//cout<<"in getHeight\n";
	if(!root)
		return 0;
	return root->height;
	cout<<"out getHeight\n";
}

int getHeightDiff(node *root){
	//cout<<"in getHeightDiff\n";
	if(!root)
		return 0;
	return getHeight(root->left)-getHeight(root->right);

}

node* LL_rotate(node *root){
	cout<<"in LL...\n";
	node *new_root=root->left;
	node *tmp=new_root->right;
	new_root->right=root;
	root->left=tmp;
	root->height=max(getHeight(root->left),getHeight(root->right))+1;
	new_root->height=max(getHeight(new_root->left),getHeight(new_root->right))+1;
	root=new_root;
	return root;
}

node* RR_rotate(node *root){
	cout<<"in RR...\n";
	node *new_root=root->right;
	node *tmp=new_root->left;
	new_root->left=root;
	root->right=tmp;
	root->height=max(getHeight(root->left),getHeight(root->right))+1;
	new_root->height=max(getHeight(new_root->left),getHeight(new_root->right))+1;
	root=new_root;
	return root;
}

node* LR_rotate(node *root){
	//cout<<"in LR...\n";
	root->left=RR_rotate(root->left);
	return LL_rotate(root);
}

node* RL_rotate(node *root){
	//cout<<"in RL...\n";
	root->right=LL_rotate(root->right);
	return RR_rotate(root);
}

node* insert(node *root, int key ){
	if(root==NULL){
		node *newNode=getNode(key);
		return newNode;
	}
	else if(key < root->val || key == root->val ){
		root->left=insert(root->left, key);
	}
	else if(key > root->val){
		root->right=insert(root->right, key);
	}
	
	int lHeight = (root->left) ? root->left->height : 0;
	int rHeight = (root->right) ? root->right->height : 0;
	root->height= max(lHeight , rHeight) + 1;
	int height_diff;
	height_diff=getHeightDiff(root);
	if(height_diff > 1){			//	LEFT HEIGHT MORE
		if(root->left && key < root->left->val){			// LL
			//cout<<"in LL condn...\n";
			return LL_rotate(root);
		}
		else if (root->left && key > root->left->val){	// LR
			//cout<<"in LR condn...\n";
			return LR_rotate(root);
		}
	}
	else if(height_diff < -1){   	//	RIGHT HEIGHT MORE
		if(root->right && key < root->right->val){			// RL
			//cout<<"in RL condn...\n";
			return RL_rotate(root);
		}
		else if (root->right && key > root->right->val){	// RR
			//cout<<"in RR condn...\n";
			return RR_rotate(root);
		}
	} 
	return root;
}

int main(){
	int t;
	node *root=NULL;
	while(1){
		cin>>t;
		root=insert(root,t);
		//cout<<"b4 inorder call in main...\n";
		inorder(root);
		cout<<HEIGHT(root)<<endl;
		//cout<<"after inorder call in main...\n";
		cout<<endl;
	}
	return 0;
}
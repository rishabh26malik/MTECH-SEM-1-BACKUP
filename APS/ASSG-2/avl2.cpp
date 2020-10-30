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
	cout<<"in getHeight\n";
	if(!root)
		return 0;
	return root->height;
	cout<<"out getHeight\n";
}

int getHeightDiff(node *root){
	cout<<"in getHeightDiff\n";
	if(!root)
		return 0;
	return getHeight(root->left)-getHeight(root->right);

}

node* insert(node *root, int key ){
	if(root==NULL){
		cout<<"null\n";
		node *newNode=getNode(key);
		return newNode;
	}
	else if(key < root->val || key == root->val ){
		cout<<"left\n";
		root->left=insert(root->left, key);
	}
	else if(key > root->val){
		cout<<"right\n";
		root->right=insert(root->right, key);
	}
	
	int lHeight = (root->left) ? root->left->height : 0;
	int rHeight = (root->right) ? root->right->height : 0;
	root->height= max(lHeight , rHeight) + 1;
	int height_diff;
	//int height_diff=getHeightDiff(root);
	/*if(root){
		cout<<"in height_diff...\n";
		height_diff=getHeight(root->left)-getHeight(root->right);
	}
	else
		height_diff=0;*/
	cout<<"out getHeightDiff\n";
	/*if(root)
		height_diff = lHeight-rHeight; //(getHeight(root->left)-getHeight(root->right));
	else
		height_diff=0;*/
	cout<<"height diff..."<<height_diff<<endl;
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
		//cout<<"after inorder call in main...\n";
		cout<<endl;
	}
	return 0;
}
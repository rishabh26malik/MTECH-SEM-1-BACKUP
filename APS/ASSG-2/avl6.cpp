#include <bits/stdc++.h> 
using namespace std;  

template <class T>
class AVL{
public:
	struct node{
		T val;
		struct node *left;
		struct node *right;
		int sizeOfRightSubtree;
		int height;
	};
	typedef struct node node;
	node *root=NULL;
	int HEIGHT(node *root){
		if(!root)
			return 0;
		return max(HEIGHT(root->left),HEIGHT(root->right))+1;

	}
	node* getNode(T key){
		node *nd= (node*)malloc(sizeof(node));
		nd->left=nd->right=NULL;
		nd->height=1;
		nd->sizeOfRightSubtree=0;
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
		if(!root)
			return 0;
		return root->height;
	}

	int getHeightDiff(node *root){
		if(!root)
			return 0;
		return getHeight(root->left)-getHeight(root->right);
	}

	node* LL_rotate(node *root){
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
		root->left=RR_rotate(root->left);
		return LL_rotate(root);
	}

	node* RL_rotate(node *root){
		root->right=LL_rotate(root->right);
		return RR_rotate(root);
	}


	node* insert(node *root, T key ){
		if(root==NULL){
			//cout<<"in root null condn...\n";
			node *newNode=getNode(key);
			cout<<newNode->val<<endl;
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
			if(root->left && key < root->left->val){
				//cout<<"in LL condn...\n";			// LL
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

	node* deleteNode(node* root, T key) {
	    if(!root)
	        return root;
	    node *tmp;
	    if(key < root->val){
	        root->left=deleteNode(root->left, key);
	    }
	    else if (key > root->val){
	        root->right=deleteNode(root->right, key);
	    }
	    else{
	        if(!root->left && !root->right){
	            delete(root);
	            return NULL;
	        }
	        else if(!root->left || !root->right){
	            tmp=(root->left) ? root->left : root->right;
	            delete(root);
	            return tmp;
	        }
	        else{
	            node *tmp=root->right;
	            while(tmp->left){
	                tmp=tmp->left;
	            }
	            root->val=tmp->val;
	            root->right=deleteNode(root->right, tmp->val);
	        }
	    }
	    if (root == NULL)  
	    	return root;
	    int height_diff=getHeightDiff(root);
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

	bool search(node *root, T key){
		if(!root ){
			return false;
		}
		if(root->val==key){
			return true;
		}
		else if(key < root->val || key == root->val ){
			return search(root->left, key);
		}
		else if(key > root->val){
			return search(root->right, key);
		}
	}

	void count(node *root, T key, int &c){
		if(!root)
			return;
		else if(key <= root->val ){
			if(key == root->val)
				c++;
			count(root->left, key,c);
		}
		else if(key > root->val){
			count(root->right, key,c);
		}
	}

	void lower_bound_util(node *root, T key, node *&out){
		if(!root){
			if(out==NULL){
				cout<<"lower bound not present\n";
				exit(0);
			}
			return;
		}
		if(root->val >= key){
			out=root;
			lower_bound_util(root->left, key, out);
		}
		else if(root->val < key){
			lower_bound_util(root->right, key, out);
		}
	}

	T lower_bound(node *root, T key){
		node *out=NULL;
		lower_bound_util(root, key, out);
		return out->val;
	}

	void upper_bound_util(node *root, T key, node *&out){
		if(!root){
			if(out==NULL){
				cout<<"upper bound not present\n";
				exit(0);
			}
			return;
		}
		if(root->val > key){
			out=root;
			upper_bound_util(root->left, key, out);
		}
		else if(root->val < key){
			upper_bound_util(root->right, key, out);
		}
	}

	T upper_bound(node *root, T key){
		node *out=NULL;
		upper_bound_util(root, key, out);
		return out->val;
	}


	/*void closestValue_util(node *root, T key, node *&out){
		if(!root)
			return;
		if(root->val == key){
			out=root;
			//result=root->val;
			return;
		}
		else if(diff > abs(root->val - key)){
			diff=abs(root->val - key);
			result=root->val;
		}
		if(key < root->val)
			closestValue_util(root->left, key, diff, result);
		else
			closestValue_util(root->right, key, diff, result);
	}

	T closestValue(node *root, T key, T &diff, T &result){
		node *out=NULL;
		
	}*/


};

int main(){
	int t,key,c,result,min_diff;
	
	AVL <int> tree;
	while(1){
		cin>>t;
		switch(t){
			case 1:
				cin>>key;
				tree.root=tree.insert(tree.root,key);
				break;
			case 2:
				cin>>key;
				tree.root=tree.deleteNode(tree.root,key);
				break;
			case 3:
				cin>>key;
				c=0;
				tree.count(tree.root, key, c);
				cout<<"count = "<<c<<endl;
				break;
			case 4:
				cin>>key;
				cout<<tree.search(tree.root, key)<<endl;
				break;
			case 5:
				cin>>key;
				cout<<tree.lower_bound(tree.root, key)<<endl;
				break;
			case 6:
				cin>>key;
				cout<<tree.upper_bound(tree.root, key)<<endl;
				break;
			case 7:
				cin>>key;
				tree.closestValue(tree.root, key, diff, result);
				cout<<result<<endl;
				break;
			
		}
		tree.inorder(tree.root);
		cout<<" height = "<<tree.HEIGHT(tree.root)<<endl;
		cout<<endl;
	}
	return 0;
}

/*

void closestValue_util(node *root, T key, T &diff, T &result){
		if(!root)
			return;
		if(root->val == key){
			result=root->val;
			return;
		}
		else if(diff > abs(root->val - key)){
			diff=abs(root->val - key);
			result=root->val;
		}
		if(key < root->val)
			closestValue_util(root->left, key, diff, result);
		else
			closestValue_util(root->right, key, diff, result);
	}*/
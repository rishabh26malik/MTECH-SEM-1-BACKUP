#include <bits/stdc++.h> 
using namespace std;  

template <class T, class U>
class AVL{
public:
	struct node{
		T key;
		U value;
		struct node *left;
		struct node *right;
		int sizeOfRightSubtree;
		int height;
	};
	T dummy;
	int SIZE=0, flag=0;
	typedef struct node node;
	node *root=NULL;
	int HEIGHT(node *root){
		if(!root)
			return 0;
		return max(HEIGHT(root->left),HEIGHT(root->right))+1;

	}
	node* getNode(T key, U val){
		node *nd= (node*)malloc(sizeof(node));
		nd->left=nd->right=NULL;
		nd->height=1;
		nd->sizeOfRightSubtree=0;
		nd->key=key;
		nd->value=val;
		return nd;
	}

	void inorder(node *root){
	if(root){
			inorder(root->left);
			cout<<root->key<<" : "<<root->value<<"   ";
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
		//root=new_root;
		return new_root;
	}

	node* RR_rotate(node *root){
		node *new_root=root->right;
		node *tmp=new_root->left;
		new_root->left=root;
		root->right=tmp;
		root->height=max(getHeight(root->left),getHeight(root->right))+1;
		new_root->height=max(getHeight(new_root->left),getHeight(new_root->right))+1;
		//root=new_root;
		return new_root;
	}

	node* LR_rotate(node *root){
		root->left=RR_rotate(root->left);
		return LL_rotate(root);
	}

	node* RL_rotate(node *root){
		root->right=LL_rotate(root->right);
		return RR_rotate(root);
	}


	node* insert_util(node *root, T key, U value ){
		if(!flag){
			flag=1;
			dummy=value;
		}

		if(root==NULL){
			//cout<<"in root null condn...\n";
			node *newNode=getNode(key, value);
			//cout<<newNode->key<<" : "<<newNode->value<<endl;
			return newNode;
		}
		if(key == root->key ){
			SIZE--;
			if(root->value!=value)
				root->value=value;
			return root;
			
		}
		else if(key < root->key ){
			root->left=insert_util(root->left, key, value);
		}
		else if(key > root->key){
			root->right=insert_util(root->right, key, value);
		}
		
		int lHeight = (root->left) ? root->left->height : 0;
		int rHeight = (root->right) ? root->right->height : 0;
		root->height= max(lHeight , rHeight) + 1;
		int height_diff;
		height_diff=getHeightDiff(root);
		if(height_diff > 1){			//	LEFT HEIGHT MORE
			if(root->left && key < root->left->key){
				//cout<<"in LL condn...\n";			// LL
				return LL_rotate(root);
			}
			else if (root->left && key > root->left->key){	// LR
				//cout<<"in LR condn...\n";
				return LR_rotate(root);
			}
		}
		else if(height_diff < -1){   	//	RIGHT HEIGHT MORE
			if(root->right && key < root->right->key){			// RL
				//cout<<"in RL condn...\n";
				return RL_rotate(root);
			}
			else if (root->right && key > root->right->key){	// RR
				//cout<<"in RR condn...\n";
				return RR_rotate(root);
			}
		} 
		return root;
	}

	node* insert(T key, U value){
		SIZE++;
		root=insert_util(root, key, value);
		return root;
	}

	node* deleteNode_util(node* root, T key){  
	    if (root == NULL)  
	        return root;  
	    if ( key < root->key )  
	        root->left = deleteNode_util(root->left, key);  
	    else if( key > root->key )  
	        root->right = deleteNode_util(root->right, key); 
	    else{
	    	if(!root->left && !root->right){	//LEAF DELETION
	    		delete(root);
	    		return NULL;
	    	}
	    	else if(!root->left || !root->right){
	    		node *tmp;
	    		if(root->left){
	    			tmp=root->left;
	    		}
	    		else{
	    			tmp=root->right;
	    		}
	    		delete(root);
	    		return tmp;
	    	}
	    	else{
	    		node *tmp=root->right;
	    		while(tmp->left){
	    			tmp=tmp->left;
	    		}
	    		root->key=tmp->key;
	    		root->value=tmp->value;
	    		root->right=deleteNode_util(root->right, tmp->key);
	    	}
	    }
	    if (root == NULL)  
    		return root;
	    int lHeight = (root->left) ? root->left->height : 0;
		int rHeight = (root->right) ? root->right->height : 0;
		root->height= max(lHeight , rHeight) + 1;
		int height_diff;
		height_diff=getHeightDiff(root);
		if(height_diff > 1){			//	LEFT HEIGHT MORE
			int L_height_diff=getHeightDiff(root->left);
			if(L_height_diff >= 0){
				return LL_rotate(root);			// LL
				
			}
			else if (L_height_diff < 0){	// LR
				return LR_rotate(root);
				
			}
		}
		else if(height_diff < -1){   	//	RIGHT HEIGHT MORE
			int R_height_diff=getHeightDiff(root->right);
			if(R_height_diff > 0){			// RL
				//cout<<"in RL condn...\n";
				return RL_rotate(root);
			}
			else if (R_height_diff <= 0){	// RR
				//cout<<"in RR condn...\n";
				return RR_rotate(root);
			}
		} 
	    return root;
	}


	void erase(T key){
		node *nd= deleteNode_util(root,key);
		return;
	}

	bool find(node *root, T key){
		if(!root ){
			return false;
		}
		if(root->key==key){
			return true;
		}
		else if(key < root->key || key == root->key ){
			return find(root->left, key);
		}
		else if(key > root->key){
			return find(root->right, key);
		}
	}

	int size(){
		return SIZE;
	}

	node* getValue(node *root, T key){
		if(!root ){
			return NULL;
		}
		if(root->key==key){
			return root;
		}
		else if(key < root->key || key == root->key ){
			return getValue(root->left, key);
		}
		else if(key > root->key){
			return getValue(root->right, key);
		}
	}

	U& operator[](T key){
    	node *res=getValue(root,key);
    	if(!res){
    		//cout<<"not found.. invalid key...\n";
    		/*if(is_same<U, string>::value ){
    			root=insert(root,key,"dummy");
    		}
    		else
    			root=insert(root,key,0);*/
    		//if(typeid(U))
    		root=insert(key,dummy);
    		node *tmp=getValue(root, key);
    		return tmp->value;
    		//exit(0);
    	}
    	else{
    		return res->value;
    	}
    	
    }

};

int main(){
	int t, key, val;
	
	AVL <int,int> tree;
	while(1){
		cin>>t;
		switch(t){
			case 1:
				cin>>key>>val;
				tree.root=tree.insert(key, val);
				break;
			case 2:
				cin>>key;
				tree.erase(key);
				break;
			case 3:
				cin>>key;
				cout<<tree.find(tree.root, key)<<endl;
				break;
			case 4:
				cout<<tree.size()<<endl;
				break;
			case 5:
				cin>>key>>val;
				tree[key]=val;
				//cout<<tree[key]<<endl;
				break;
			case 6:
				tree.inorder(tree.root);
				break;
			
		}
		tree.inorder(tree.root);
		//cout<<" height = "<<tree.HEIGHT(tree.root)<<endl;
		cout<<endl;
	}
	return 0;
}


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
	//cout<<"in LL...\n";
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
	//cout<<"in RR...\n";
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

node* deleteNode(node* root, int key) {
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

node* search(node *root, int key){
	if(!root || root->val==key){
		return root;
	}
	else if(key < root->val || key == root->val ){
		return search(root->left, key);
	}
	else if(key > root->val){
		return search(root->right, key);
	}
}

void count(node *root, int key, int &c){
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

/*int lower_bound(node *root, int key, int &prev){
	if(!root)
		return -1;
	else if(root->val==key){
		
	}
	else if(key < root->val ){
		return lower_bound(root->left, key, prev);
	}
	else if(key > root->val){
		prev=root->val
		return lower_bound(root->right, key, prev);
	}
}

int upper_bound(node *root, int key){
	if(!root)
		return -1;
	else if(root->val==key){
		if(root->right)
			return root->right->val;
		return -1;
	}
	else if(key < root->val ){
		return upper_bound(root->left, key);
	}
	else if(key > root->val){
		return upper_bound(root->right, key);
	}
}
*/

int Closest_Element(node *root, int &min_diff, int key, int &result){
	if(!root)
		return result;
	if(root->val = key)
	{
		result=key;
		return key;
	}
	if(min_diff > abs(root->val - key)){
		min_diff=abs(root->val - key);
		result=root->val;
	}
	if(key < root->val){
		return Closest_Element(root->left, min_diff,key,result);
	}
	else{
		return Closest_Element(root->right, min_diff,key,result);	
	}
}

int main(){
	int t,key,c,result,min_diff;
	node *root=NULL;
	while(1){
		cin>>t;
		switch(t){
			case 1:
				cin>>key;
				root=insert(root,key);
				break;
			case 2:
				cin>>key;
				root=deleteNode(root,key);
				break;
			/*case 3:
				cin>>key;
				node *find=search(root,key);
				if(find)
					cout<<"FOUND!!\n";
				else
					cout<<"NOT FOUND!!\n";
				break;*/
			case 4:
				cin>>key;
				c=0;
				count(root,key,c);
				cout<<"count = "<<c<<endl;
				break;
			/*case 5:
				cin>>key;
				c=0;
				cout<<lower_bound(root,key)<<endl;
				break;
			case 6:
				cin>>key;
				c=0;
				cout<<upper_bound(root,key)<<endl;
				break;*/
			case 7:
			cin>>key;
			min_diff=INT_MAX;
			result=-1;
			cout<<Closest_Element(root, min_diff, key, result)<<endl;
			cout<<result<<endl;
		}
		
		//cout<<"b4 inorder call in main...\n";
		//inorder(root);
		cout<<HEIGHT(root)<<endl;
		//cout<<"after inorder call in main...\n";
		cout<<endl;
	}
	return 0;
}
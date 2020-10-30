#include <bits/stdc++.h> 
using namespace std;  

template <class T>
class AVL{
public:
	struct node{
		T val;
		struct node *left;
		struct node *right;
		int sizeOfRightSubtree, sizeOfLeftSubtree;
		int height;
	};
	typedef struct node node;
	node *root=NULL;
	int SIZE=0;
	int HEIGHT(node *root){
		if(!root)
			return 0;
		return max(HEIGHT(root->left),HEIGHT(root->right))+1;

	}
	node* getNode(T key){
		node *nd= (node*)malloc(sizeof(node));
		nd->left=nd->right=NULL;
		nd->height=1;
		nd->sizeOfRightSubtree=nd->sizeOfLeftSubtree=0;
		nd->val=key;
		return nd;
	}

	void inorder(node *root){
	if(root){
			inorder(root->left);
			//cout<<root->val<<"  ";
			cout<<root->sizeOfLeftSubtree<<","<<root->val<<","<<root->sizeOfRightSubtree<<"   ";
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

	void updateSubtreeSize(node *root){
		int Rsize=(root->right) ? root->right->sizeOfLeftSubtree + root->right->sizeOfRightSubtree + 1 : 0;
		int Lsize=(root->left) ? root->left->sizeOfLeftSubtree + root->left->sizeOfRightSubtree + 1 : 0;
		root->sizeOfRightSubtree = Rsize;
		root->sizeOfLeftSubtree = Lsize;
		//root->sizeOfRightSubtree = (root->right) ? root->right->sizeOfRightSubtree + 1 : 0;
		//root->sizeOfLeftSubtree  = (root->left)  ? root->left->sizeOfLeftSubtree + 1   : 0;
	}

	node* LL_rotate(node *root){
		node *new_root=root->left;
		node *tmp=new_root->right;
		new_root->right=root;
		root->left=tmp;
		root->height=max(getHeight(root->left),getHeight(root->right))+1;
		new_root->height=max(getHeight(new_root->left),getHeight(new_root->right))+1;
		root=new_root;
		updateSubtreeSize(root);
		updateSubtreeSize(new_root);
		return root;
	}

	node* RR_rotate(node *root){
		node *new_root=root->right;
		node *tmp=new_root->left;
		new_root->left=root;
		root->right=tmp;
		root->height=max(getHeight(root->left),getHeight(root->right))+1;
		new_root->height=max(getHeight(new_root->left),getHeight(new_root->right))+1;
		updateSubtreeSize(root);
		updateSubtreeSize(new_root);
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
			SIZE++;
			node *newNode=getNode(key);
			//cout<<newNode->val<<endl;
			return newNode;
		}
		else if(key < root->val || key == root->val ){
			root->left=insert(root->left, key);
		}
		else if(key > root->val){
			root->right=insert(root->right, key);
		}
		
		//updateSubtreeSize(root);

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
		updateSubtreeSize(root);
		return root;
	}

	node* deleteNode(node* root, T key) {
	    if(!root){
	    	SIZE--;
	        return root;
	    }
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

	/*bool search(node *root, T key){
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
	}*/

	node* search_util(node *root, T key){
		if(!root ){
			return root;
		}
		if(root->val==key){
			return root;
		}
		else if(key < root->val || key == root->val ){
			return search_util(root->left, key);
		}
		else if(key > root->val){
			return search_util(root->right, key);
		}
	}

	bool search(T key){
		if(search_util(root,key))
			return true;
		return false;
	}

	void count_util(node *root, T key, int &c){
		if(!root)
			return;
		else if(key <= root->val ){
			if(key == root->val)
				c++;
			count_util(root->left, key,c);
		}
		else if(key > root->val){
			count_util(root->right, key,c);
		}
	}

	int count(T key){
		int c=0;
		count_util(root,key,c);
		return c;
		
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

	T lower_bound(T key){
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

	T upper_bound(T key){
		node *out=NULL;
		upper_bound_util(root, key, out);
		return out->val;
	}

	node* kTHlargest_util(node *root, int &k){
		//cout<<"in kTHlargest _ UTIL...."<<k<<endl;
		if(!root)
			return root;
		if( k == 0 /*|| k -1 == root->sizeOfRightSubtree*/ )
			return root;
		//else if()
		/*else if( k-1 > root->sizeOfRightSubtree ){
			k -= root->sizeOfRightSubtree;
			return kTHlargest_util(root->right, k);
		}*/
		else if( k-1 == root->sizeOfRightSubtree ){
			return root;
			//k -= root->sizeOfRightSubtree;
			//return kTHlargest_util(root->right, k);
		}
		else if( k > root->sizeOfRightSubtree ){
			k =k-1- root->sizeOfRightSubtree;
			return kTHlargest_util(root->left, k);
		}
		else if( k == root->sizeOfRightSubtree ){
			k -= root->sizeOfRightSubtree;
			return kTHlargest_util(root->right, k);
		}
		else{
			return kTHlargest_util(root->right, k);	
		}
	}
	T kTHlargest(int k){
		//cout<<"in kTHlargest....\n";
		node *nd=kTHlargest_util(root,k);
		if(!nd){
			cout<<"kth largest not present\n";
			exit(0);
		}
		//cout<<"OUT kTHlargest....\n";
		return nd->val;
	}

	int countINRange_util(node *root, int low, int high){
		node *ll=search_util(root, low);
		node *rr=search_util(root, high);
		int lsize=0,rsize=0;
		if(ll){
			lsize=ll->sizeOfLeftSubtree;
			//lsize=1 + ll->sizeOfLeftSubtree + ll->sizeOfRightSubtree;
		}
		if(rr){
			rsize=rr->sizeOfRightSubtree;
			//rsize=1 + rr->sizeOfLeftSubtree + rr->sizeOfRightSubtree;
		}
		cout<<SIZE<<" "<<lsize<<" "<<rsize<<endl;
		return SIZE- lsize - rsize; 
	}


	int countINRange(int low, int high){
		int result=countINRange_util(root, low, high);
		return result;
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

	T closestValue(T key){
		node *out=NULL;
		
	}*/


};

int main(){
	int t,key,c,result,min_diff, k;
	int val1,val2;
	pair<int,int> p;
	AVL <int> tree;
	tree.root=tree.insert(tree.root,10);
	tree.root=tree.insert(tree.root,20);
	tree.root=tree.insert(tree.root,30);
	tree.root=tree.insert(tree.root,40);
	tree.root=tree.insert(tree.root,50);
	tree.root=tree.insert(tree.root,60);
	tree.inorder(tree.root);
	while(1){
		cin>>key;
		//cout<<tree.closestValue(key)<<endl;
	}
	/*while(1){
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
				cout<<tree.count(key)<<endl;
				break;
			case 4:
				cin>>key;
				cout<<tree.search(key)<<endl;
				break;
			case 5:
				cin>>key;
				cout<<tree.lower_bound(key)<<endl;
				break;
			case 6:
				cin>>key;
				cout<<tree.upper_bound(key)<<endl;
				break;
			//case 7:
			//	cin>>key;
			//	tree.closestValue(tree.root, key);
			//	cout<<result<<endl;
			//	break;
			case 8:
				cin>>k;
				cout<<tree.kTHlargest( k)<<endl;
				break;
			case 9:
				int low,high;
				cin>>low>>high;
				cout<<tree.countINRange(low,high)<<endl;	
				break;
		}
		tree.inorder(tree.root);
		//cout<<" height = "<<tree.HEIGHT(tree.root)<<endl;
		cout<<endl;
	}*/
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
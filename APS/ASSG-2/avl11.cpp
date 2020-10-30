#include <bits/stdc++.h> 
#include <type_traits>

using namespace std;  

template <class T>
class AVL{
public:
	struct node{
		T val;
		struct node *left;
		struct node *right;
		int sizeOfRightSubtree, sizeOfLeftSubtree;
		int smallCount;
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
	node* getNode(T key, int smallerCount){
		node *nd= (node*)malloc(sizeof(node));
		nd->left=nd->right=NULL;
		nd->height=1;
		nd->sizeOfRightSubtree=nd->sizeOfLeftSubtree=0;
		nd->val=key;
		nd->smallCount=smallerCount;
		return nd;
	}

	void inorder(node *root){
	if(root){
			inorder(root->left);
			//cout<<root->val<<","<<root->smallCount<<"  ";
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


	node* insert_util(node *root, T key, int smallerCount ){
		if(root==NULL){
			//cout<<"in root null condn...\n";
			SIZE++;
			node *newNode=getNode(key,smallerCount);
			//cout<<newNode->val<<endl;
			return newNode;
		}
		else if(key < root->val || key == root->val ){
			root->left=insert_util(root->left, key, smallerCount);
		}
		else if(key > root->val){
			smallerCount=root->smallCount + 1;
			root->right=insert_util(root->right, key, smallerCount);
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

	node* insert(T key){
		node *nd=insert_util(root,key,0);
		return nd;
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
		updateSubtreeSize(root);
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

	int countINRange_util(node *root, T key, node *&tmp){
		if(!root)
			return 0;
		if(root->val == key)
			return root->smallCount;
		else if(root->val > key){
			//tmp=root;
			return countINRange_util(root->left, key, tmp);
		}
		else{
			tmp=root;
			return countINRange_util(root->right, key, tmp);	
		}
	}


	void countINRange_util(node *root, T low, int &c){
		if(!root)
			return;
		if(root->val == low){
			c=c+1;
			cout<<"a - "<<c<<endl;
			countINRange_util(root->left, low, c);
		}
		else if( root->val > low){
			cout<<"b - "<<c<<endl;
			countINRange_util(root->left, low, c);
		}
		else if(root->val < low){
			c=c+1+root->sizeOfLeftSubtree;
			cout<<"c - "<<c<<endl;
			countINRange_util(root->right, low, c);
		}
	}

	int countINRange(T low, T high){
		int a=0,b=0;
		countINRange_util(root,low,a);
		cout<<"-----------\n";
		countINRange_util(root,high,b);
		cout<<a<<" "<<b<<endl;
		return b-a+1;
	}

	//template <class T>
	void closestValue_util(node *root, T key, node *&min_diff, node *&out){
		if(!root)
			return;
		if(abs(min_diff->val - key) > abs(root->val - key)){
			out=root;
			min_diff=root;
		}
		else if(abs(min_diff->val - key) == abs(root->val - key)){
			if(root->val < min_diff->val)
				out=root;
			else
				out=min_diff;
		}
		if(key < root->val)
			closestValue_util(root->left, key, min_diff, out);
		else if(key > root->val)
			closestValue_util(root->right, key, min_diff, out);
		else if(key == root->val){
			min_diff=out=root;
			return;
		}
		
	}

/*
T close_val(node<T> *root,T x,T cl)
{
	if(root)
	{
		if(abs(cl-x) > abs(root->val-x))
			cl=root->val;
		if(abs(cl-x) == abs(root->val-x))		//alwways take smaller value
			cl=min(root->val,cl);
				
		if(x < root->val)  
			return close_val(root->left,x,cl);
		else if(x > root->val) 
			return close_val(root->right,x,cl);
		else if(x == root->val)
			return x;
	}
	return cl;
}*/
	//template <>
	/*void closestValue_util_string(node *root, string key, node *&pre, node *&suc){
		if(!root)
			return;
		if(root->val == key){
			pre=root;
			return;
		}
		else if(key < root->val){
			suc=root;
			closestValue_util_string(root->left, key, pre, suc);
		}
		else{
			pre=root;
			closestValue_util_string(root->right, key, pre, suc);
		}
	}*/

		/*string closestValue(string key){
		node *pred=NULL, *succ=NULL;
		closestValue_util(root, key, pred, succ);
		if(pred)
			return pred->val;
		return succ->val;	
	}*/
	//template <class T>
	T closestValue(T key){
		node *out=NULL;
		//T min_diff;
		    if(is_same<T, string>::value ){
		    	node *pred=NULL, *succ=NULL;
		    	cout<<"ninccxcx\n";
				//closestValue_util_string(root, key, pred, succ);
				if(pred)
					return pred->val;
				return succ->val;
		    }
		    else if(is_same<T, int>::value || is_same<T, float>::value || is_same<T, double>::value || is_same<T, char>::value){
		    	node *min_diff=root;
				closestValue_util(root, key, min_diff, out);
			}
			
		return out->val;	
	}

};


	//template <>


int main(){
	int t,c,result,min_diff, k, key;
	//string val1,val2;
	//string key;
	pair<int,int> p;
	AVL <int> tree;
	/*tree.root=tree.insert(20);
	tree.root=tree.insert(10);
	tree.root=tree.insert(5);
	tree.root=tree.insert(15);
	tree.root=tree.insert(16);
	tree.root=tree.insert(17);
	tree.root=tree.insert(19);
	tree.root=tree.insert(30);
	tree.root=tree.insert(40);
	tree.root=tree.insert(25);
	tree.root=tree.insert(24);
	tree.root=tree.insert(27);
	tree.root=tree.insert(29);
	tree.inorder(tree.root);
	while(1){
		int low,high;
		cin>>low>>high;
		cout<<tree.countINRange(low,high)<<endl;
	}*/
	while(1){
		cin>>t;
		switch(t){
			case 1:
				cin>>key;
				tree.root=tree.insert(key);
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
			case 7:
				cin>>key;
				cout<<tree.closestValue(key)<<endl;
				
				break;
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
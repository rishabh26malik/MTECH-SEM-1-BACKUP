#include <bits/stdc++.h> 
#include <type_traits>

using namespace std;  

class abc{
public:
	pair <int,int> p;
	abc(){
		p.first=1;
		p.second=2;
	}
	abc(int a){
		p.first=a;
		p.second=20;
	}
	abc(int a,int b){
		p.first=a;
		p.second=b;
	}
	bool operator <(abc A){
		if(p.first < A.p.first )
			return true;
		else if(p.first == A.p.first && p.second < A.p.second)
			return true;
		return false;
	}
	bool operator >(abc A){
		if(p.first > A.p.first )
			return true;
		else if(p.first == A.p.first && p.second > A.p.second)
			return true;
		return false;
	}
	bool operator ==(abc A){
		return (p.first == A.p.first && p.second == A.p.second);
	}
	bool operator <=(abc A){
		if(p.first < A.p.first )
			return true;
		else if(p.first == A.p.first && p.second < A.p.second)
			return true;
		else if (p.first == A.p.first && p.second == A.p.second)
			return true;
		return false;
	}
	bool operator >=(abc A){
		if(p.first > A.p.first )
			return true;
		else if(p.first == A.p.first && p.second > A.p.second)
			return true;
		else if (p.first == A.p.first && p.second == A.p.second)
			return true;
		return false;
	}
	bool operator -(abc A){
		if(p.first - A.p.first < 0 )
			return true;
		else if(p.first == A.p.first && p.second < A.p.second)
			return true;
		return false;
	}
};

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
			//cout<<(root->val).p.first<<" "<<(root->val).p.second<<","<<"   ";
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
		if(!root)
			return root;
		if( k == 0  )
			return root;
		
		else if( k-1 == root->sizeOfRightSubtree ){
			return root;
			
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

	void countSmaller(node *root, T key, int &c, bool &found){
		if(root){
			countSmaller(root->left, key, c, found);
			if(root->val <= key){
				c++;
			}
			if(root->val == key){
				found=true;
			}
			countSmaller(root->right, key, c, found);
		}
	}

	int countINRange(T low, T high){
		int a,b;
		a=b=0;
		bool lowFound=false, highFound=false;
		countSmaller(root, low, a, lowFound);
		countSmaller(root, high, b, highFound);
		if(!lowFound && !highFound)
			return b-a;
		else if(lowFound && highFound)
			return b-a+1;
		else if(!lowFound && highFound)
			return b-a;
		else
			return b-a+1;
	}

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

	
	T closestValue(T key){
		node *out=NULL;
		node *min_diff=root;
		closestValue_util(root, key, min_diff, out);
		return out->val;	
	}

};

int main(){
	int t,c,result,min_diff, k;
	int key;
	//string key;
	AVL <int> tree;
	//AVL <string> tree;
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
				//out=tree.closestValue(key);
				//cout<<out.p.first<<" "<<out.p.second<<endl;
				cout<<tree.closestValue(key)<<endl;
				
				break;
			case 8:
				cin>>k;
				cout<<tree.kTHlargest( k)<<endl;
				//cout<<out.p.first<<" "<<out.p.second<<endl;
				//cout<<tree.kTHlargest( k)<<endl;
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

int main(){
	int t,c,result,min_diff, k, key;
	//string val1,val2;
	//string key;
	abc A(4,5);
	abc out;
	AVL <abc> tree;
	
	while(1){
		cin>>t;
		switch(t){
			case 1:
				cin>>key>>k;
				A.p.first=key;
				A.p.second=k;
				tree.root=tree.insert(A);
				break;
			case 2:
				cin>>key>>k;
				A.p.first=key;
				A.p.second=k;
				tree.root=tree.deleteNode(tree.root,A);
				break;
			case 3:
				cin>>key>>k;
				A.p.first=key;
				A.p.second=k;
				cout<<tree.count(A)<<endl;
				break;
			case 4:
				cin>>key>>k;
				A.p.first=key;
				A.p.second=k;
				cout<<tree.search(A)<<endl;
				break;
			case 5:
				cin>>key>>k;
				A.p.first=key;
				A.p.second=k;
				out=tree.lower_bound(A);
				cout<<out.p.first<<" "<<out.p.second<<endl;
				//cout<<tree.lower_bound(A)<<endl;
				break;
			case 6:
				cin>>key>>k;
				A.p.first=key;
				A.p.second=k;
				out=tree.upper_bound(key);
				cout<<out.p.first<<" "<<out.p.second<<endl;
				//cout<<tree.upper_bound(key)<<endl;
				break;
			case 7:
				cin>>key>>k;
				out=tree.closestValue(key);
				cout<<out.p.first<<" "<<out.p.second<<endl;
				
				break;
			case 8:
				cin>>k;
				out=tree.kTHlargest( k);
				cout<<out.p.first<<" "<<out.p.second<<endl;
				//cout<<tree.kTHlargest( k)<<endl;
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

*/
#include<bits/stdc++.h>
using namespace std;
struct trie{
	struct trie *left=NULL, *right=NULL;
};
typedef struct trie trie;
trie *root;

void makeTrie(vector <long long int> arr, int n){
	long long int i, j;
	trie *tmp;
	for(i=0;i<n;i++){
		tmp=root;
		for(j=63;j>=0;j--){
			if((arr[i]>>j)&1==1){
				if(!tmp->right){
					tmp->right=(trie*)malloc(sizeof(trie));
				}
				tmp=tmp->right;
			}
			else{
				if(!tmp->left){
					tmp->left=(trie*)malloc(sizeof(trie));
				}
				tmp=tmp->left;
			}
		}
	}
}

int maxXor(vector <long long int> arr, int n){
	long long int  i, Xor, j;
	trie *tmp;
	tmp=root;
	Xor=0;
	for(j=63;j>=0;j--){
		if((n>>j)&1 == 1){
			if(tmp->left){
				tmp=tmp->left;
				Xor+=pow(2,j);
			}
			else
				tmp=tmp->right;
		}	
		else{
			if(tmp->right){
				tmp=tmp->right;
				Xor+=pow(2,j);
			}
			else
				tmp=tmp->left;
		}
	}
		
	return Xor;
}


int main(){
	long long int n, q, i, num;
	cin>>n>>q;
	vector <long long int> arr(n);
	for(i=0;i<n;i++){
		cin>>arr[i];
	}
	root=(trie*)malloc(sizeof(trie));
	makeTrie(arr, n);
	while(q--){	
		cin>>num;
		cout<<maxXor(arr, num)<<endl;
	}
	return 0;
}
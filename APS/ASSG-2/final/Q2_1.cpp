#include <bits/stdc++.h> 
using namespace std;  
#define MAX 100005
#define BKT 100

template <class A, class B>
class Unordered_Map{
public:
	long long prime_num = 31;
    long long bucket = BKT;
	struct node{
		A key;
		B value;
		struct node *next;
	};
	typedef struct node node;
	node *hash[MAX];
	node *last[MAX];
	Unordered_Map(){
		int i;
		// INITIALIZE HASH TABLE WITH ALL NULL VALUES
		for(i=0;i<100005;i++){
			hash[i]=NULL;
			last[i]=NULL;
		}
	}

	/************************************/
	int calculateHash(A key)
    {
        ostringstream s1;
        s1 << key;
        string s = s1.str();
        long long hash_val = 0;
        long long mul = 1;
        for (long long i = 0; i < s.size(); i++)
        {
            hash_val += (s[i] * mul);
            hash_val %= bucket;
            mul *= prime_num;
        }
        return hash_val;
    }
	/********************************* */

    node* getNode(A key, B val){
    	node *nd=(node*)malloc(sizeof(node));
    	nd->key=key;
    	nd->value=val;
    	nd->next=NULL;
    	return nd;
    }

    /*void displayHASH(){
    	int i=0;
    	for(i=0;i<100005;i++){
    		if(hash[i]){
    			cout<<"INDEX : "<<i<<"  -->>  ";
    			node *tmp=hash[i];
    			while(tmp){
    				cout<<tmp->key<<" : "<<tmp->value[0]<<" "<<tmp->value[1]<<" "<<tmp->value[2]<<",  ";
    				tmp=tmp->next;
    			}
    			cout<<endl;
    		}
    	}
    }*/

    void insert(A key, B val){
    	int idx=calculateHash(key);
    	int i;
    	node *tmp=hash[idx];
    	if(hash[idx]==NULL){		// first {key,value} insertion
            node *nd=getNode(key, val);
    		hash[idx]=nd;
    	}
    	else{
    		while(tmp->next != NULL){
    			if(tmp->key == key){
    				cout<<"in same key...\n";
    				if(tmp->value == val)
    					return;
    				else{
    					tmp->value=val;
    					return;
    				}
    			}
    			tmp=tmp->next;
    		}
    		if(tmp->key== key){
    				if(tmp->value != val){
    					tmp->value=val;
    				}
    				return;
    		}
    		node *nd=getNode(key, val);
    		tmp->next=nd;
    	}
    	
    }

    void erase(A key){
    	int idx=calculateHash(key);
    	int i;
    	node *tmp=hash[idx];
    	if(hash[idx]==NULL){		// first {key,value} insertion
    		return;
    	}
    	else if(hash[idx]->key==key){
    		hash[idx]=hash[idx]->next;
    		delete(tmp);
    	}
    	else{
    		while(tmp->next != NULL){
    			if(tmp->next->key == key){
    				node *del=tmp->next;
    				tmp->next=del->next;
    				delete(del);
    				break;
    			}
    			tmp=tmp->next;
    		}

    	}
    }

    bool find(A key){
    	int idx=calculateHash(key);
    	int i;
    	node *tmp=hash[idx];
    	if(hash[idx]==NULL){		// first {key,value} insertion
    		return false;
    	}
    	else{
    		while(tmp != NULL){
    			if(tmp->key == key){
    				return true;
    			}
    			tmp=tmp->next;
    		}
    	}
    	return false;
    }

    B operator[](A key){
    	int idx=calculateHash(key);
    	node *tmp=hash[idx];
    	if(hash[idx]==NULL){		// first {key,value} insertion
    		cout<<"not found\n";
    		exit(0);
    		//return NULL;
    	}
    	else{
    		while(tmp != NULL){
    			if(tmp->key == key){
    				//node *nd=getNode(key,tmp->value);
    				//return nd;
    				return tmp->value;
    			}
    			tmp=tmp->next;
    		}
    	}
    }

};


int main(){
	//unordered_map <int, pair<int,string>> hh;
	//Unordered_Map<int,vector<pair<int,int>>> a;
    //Unordered_Map<int,vector<string>> a;
    //Unordered_Map<int,vector<char>> a;
    Unordered_Map<int,vector<pair<int,char>>> a;
    //vector <pair<int,int>> vec;
    //vector <pair<int,int>> out;
    //pair<int,int> p;
    //vector<string> vec,out;
    pair<int,char> p;
    //vector<char> vec,out;
    vector<pair<int,char>> vec,out;
	int key, val1,choice, val2, val3,n;
    string val;
    char ch;
	while(1){
        cout<<"\nenter choice : ";
		cin>>choice;;
		switch(choice){
			case 1:
                cout<<"enter key , n : ";
				cin>>key>>n;
                vec.clear();
                while(n--){
                    cin>>val1>>ch;      // vec of pair(int,char)
                    p={val1,ch};
                    vec.push_back(p);
                    /*cin>>ch;         // vec of char        DONE
                    vec.push_back(ch);*/
                    /*cin>>val;         // vec of string
                    vec.push_back(val);*/
                    /*cin>>val1;
                    vec.push_back(val1);*/
                    /*cin>>val1>>val2;          //vec of pair   DONE
                    p={val1,val2};
                    vec.push_back(p);*/
                }
				a.insert(key,vec);
				break;
			case 2:
				cin>>key;
				a.erase(key);
				break;
			case 3:
				cin>>key;
				if(a.find(key))
					cout<<"found\n";
				else
					cout<<"not found\n";
				break;
			case 4:
				cin>>key;
                out=a[key];
				for(auto it : out){
                    cout<<it.first<<" "<<it.second<<",  ";	
                }
                
		}
		//a.displayHASH();
	}
	return 0;
}
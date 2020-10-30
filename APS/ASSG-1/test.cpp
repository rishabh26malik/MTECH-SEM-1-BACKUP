#include <bits/stdc++.h> 
using namespace std;  

template <class T >
struct node{
	T data;
	node<T> *next, *prev;
};
//typedef struct node node;
template <class T >

class Deque{
	public :
	node<T> *rear, *front;
	Deque<T>(){
		rear=front=NULL;
	}
	void deque1(int n, T x){
		node<T> *tmp;
		while(n--){
			tmp=new node<T>;
			tmp->data=x;
			tmp->next=tmp->prev=NULL;
			if(front==NULL){
				front=rear=tmp;
			}	
			else{
				rear->next=tmp;
				tmp->prev=rear;
				rear=tmp;
			}
		}
	}

	void push_back1(T x){
		node<T> *tmp;
		tmp=new node<T>;
		tmp->data=x;
		tmp->next=tmp->prev=NULL;
		if(front==NULL){
			front=rear=tmp;
		}	
		else{
			rear->next=tmp;
			tmp->prev=rear;
			rear=tmp;
		}
	}

	T pop_back1(){
		T res;
		node<T> *tmp;
		if(rear){
			tmp=rear;
			res=rear->data;
			if(rear->prev){
				rear=rear->prev;
				rear->next=NULL;
			}
			else{
				front=rear=NULL;
			}
			delete(tmp);
			return res;
		}
		return -1;
	}

	T pop_front1(){
		T res;
		node<T> *tmp;
		if(front){
			tmp=front;
			res=front->data;
			if(front->next){
				front=front->next;
				front->prev=NULL;
				//Q=front;
			}
			else{
				front=rear=NULL;
			}
			delete(tmp);
			return res;
		}
		return -1;
	}

	void push_front1(T x){
		//node *tmp=(node*)malloc(sizeof(node));
		node<T> *tmp;
		tmp=new node<T>;
		tmp->data=x;
		tmp->next=tmp->prev=NULL;
		if(front==NULL){
			//Q=tmp;
			front=rear=tmp;
		}	
		else{
			front->prev=tmp;
			tmp->next=front;
			front=tmp;
			//Q=front;
		}
	}


	void display(){
		node<T> *tmp=front;
		while(tmp){
			cout<<tmp->data<<" ";
			tmp=tmp->next;
		}
	}

	void clear(){
		node<T> *tmp=front;
		while(front){
			tmp=front;
			front=front->next;
			delete(tmp);
		}
		front=rear=NULL;
	}

	int front1(){
		if(front){
			return front->data;
		}
		return -1;
	}

	int back(){
		if(rear){
			return rear->data;
		}
		return -1;
	}

	bool empty(){
		if(!front)
			return true;
		return false;
	}

	int size(){
		int i=0;
		node<T>* tmp=front;
		while(tmp){
			i++;
			tmp=tmp->next;
		}
		return i;
	}
};

int main() 
{ 
  	Deque<int> Q;
  	//Q.deque1(5,"aa");
  	Q.display();
  	int ch,num,n;
	cout<<"1 - pushback\n"<<"2 - pushfront\n"<<"3 - popback\n"
		<<"4 - popfront\n"<<"5 - display\n"<<"6 - clear\n"
		<<"7 - front\n"<<"8 - back\n"<<"9 - empty\n"
		<<"10 - size\n"<<"11 - deque(n,x)"<<endl;
	//display();
	while(1){
		cout<<"enter choice : ";
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"enter no. - ";
				cin>>num;
				Q.push_back1(num);
				break;
			case 2:
				cout<<"enter no. - ";
				cin>>num;
				Q.push_front1(num);
				break;
			case 3:
				cout<<Q.pop_back1()<<endl;
				break;
			case 4:
				cout<<Q.pop_front1()<<endl;
				break;	
			case 5:
				Q.display();
				break;
			case 6:
				Q.clear();
				break;
			case 7:
				cout<<Q.front1()<<endl;
				break;
			case 8:
				cout<<Q.back()<<endl;
				break;
			case 9:
				cout<<Q.empty()<<endl;
				break;
			case 10:
				cout<<Q.size()<<endl;
				break;
			case 11:
				cout<<"enter n , x - ";
				cin>>n>>num;
				Q.deque1(n,num);
				break;
			/*case 12:
				cout>>"enter n : "
				cin>>n;*/

			default:
				cout<<"wrong choice\n";
		}
	}
    return 0; 
} 
#include <bits/stdc++.h> 
using namespace std;  

struct node{
	int data;
	struct node *next;
	struct node *prev;
};
typedef struct node node;
node *front,*rear,*Q=NULL;

node* deque1(int n, int x){
	node *tmp;
	while(n--){
		tmp=(node*)malloc(sizeof(node));
		tmp->data=x;
		tmp->next=tmp->prev=NULL;
		if(Q==NULL){
			Q=tmp;
			front=rear=Q;
		}	
		else{
			rear->next=tmp;
			tmp->prev=rear;
			rear=tmp;
		}
	}
	
}

void push_back1(int x){
	node *tmp=(node*)malloc(sizeof(node));
	tmp->data=x;
	tmp->next=tmp->prev=NULL;
	if(Q==NULL){
		Q=tmp;
		front=rear=Q;
	}	
	else{
		rear->next=tmp;
		tmp->prev=rear;
		rear=tmp;
	}
}

int pop_back1(){
	int res;
	node *tmp;
	if(rear){
		tmp=rear;
		res=rear->data;
		if(rear->prev){
			rear=rear->prev;
			rear->next=NULL;
		}
		else{
			Q=front=rear=NULL;
		}
		delete(tmp);
		return res;
	}
	return -1;
}

int pop_front1(){
	int res;
	node *tmp;
	if(front){
		tmp=front;
		res=front->data;
		if(front->next){
			front=front->next;
			front->prev=NULL;
			Q=front;
		}
		else{
			Q=front=rear=NULL;
		}
		delete(tmp);
		return res;
	}
	return -1;
}

void push_front1(int x){
	node *tmp=(node*)malloc(sizeof(node));
	tmp->data=x;
	tmp->next=tmp->prev=NULL;
	if(Q==NULL){
		Q=tmp;
		front=rear=Q;
	}	
	else{
		front->prev=tmp;
		tmp->next=front;
		front=tmp;
		Q=front;
	}
}

void display(){
	node *tmp=Q;
	if(!Q){
		cout<<"DQ is empty\n";
		return;
	}
	while(tmp){
		cout<<tmp->data<<" ";
		tmp=tmp->next;
	}
	cout<<endl;
}

void clear(){
	node *tmp=Q;
	while(Q){
		tmp=Q;
		Q=Q->next;
		delete(tmp);
	}
	Q=front=rear=NULL;
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
	if(!Q)
		return true;
	return false;
}

int size(){
	int i=0;
	node* tmp=Q;
	while(tmp){
		i++;
		tmp=tmp->next;
	}
	return i;
}

int main(){
	//deque1(10,2);
	int ch,num;
	cout<<"1 - pushback\n"<<"2 - pushfront\n"<<"3 - popback\n"
		<<"4 - popfront\n"<<"5 - display\n"<<"6 - clear\n"
		<<"7 - front\n"<<"8 - back\n"<<"9 - empty\n"
		<<"10 - size\n"<<endl;
	//display();
	while(1){
		cout<<"enter choice : ";
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"enter no. - ";
				cin>>num;
				push_back1(num);
				break;
			case 2:
				cout<<"enter no. - ";
				cin>>num;
				push_front1(num);
				break;
			case 3:
				cout<<pop_back1()<<endl;
				break;
			case 4:
				cout<<pop_front1()<<endl;
				break;	
			case 5:
				display();
				break;
			case 6:
				clear();
				break;
			case 7:
				cout<<front1()<<endl;
				break;
			case 8:
				cout<<back()<<endl;
				break;
			case 9:
				cout<<empty()<<endl;
				break;
			case 10:
				cout<<size()<<endl;
				break;
			default:
				cout<<"wrong choice\n";
		}
	}
	return 0;
}
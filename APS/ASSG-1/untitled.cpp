#include <bits/stdc++.h> 
using namespace std;  

template <typename T>
class Deque{
	public:
		int Size=0, max=10;
		int front_pos, rear_pos;
		
		T *DQ,*resizedDQ;
		void deque(){
			DQ=(T*)malloc(sizeof(T)*10);
			rear_pos=-1;
			front_pos=-1;
		}

		void IncreaseSize(){
			max=max*2;
			resizedDQ=(T*)malloc(sizeof(T)*max);
			int i,j=0;
			for(i=front_pos;i!=rear_pos+1;){
				//cout<<DQ[i]<<" ";
				resizedDQ[j]=DQ[i];
				i=(i+1)%(max/2);
			}
			front_pos=rear_pos=-1;
			DQ=resizedDQ;
		}

		void push_back(T x){
			if(Size!=max){
				if(Size==0)
				{
					front_pos=rear_pos=0;
					DQ[0]=x;
				}
				else if(rear_pos==max-1){
					rear_pos=0;
					DQ[rear_pos]=x;
				}
				else{
					rear_pos++;
					DQ[rear_pos]=x;
				}
				Size++;
			}
			else{
				IncreaseSize();
			}
		}
		
		void push_front(T x){
			if(Size!=max){
				if(front_pos==0)
				{
					front_pos=max-1;
					DQ[front_pos]=x;
				}
				else {
					front_pos--;
					DQ[front_pos]=x;		
				}
				Size++;
			}
		}
		
		T pop_back(){
			if(Size!=max){
				int res=DQ[rear_pos];
				if(Size==1){
					rear_pos=front_pos=-1;
				}
				else if(rear_pos==0){
					rear_pos=max-1;
				}
				else{
					rear_pos--;
				}
				Size--;
				return res;
			}
			return -1;
		}

		T pop_front(){
			if(Size!=max){
				int res=DQ[front_pos];
				if(Size==1){
					rear_pos=front_pos=-1;
				}
				else if(front_pos==max-1){
					front_pos=0;
				}
				else{
					front_pos++;
				}
				Size--;
				return res;
			}
			return -1;
		}

		void display(){
			int i;
			if(Size>0){
				for(i=front_pos;i!=rear_pos+1;){
					cout<<DQ[i]<<" ";
					i=(i+1)%max;
				}
			}
			else{
				cout<<-1;
			}
			cout<<endl;
		}
		void clear(){
			Size=0;
			front_pos=rear_pos=-1;
		}
		bool empty(){
			if(Size==0)
				return true;
			return false;
		}
		T front(){
			if(Size>0){
				return DQ[front_pos];
			}
			else{
				cout<<"nothing to return"<<endl;
				exit(0);
			}
		} 
		T back(){
			if(Size>0){
				return DQ[rear_pos];
			}
			else{
				cout<<"nothing to return"<<endl;
				exit(0);
			}
		} 
		int size(){
			return Size;
		}
};


int main(){
	//deque1(10,2);
	Deque<int> Q;
	Q.deque();

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
				Q.push_back(num);
				break;
			case 2:
				cout<<"enter no. - ";
				cin>>num;
				Q.push_front(num);
				break;
			case 3:
				cout<<Q.pop_back()<<endl;
				break;
			case 4:
				cout<<Q.pop_front()<<endl;
				break;	
			case 5:
				Q.display();
				break;
			case 6:
				Q.clear();
				break;
			case 7:
				cout<<Q.front()<<endl;
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
			/*case 11:
				cout<<"enter n , x - ";
				cin>>n>>num;
				Q.deque1(n,num);
				break;
						*/
			default:
				cout<<"wrong choice\n";
		}
	}
	return 0;
}
#include <bits/stdc++.h> 
using namespace std;  

template <typename T>
class Deque{
	public:
		int Size=0, max=5;
		int front_pos, rear_pos;
		
		T *DQ,*resizedDQ,x;
		void deque(){
			Size=0;
			DQ=(T*)malloc(sizeof(T)*max);
			rear_pos=-1;
			front_pos=-1;
		}

		void deque(int n, T x){
			max=n*2;
			Size=0;
			DQ=(T*)malloc(sizeof(T)*max);
			rear_pos=-1;
			front_pos=-1;
			int i=0;
			while(n--){
				push_back(x);
			}
		}
		
		void IncreaseSize(){
			max=max*2;
			resizedDQ=(T*)malloc(sizeof(T)*max);
			int i,j=0,k=0;
			
			for(i=front_pos;k<Size;k++){
				resizedDQ[j]=DQ[i];
				//cout<<DQ[i]<<" "<<resizedDQ[j]<<" "<<i<<" "<<j<<endl;
				j++;
				i=(i+1)%(max/2);
			}
			delete(DQ);
			front_pos=0;
			rear_pos=j-1;
			DQ=resizedDQ;
		}

		void push_back(T x){
			if(Size==max){
				IncreaseSize();
			}
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
				//cout<<rear_pos<<" "<<endl;
			}
			Size++;
		}
		void push_front(T x){
			if(Size==max){
				IncreaseSize();
			}
			if(Size==0)
			{
				front_pos=rear_pos=0;
				DQ[0]=x;
			}
			else if(front_pos==0)
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
		
		T pop_back(){
			if(Size!=0){
				string res=DQ[rear_pos];
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
			cout<<"nothing to return\n";
			exit(0);
			//return -1;
		}

		T pop_front(){
			if(Size!=0){
				string res=DQ[front_pos];
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
			cout<<"nothing to return\n";
			exit(0);
			//return -1;
		}

		void display(){
			int i,k=0;
			if(Size>0){
				//cout<<front_pos<<" "<<rear_pos;
				for(i=front_pos;k<Size;k++){
					cout<<DQ[i]<<" ";
					//cout<<front_pos<<" "<<rear_pos<<" "<<i<<" "<<DQ[i]<<" "<<endl;
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
			//cout<<"max = "<<max<<endl;
			return Size;
		}
		void resize(T x, int d){
			if(d>Size){
				int Elements2push=d-Size;
				while(Elements2push--){
					push_back(x);
				}
			}
			else if(d<Size){
				int Elements2pop=Size-d;
				while(Elements2pop--){
					pop_back();
				}
			}
			return;
		}
};


int main(){
	//deque1(10,2);
	Deque<string> Q;
	//Q.deque();
	int d,n,fr,rr;
	//int ch,num,diffFromFront;
	int ch,diffFromFront;
	
	string num;
	/*cout<<"1 - pushback\n"<<"2 - pushfront\n"<<"3 - popback\n"
		<<"4 - popfront\n"<<"5 - display\n"<<"6 - clear\n"
		<<"7 - front\n"<<"8 - back\n"<<"9 - empty\n"
		<<"10 - size\n"<<"11 - resize(x,d)\n"<<"12 - D[n]"<<endl;
	*///display();
	
		while(1){
		//cout<<"enter choice : ";
		cin>>ch;
		switch(ch){
			case 1:
				//cout<<"enter no. - ";
				cin>>num;
				Q.push_front(num);
				//Q.display();
				break;	
			case 2:
				cout<<Q.pop_front()<<endl;
				//Q.display();
				break;	
			case 3:
				//cout<<"enter no. - ";
				cin>>num;
				Q.push_back(num);
				//Q.display();
				break;
			case 4:
				cout<<Q.pop_back()<<endl;
				//Q.display();
				break;
			case 5:
				Q.deque();
				break;			
			case 6:
				cin>>n>>Q.x;
				Q.deque(n,Q.x);
				break;
			case 7:
				cout<<Q.front()<<endl;
				break;
			case 8:
				cout<<Q.back()<<endl;
				break;
			case 9:
				if(Q.empty())
					cout<<"true"<<endl;
				else
					cout<<"false"<<endl;
				//cout<<Q.empty()<<endl;
				break;
			case 10:
				cout<<Q.size()<<endl;
				break;
			case 11:
				//cout<<"enter x , d - ";
				cin>>Q.x>>d;
				Q.resize(Q.x,d);
				break;
			case 12:
				Q.clear();
				break;
			case 13:
				//cout<<"enter n : ";
				cin>>n;
				if(n<0 || n>=Q.Size){
					cout<<-1<<endl;
					break;
				}
				fr=Q.front_pos;
				rr=Q.rear_pos;
				diffFromFront=Q.max-fr;
				n++;
				if( n > diffFromFront ){
					n-=diffFromFront;
					cout<<Q.DQ[n-1]<<endl;	
				}
				else{
					if(fr+n-1)	
						cout<<Q.DQ[fr+n-1]<<endl;
					else
						cout<<-1<<endl;
				}
				break;
			case 14:
				Q.display();
				break;			
			default:
				cout<<"wrong choice\n";
		}
	}
	return 0;
}
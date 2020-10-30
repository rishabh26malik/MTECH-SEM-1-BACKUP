#include <bits/stdc++.h> 
using namespace std;  
int fact[500000]={0};
int mult[500000]={0};
void multiply(string a, string b){
	string tmp,zeros="",prod;
	int len,n,m,carry,val,i,j,num,c=0,k,size,carry1;
	n=a.length();
	m=b.length();
	for(i=m-1;i>=0;i--){
		tmp=a;
		num=b[i]-'0';
		tmp=a+zeros;
		n=tmp.length();
		prod="";
		carry=0;
		cout<<tmp<<" "<<num<<" ";
		k=0;
		for(j=n-1;j>=0;j--){
			val=(num*(tmp[j]-'0')+carry)%10;
			prod=char(val+'0')+prod;
			carry=(num*(tmp[j]-'0')+carry)/10;
			/*if(i==m-1){
				mult[k]=val;
				k++;
			}
			else{
				mult[k]=(mult[k]+val+carry1)%10;
				carry1=(carry1+mult[k]+val)/10;
				k++;
			}*/			
		}
		while(carry){
			/*if(i==m-1)
				mult[k]=carry%10;
			else{
				mult[k]=(mult[k]+carry1+carry)%10;
			}
			carry1/=10;*/
			prod=char(carry+'0')+prod;
			carry=carry/10;
			//k++;
		}
		k=0;
		len=prod.length();
		carry=0;
		for(j=len-1;j>=0;j--){
			mult[k]=(mult[k]+(prod[j]-'0')+carry)%10;
			carry=(mult[k]+(prod[j]-'0')+carry)/10;;
			k++;
		}
		if(carry){
			mult[k]=carry;
			k++;
		}
		size=k;
		for(j=size-1;j>=0;j--)
			cout<<mult[j];
		c++;
		zeros+="0";
		cout<<" "<<prod<<endl;
	}

}
/*
int main(){
	string n,m;
	int exp;
	cin>>n>>m;
	//cin>>base;
	//cin>>exp;
	multiply(n,m);
	return 0;
}
*/

int main(){
	int carry=0,prod,n,num,size,i,j;
	cin>>num;
	fact[0]=1;
	size=1;
	for(i=2;i<=num;i++){
		carry=0;
		for(j=0;j<size;j++){
			prod=fact[j]*i+carry;
			fact[j]=prod%10;
			carry=prod/10;
		}
		while(carry > 0){
			fact[size]=carry%10;
			carry/=10;
			size++;
		}
		
	}
	cout<<size<<endl;
	for(i=size-1;i>=0;i--)
		cout<<fact[i];
	cout<<endl;
	return 0;
}
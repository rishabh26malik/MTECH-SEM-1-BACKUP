#include<bits/stdc++.h>
using namespace std;
int mult[500000]={0};
int fact[500000]={0};

string subtract(string a, string b){
	int n,m,i,j,valA,valB,borrow,diff;
	string sub="",result="";
	n=a.length();
	m=b.length();
	i=n-1;
	j=m-1;
	borrow=0;
	while(j>=0){
		valA=a[i]-'0';
		valB=b[j]-'0';
		if(borrow==1)
			valA--;
		if(valA >= valB){
			diff=valA-valB;
			
			borrow=0;
		}
		else{
			diff=10+valA-valB;
			borrow=1;
			
		}
		sub=char(diff+'0')+sub;
		//cout<<valA<<" "<<valB<<" "<<diff<<" "<<sub<<endl;
		i--;
		j--;
	}
	while(i>=0){
		valA=a[i]-'0';
		if(borrow==1){
			valA--;
			borrow=0;
		}
		sub=char(valA+'0')+sub;
		i--;
	}
	n=sub.length();
	for(i=0;i<n;i++)
		if(sub[i]!='0')
			break;
	for(;i<n;i++)
		result+=sub[i];

	//cout<<"sub : "<<result<<endl;
	return result;
	
}


string multiply(string a, string b){
	string tmp,zeros="",prod;
	int len,n,m,carry,val,i,j,num,k,size;
	n=a.length();
	m=b.length();
	memset(mult,0,sizeof(mult));
	for(i=m-1;i>=0;i--){
		num=b[i]-'0';
		tmp=a+zeros;
		n=tmp.length();
		prod="";
		carry=0;
		for(j=n-1;j>=0;j--){
			val=(num*(tmp[j]-'0')+carry)%10;
			prod=char(val+'0')+prod;
			carry=(num*(tmp[j]-'0')+carry)/10;		
		}
		if(carry){
			prod=char(carry+'0')+prod;
			carry=carry/10;
		}
		k=0;
		len=prod.length();
		carry=0;
		for(j=len-1;j>=0;j--){
			val=(mult[k]+(prod[j]-'0')+carry)%10;
			carry=(mult[k]+(prod[j]-'0')+carry)/10;;
			mult[k]=val;
			k++;
		}
		if(carry){
			mult[k]=carry;
			k++;
		}
		size=k;
		zeros+="0";
	}
	string result="";
	for(j=size-1;j>=0;j--){
		result+=char(mult[j]+'0');
		//cout<<(mult[i]+'0');
	}
	//cout<<result<<endl;
	return result;
}

int compare(string a, string b){
	if(a==b)
		return 0;
	if(a.length() > b.length())
		return 1;
	if(a.length() < b.length())
		return 2;
	int i,n=a.length();
	for(i=0;i<n;i++){
		if((a[i]-'0') > (b[i]-'0'))
		{
			return 1;
		}
		else if(a[i]-'0' < b[i]-'0')
		{
			return 2;
		}		
	}
	return 0;
}

string div(string dividend, string divisor){
	int lenD=dividend.length(), i,k,j,quotient;
	int len_div=divisor.length(), flag,flag2;
	string D, Q="", R="", rem="";
	string mul1,mul2,diff;
	k=0;
	for(i=0;i<lenD;){
		D=rem;
		while(i<lenD && k<len_div ){
			if(i<lenD){
				D+=dividend[i];
				i++;
				k++;
				Q+="0";
				flag=compare(D,divisor);
				if(flag==0 || flag==1)
					break;
			}
		}
		if(D.length()==len_div){
			quotient=(D[0]-'0')/(divisor[0]-'0');
		}
		else{
			quotient=((10*(D[0]-'0'))+(D[1]-'0'))/(divisor[0]-'0');
		}
		mul1=multiply(divisor, to_string(quotient));
		while( compare(D,mul1)==2 ){
			quotient--;
			mul1=multiply(divisor, to_string(quotient));
		}
		flag2=compare(D,mul1);
		if( flag2==0 ){
			Q+="1";
			k=0;
			rem="";	
		}
		else if( flag2==1 ){
			rem=subtract(D , mul1);
			k=rem.length();		
			Q+=to_string(quotient);
		}
		//cout<<D<<"-"<<Q<<"-"<<rem<<endl;
		if(i<lenD){
			rem+=dividend[i++];
			k++;
		}
		D=rem;
		
	}
	//cout<<"---------------------------\n";
	//cout<<D<<"-"<<Q<<"-"<<rem<<endl;
	flag=compare(D,divisor);
	if(flag==0)
		rem="";
	else if(flag==1){
		if(D.length()==len_div){
			quotient=(D[0]-'0')/(divisor[0]-'0');
		}
		else{
			quotient=((10*(D[0]-'0'))+(D[1]-'0'))/(divisor[0]-'0');
		}
		mul1=multiply(divisor, to_string(quotient));
		//flag2=compare(D,mul1);

		while( compare(D,mul1)==2 ){
			quotient--;
			mul1=multiply(divisor, to_string(quotient));
		}
		flag2=compare(D,mul1);

		if(flag2==0)
			rem="";
		else if(flag2==1){
			flag2=compare(D,mul1);
			if( flag2==0 ){
				Q+="1";
				rem="";	
			}
			else if( flag2==1 ){
				rem=subtract(D , mul1);
				Q+=to_string(quotient);
			}
		}
	}
	if(rem=="")
		rem="0";
	//cout<<D<<"-"<<Q<<"-"<<rem<<endl;
	return rem;
}

string gcd(string a, string b){
	if(b=="0")
		return a;
	string mod=div(a,b);
	return gcd(b,mod);	
}

void factorial(int num){
	int size,j,i,carry,prod;
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
	//cout<<size<<endl;
	for(i=size-1;i>=0;i--)
		cout<<fact[i];
	cout<<endl;
}

string power(string base, int exp){
	if(exp==0)
		return "1";
	if(exp==1)
		return base;
	string res=power(base,exp/2);
	//res = multiply(base,base);
	if(exp % 2 == 0){
		res = multiply(res,res);
		//cout<<exp<<" "<<res<<endl;
		return res;
	}
	else{
		res = multiply(res,res);
		//cout<<exp<<" "<<res<<endl;
		return multiply(base,res);
	}
}

int main(){
	int choice,t,num,exp,check;
	string base,a,b;
	cin>>t;
	while(t--){
		cin>>choice;
		switch(choice){
			case 1:				// power
				cin>>base>>exp;
				cout<<power(base,exp)<<endl;
				break;
			case 2:				// gcd
				cin>>a>>b;
				check=compare(a,b);
				if(check==0)
					cout<<a<<endl;
				else if(check==1)
					cout<<gcd(a,b)<<endl;
				else
					cout<<gcd(b,a)<<endl;
				break;
			case 3:				// factorial
				cin>>num;
				if(num==0 || num==1){
					cout<<1<<endl;
				}
				else
					factorial(num);
				break;
			
		}
	}
	return 0;
}
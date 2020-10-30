#include <bits/stdc++.h> 
using namespace std;



string subtract(string a, string b){
	int n,m,i,j,valA,valB,borrow,diff;
	string sub="";
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
		cout<<valA<<" "<<valB<<" "<<diff<<" "<<sub<<endl;
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
	return sub;
	//cout<<sub<<endl;
}

int compare(string a, string b ){
	if(a.length() > b.length())
		return 1;
	else if(a.length() < b.length())
		return 2;
	else{
		int i,n=a.length();
		for(i=0;i<n;i++){
			if((a[i]-'0') > (b[i]-'0'))
			{
				//subtract(a,b);
				return 1;
			}
			else if(a[i]-'0' < b[i]-'0')
			{
				//subtract(b,a);
				return 2;
			}
		}
		return 3;
	}
}

string gcd(string a, string b){
	if(a=="0")
		return b;
	if(b=="0")
		return a;
	if(a==b)
		return a;
	int cmp=compare(a,b);
	string diff;
	if(cmp==1){
		diff=subtract(a,b);
		cout<<diff<<endl;
		return gcd(diff,b);
	}
	else{
		diff=subtract(b,a);
		cout<<diff<<endl;
		return gcd(a,diff);
	}
}

int main()
{
	string a,b;
	cin>>a>>b;
	cout<<subtract(a,b)<<endl;
	//cout<<gcd(a,b)<<endl;
	return 0;
}
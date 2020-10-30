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
		//cout<<valA<<" "<<valB<<" "<<diff<<" "<<sub<<endl;
		i--;
		j--;
	}
	while(i>=0){
		valA=a[i]-'0';
		if(borrow==1){
			if(valA>0){
				valA--;
				borrow=0;
			}
			else{
				valA=9;
				borrow=1;
			}
			
		}
		
		sub=char(valA+'0')+sub;
		i--;
	}
	//cout<<a<<" "<<b<<" "<<sub<<endl;
	n=sub.length();
	for(i=0;i<n-1;i++){
		if(sub[i]!='0')
			break;
	}
	string result="";
	for(;i<n;i++)
		result+=sub[i];
	//sub=sub.substr(i,n-i);
	//cout<<sub<<" "<<result<<endl;
	return result;
	//cout<<sub<<endl;
}

int compare(string a, string b ){
	if(a==b)
		return 0;
	else if(a.length() > b.length())
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

string mod(string a, string b){
	while(compare(a,b)==1){
		a=subtract(a,b);
		cout<<a<<" "<<b<<endl;
		if(a.compare(b)==0)
			return "0";
	}
	return a;
}

string gcd(string a, string b){
	if(b=="0")
		return a;
	string MOD=mod(a,b);
	if(MOD=="0")
		return b;
	cout<<a<<" "<<b<<" "<<MOD<<endl;
	return gcd(b,MOD);
	
}

int main()
{
	string a,b;
	cin>>a>>b;
	string s1="4"; 
    string s2="4";
	//cout<<s1.compare(s2)<<endl;
	
	//cout<<a<<endl;
	//cout<<subtract(a,b)<<endl;
	cout<<gcd(a,b)<<endl;
	return 0;
}
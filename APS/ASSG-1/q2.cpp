#include <bits/stdc++.h> 
using namespace std;  
using namespace std::chrono; 

int fact[500000]={0};
int mult[500000]={0};

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
    //time_t start, end; 
    
	string n,m;
	int exp;
	cin>>n>>exp;
	//cin>>base;
	//cin>>exp;
	//multiply("5","5");
	//time(&start);
	string output=power(n,exp);
	//cout<<power(n,exp)<<endl;
	//time(&end);
	auto start = high_resolution_clock::now();
	cout<<output<<endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
	//double time_taken = double(end - start); 
	//cout << "Time taken by program is : " << fixed 
    //     << time_taken << setprecision(5); 
    //cout << " sec " << endl; 
	return 0;
}

/*
int main(){
	int carry=0,prod,n,num,size,i,j;
	cin>>num;
	fact[0]=1;
	size=1;
	//time_t start, end;
	//time(&start);
	auto start = high_resolution_clock::now();
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
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
	//time(&end);
	//double time_taken = double(end - start); 
    //cout << "Time taken by program is : " << fixed 
    //     << time_taken << setprecision(5); 
    //cout << " sec " << endl;
	cout<<size<<endl;
	//for(i=size-1;i>=0;i--)
	//	cout<<fact[i];
	//cout<<endl;
	return 0;
}
*/


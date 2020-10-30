#include <bits/stdc++.h> 
using namespace std;
int mult[500000]={0};

string division(string number, int divisor) 
{ 
    // As result can be very large store it in string 
    string ans; 
  
    // Find prefix of number that is larger 
    // than divisor. 
    int idx = 0; 
    int temp = number[idx] - '0'; 
    while (temp < divisor) 
        temp = temp * 10 + (number[++idx] - '0'); 
  
    // Repeatedly divide divisor with temp. After 
    // every division, update temp to include one 
    // more digit. 
    while (number.size() > idx) { 
        // Store result in answer i.e. temp / divisor 
        ans += (temp / divisor) + '0'; 
  
        // Take next digit of number 
        temp = (temp % divisor) * 10 + number[++idx] - '0'; 
    } 
  
    // If divisor is greater than number 
    if (ans.length() == 0) 
        return "0"; 
  
    // else return ans 
    return ans; 
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

string addition(string a, string b){
	int n,m,i,j,valA,valB,carry,sum;
	string add="";
	n=a.length();
	m=b.length();
	i=n-1;
	j=m-1;
	carry=0;
	while(j>=0){
		valA=a[i]-'0';
		valB=b[j]-'0';
		sum=(valA+valB+carry)%10;
		carry=(valA+valB+carry)/10;	
		add=char(sum+'0')+add;
		//cout<<valA<<" "<<valB<<" "<<sum<<" "<<add<<endl;
		i--;
		j--;
	}
	while(i>=0){
		valA=a[i]-'0';
		if(carry==1){
			if(valA < 9){
				sum=valA+carry;
				carry=0;
			}
			else{
				sum=0;
				carry=1;
			}
		}
		else
			sum=valA;
		//cout<<valA<<" "<<sum<<" "<<add<<endl;
		add=char(sum+'0')+add;
		i--;
	}
	if(carry){
		add=char(carry+'0')+add;
	}
	//cout<<a<<" "<<b<<" "<<sub<<endl;
	n=add.length();
	for(i=0;i<n-1;i++){
		if(add[i]!='0')
			break;
	}
	string result="";
	for(;i<n;i++)
		result+=add[i];
	return result;
}

void tooms(string num1, string num2){
	string x2,x1,x0,y2,y1,y0,a0,a1,tmp1,tmp2,a2,tmp3,tmp4,a3,a4;
	string tmp5,tmp6,a,b,c,d,e;
	int n,len,out1,out2;
	int neg,i,j,carry;
	len=num1.length();
	n=len/3;
	x2=num1.substr(0,n);
	x1=num1.substr(n,n);
	x0=num1.substr(n+n,n);
	len=num2.length();
	n=len/3;
	y2=num2.substr(0,n);
	y1=num2.substr(n,n);
	y0=num2.substr(n+n,n);
	cout<<x2<<" "<<x1<<" "<<x0<<endl;
	cout<<y2<<" "<<y1<<" "<<y0<<endl;
	// AT t=0
	a0=multiply(x0,y0);
	cout<<"a0 = "<<a0<<endl;
	
	// AT t=1
	a1=multiply( addition(x2,addition(x1,x0)) , addition(y2,addition(y1,y0)) );
	cout<<"a1 = "<<a1<<endl;
	
	// AT t=-1
	tmp1=addition(x2,x0);
	tmp2=addition(y2,y0);
	out1=compare(tmp1,x1);
	out2=compare(tmp2,y1);
	if((out1==1 && out2==1) || (out1==2 && out2==2) )
		neg=0;
	else if( out1==0 || out2==0 )
		a2="0";
	else
		neg=1;
	if( a2!="0" ){
		if(out1==1)
			tmp1=subtract(tmp1,x1);
		else
			tmp1=subtract(x1,tmp1);
		if(out2==1)
			tmp2=subtract(tmp2,y1);
		else
			tmp2=subtract(y1,tmp2);
		a2=multiply(tmp1,tmp2);
		if(neg==1)
			a2="-"+a2;
	}
	cout<<"a2 = "<<a2<<endl;

	// AT t=2
	tmp1=multiply(x2,"4");
	tmp2=multiply(x1,"2");
	tmp3=multiply(y2,"4");
	tmp4=multiply(y1,"2");
	a3=multiply( addition(tmp1 , addition(tmp2,x0)) , addition(tmp3 , addition(tmp4,y0)) );
	cout<<"a3 = "<<a3<<endl;

	// AT t=-2
	tmp5=addition(tmp1,x0);
	tmp6=addition(tmp3,y0);
	out1=compare(tmp5,tmp2);
	out2=compare(tmp6,tmp4);
	//cout<<tmp5<<" "<<tmp6<<endl;
	if((out1==1 && out2==1) || (out1==2 && out2==2) )
		neg=0;
	else if( out1==0 || out2==0 )
		a4="0";
	else
		neg=1;
	if( a4!="0" ){
		if(out1==1)
			tmp1=subtract(tmp5,tmp2);
		else
			tmp1=subtract(tmp2,tmp5);
		if(out2==1)
			tmp2=subtract(tmp6,tmp4);
		else
			tmp2=subtract(tmp4,tmp6);
		//cout<<tmp1<<" "<<tmp2<<endl;
		a4=multiply(tmp1,tmp2);
		if(neg==1)
			a4="-"+a4;
	}
	cout<<"a4 = "<<a4<<endl;
	/////////////////////
	e=a0;
	b=division(subtract((subtract(a3,a4)) , multiply(subtract(a1,a2),"2")),12);
	tmp1=addition(a3,a4);
	tmp2=multiply(a0,"2");
	tmp3=addition(a1,a2);
	tmp4=subtract(tmp1,tmp2);
	tmp5=subtract(tmp3,tmp2);
	tmp6=multiply(tmp5,"4");
	a=subtract(tmp4,tmp6);
	a=division(a,24);
	//a=division((subtract(addition(a3,a4) , multiply(a0,"2")) , multiply(subtract(addition(a1,a2),multiply(a0,"2")),"4")),24);
	d=subtract(division(subtract(a1,a2),2),b);
	c=subtract(a1,addition(addition(addition(a,b),d),e));
	cout<<"a = "<<a<<endl;
	cout<<"b = "<<b<<endl;
	cout<<"c = "<<c<<endl;
	cout<<"d = "<<d<<endl;
	cout<<"e = "<<e<<endl;
	string result="";

}

int main(){
	string num1,num2;
	int len,n;
	num1="831275469123";
	num2="897512436123";
	//cin>>num1>>num2;
	tooms(num1,num2);
	
	//cout<<addition(a,b)<<endl;
	return 0;
}
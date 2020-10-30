#include<bits/stdc++.h>
using namespace std;

int main()
{
	char buffer[15];
	int ret;
	while(1){
		ret=read(0,buffer,15);
		if(ret<15){
			buffer[ret]=0;
			cout<<buffer<<endl;
			break;
		}
		cout<<buffer<<endl;
	}
	return 1;
}

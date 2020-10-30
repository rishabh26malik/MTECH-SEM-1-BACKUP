



	//
		LATEST COPY


#include<bits/stdc++.h>
using namespace std;

struct EXP{
	string data;
	struct EXP *next;
};
typedef EXP EXP;

struct PostFix{
	string str;
	float num;
	bool isNum;
	char opn;
	struct PostFix *next;
};
typedef PostFix PostFix;

bool isOperator(char op){
	if( op=='-' || op=='+' || op=='*' || op=='/' || op=='%' || op=='(' || op==')' )
		return true;
	return false;
}

void PostFixInsert(string val, bool isOpr, PostFix **head, PostFix **last){
	PostFix *nd=(PostFix*)malloc(sizeof(PostFix));
	nd->next=NULL;
	
	if( !isOpr ){
		nd->isNum=true;
		nd->num=stof(val);
		//cout<<"stof done"<<endl;
	}
	else{
		nd->isNum=false;
		//string opn(1,val);
		nd->opn=val[0];
	}
	
	nd->str=val;
	if(*head==NULL){
		*head=nd;
		*last=nd;
	}
	else{
		(*last)->next=nd;
		*last=nd;
	}
}


void ExpInsert(string val, EXP **head, EXP **last){
	EXP *nd=(EXP*)malloc(sizeof(EXP));
	nd->next=NULL;
	nd->data=val;
	if(*head==NULL){
		*head=nd;
		*last=nd;
	}
	else{
		(*last)->next=nd;
		*last=nd;
	}
}

int precedence(char ch){
	if(ch=='/' || ch=='%' || ch=='*')
		return 2;
	else if(ch=='+' || ch=='-')
		return 1;
	return -1;
}

string removeSpaces(string exp){
	string newExp="";
	int i,len=exp.length();
	for(i=0;i<len;i++)
		if(exp[i]!=' ')
			newExp+=exp[i];
	return newExp;
}

void separateExp(string exp, EXP **head){
	//exp="-11+22*(-33/44-55)*(66+77*88)-99";
	//exp="111*88/65+432+5-5/15*89";
	//exp="11+22*33/44-55";
	//exp="((11.1*8.8)/65)+43.2+(5-(5/15)*.9)";
	exp="(-11*-22)*-33/44-55";
	int i=0,len=exp.length(),neg=0;
	EXP *nd,*last=NULL;
	string num="";
	//	11+22*(33/(44-55))+1
	for(i=0;i<len;i++){
		if(isOperator(char(exp[i]))){
			//cout<<exp[i]<<" ";
			if(exp[i]=='-' && exp[i+1]>='0' && exp[i+1]<='9'){
				neg=1;
				if(i==0)
					continue;
				//if(isOperator(char(exp[i-1])) && exp[i-1]!=')' && exp[i-1]!='(' ){
				if(isOperator(char(exp[i-1])) && exp[i-1]=='(' ){
					continue;
				}
				else if( isOperator(char(exp[i-1])) && exp[i-1]==')' ) {
					exp[i]='+';	
				}
				else if( isOperator(char(exp[i-1])) ) {
					continue;
					//exp[i]='+';	
				}
				else if( !isOperator(char(exp[i-1])) ) {	
					exp[i]='+';	
				}
				//string sign="+";
				//string opn(1,sign);
				//exp[i]='+';
			}
			//else
				string opn(1,exp[i]);
			nd=(EXP*)malloc(sizeof(EXP));
			nd->next=NULL;
			nd->data=opn;
			if(*head==NULL){
				*head=nd;
				last=nd;
			}
			else{
				last->next=nd;
				last=nd;
			}
			num="";
		}
		else{
			//cout<<exp[i]<<" ";
			num+=exp[i];
			if(i+1==len || (i+1 < len && isOperator(exp[i+1]))){
				nd=(EXP*)malloc(sizeof(EXP));
				nd->next=NULL;
				if(neg){
					num="-"+num;
					neg=0;
				}
				nd->data=num;
				if(*head==NULL){
					*head=nd;
					last=nd;
				}
				else{
					last->next=nd;
					last=nd;
				}	
				num="";
			}
		}
	}
}

void toPostfix(EXP *exp, PostFix **postfix){
	stack <char> S;
	string operand, opn;
	char operatr;
	bool isOperand;
	PostFix *nd,*last=NULL;
	//cout<<"aa"<<endl;
	while(exp!=NULL){
		//cout<<"bb"<<endl;
		operand=exp->data;
		if( operand.length()==1 ){
			if( !isOperator(operand[0]) )
				isOperand=true;
			else
				isOperand=false;	
		}
		else{
			isOperand=true;
		}
		//isOperand=!isOperator(operand[0]) || ( isOperator(operand[0]) && !isOperator(operand[1]) );
		//cout<<operand;
		if( isOperand ){
			//cout<<operand<<endl;
			PostFixInsert(operand,false,postfix,&last);
		}
		else {
			//cout<<'a'<<" ";
			operatr=operand[0];
			if(S.empty() || operatr=='(' ){
				//cout<<operatr<<endl;
				S.push(operatr);
			}
			else if ( operatr== ')'){
				while( S.top() != '(' ){
					//cout<<S.top()<<" ";
					string opn(1,S.top());
					//opn=S.top();
					PostFixInsert(opn,true,postfix,&last);
					S.pop();	
				}

				//cout<<endl;
				S.pop();
			}
			else {
				while( !S.empty() && precedence(S.top()) >= precedence(operatr) ){
					string opn(1,S.top());
					//opn=S.top();
					//cout<<S.top()<<" ";
					PostFixInsert(opn,true,postfix,&last);			
					S.pop();
					if(!S.empty() && S.top()=='(')
						break;
				}
				//cout<<endl;
				S.push(operatr);	
			}
		}
		exp=exp->next;
		//isOperand=1-isOperand;
	}
	while(!S.empty()){
		//cout<<S.top()<<" ";
		string opn(1,S.top());
		PostFixInsert(opn,true,postfix,&last);			
		S.pop();
	}
}

float evaluateExp(PostFix *postfix){
	stack <float> S;
	float num1, num2;
	while(postfix!=NULL){
		if(postfix->isNum){
			S.push(postfix->num);
		}
		else{
			num1=S.top();
			S.pop();
			num2=S.top();
			S.pop();
			switch(postfix->opn){
				case '*':
					S.push(num2 * num1);
					break;
				case '+':
					S.push(num2 + num1);
					break;
				case '-':
					S.push(num2 - num1);
					break;
				case '/':
					S.push(num2 / num1);
					break;
				case '%':
					S.push(int(num2) % int(num1));
					break;
			}
		}
		postfix=postfix->next;
	}
	return S.top();
}

int main(){
	string exp;
	//getline(cin,exp);
	//exp="11+22*(33/44-55)*(66+77*88)-99";
	//exp="11+22*(33/(44-55))+1";
	exp=removeSpaces(exp);
	EXP *sepExp=NULL,*tmp;
	PostFix *postfix=NULL,*tmp2;
	separateExp(exp,&sepExp);
	tmp=sepExp;
	while(tmp!=NULL){
		cout<<tmp->data<<" ";
		tmp=tmp->next;
	}
	cout<<endl;
	toPostfix(sepExp, &postfix);
	cout<<endl;
	tmp2=postfix;
	while(tmp2!=NULL){
		if( tmp2->isNum )
			cout<<tmp2->num<<" ";
		else
			cout<<tmp2->opn<<" ";
		//cout<<tmp2->str<<" ";
		tmp2=tmp2->next;
	}
	cout<<endl;
	cout<<evaluateExp(postfix)<<endl;
	return 0;
}


/*

void toPostfix(EXP *exp, PostFix **postfix){
	stack <char> S;
	string operand, opn;
	char operatr;
	int isOperand=1;
	PostFix *nd,*last=NULL;
	cout<<33<<" ";
	while(exp!=NULL){
		cout<<11<<" ";
		operand=exp->data;
		//cout<<operand;
		if( isOperand ){
			cout<<operand<<" ";
			PostFixInsert(operand,false,postfix,&last);
		}
		else {
			operatr=operand[0];
			if(S.empty() || operatr=='(' ){
				cout<<operatr<<" ";
				S.push(operatr);
			}
			else if ( operatr== ')'){
				while( S.top() != '(' ){
					cout<<S.top()<<" ";
					string opn(1,S.top());
					//opn=S.top();
					PostFixInsert(opn,true,postfix,&last);
					S.pop();	
				}
				S.pop();
			}
			else {
				while( !S.empty() && precedence(S.top()) >= precedence(operatr) ){
					string opn(1,S.top());
					//opn=S.top();
					cout<<S.top()<<" ";
					PostFixInsert(opn,true,postfix,&last);			
					S.pop();
					if(!S.empty() && S.top()=='(')
						break;
				}
				S.push(operatr);	
			}
		}
		exp=exp->next;
		isOperand=1-isOperand;
	}
	while(!S.empty()){
		cout<<S.top()<<" ";
		string opn(1,S.top());
		PostFixInsert(opn,true,postfix,&last);			
		S.pop();
	}
}


*/



-----------------------------------------------------------------------------------------------------------------------------

#include<bits/stdc++.h>
using namespace std;

struct EXP{
	string data;
	struct EXP *next;
};
typedef EXP EXP;

struct PostFix{
	string str;
	float num;
	bool isNum;
	char opn;
	struct PostFix *next;
};
typedef PostFix PostFix;

bool isOperator(char op){
	if( op=='-' || op=='+' || op=='*' || op=='/' || op=='%' || op=='(' || op==')' )
		return true;
	return false;
}

void PostFixInsert(string val, bool isOpr, PostFix **head, PostFix **last){
	PostFix *nd=(PostFix*)malloc(sizeof(PostFix));
	nd->next=NULL;
	
	if( !isOpr ){
		nd->isNum=true;
		nd->num=stof(val);
		//cout<<"stof done"<<endl;
	}
	else{
		nd->isNum=false;
		//string opn(1,val);
		nd->opn=val[0];
	}
	
	nd->str=val;
	if(*head==NULL){
		*head=nd;
		*last=nd;
	}
	else{
		(*last)->next=nd;
		*last=nd;
	}
}


void ExpInsert(string val, EXP **head, EXP **last){
	EXP *nd=(EXP*)malloc(sizeof(EXP));
	nd->next=NULL;
	nd->data=val;
	if(*head==NULL){
		*head=nd;
		*last=nd;
	}
	else{
		(*last)->next=nd;
		*last=nd;
	}
}

int precedence(char ch){
	if(ch=='/' || ch=='%' || ch=='*')
		return 2;
	else if(ch=='+' || ch=='-')
		return 1;
	return -1;
}

string removeSpaces(string exp){
	string newExp="";
	int i,len=exp.length();
	for(i=0;i<len;i++)
		if(exp[i]!=' ')
			newExp+=exp[i];
	return newExp;
}

void separateExp(string exp, EXP **head){
	//exp="11+22*(33/44-55)*(66+77*88)-99";
	// "111*88/65+432+5-5/15*89"
	exp="11+22*33/44-55";
	//exp="((11.1*8.8)/65)+43.2+(5-(5/15)*.9)";
	int i=0,len=exp.length(),c=0;
	EXP *nd,*last=NULL;
	string num="";
	//	11+22*(33/(44-55))+1
	for(i=0;i<len;i++){
		c++;
		if(isOperator(char(exp[i]))){
			//cout<<exp[i]<<" ";
			string opn(1,exp[i]);
			nd=(EXP*)malloc(sizeof(EXP));
			nd->next=NULL;
			nd->data=opn;
			if(*head==NULL){
				*head=nd;
				last=nd;
			}
			else{
				last->next=nd;
				last=nd;
			}
			num="";
		}
		else{
			//cout<<exp[i]<<" ";
			num+=exp[i];
			if(i+1==len || (i+1 < len && isOperator(exp[i+1]))){
				nd=(EXP*)malloc(sizeof(EXP));
				nd->next=NULL;
				nd->data=num;
				if(*head==NULL){
					*head=nd;
					last=nd;
				}
				else{
					last->next=nd;
					last=nd;
				}	
				num="";
			}
		}
	}
}

void toPostfix(EXP *exp, PostFix **postfix){
	stack <char> S;
	string operand, opn;
	char operatr;
	bool isOperand;
	PostFix *nd,*last=NULL;
	//cout<<"aa"<<endl;
	while(exp!=NULL){
		//cout<<"bb"<<endl;
		operand=exp->data;
		isOperand=!isOperator(operand[0]);
		//cout<<operand;
		if( isOperand ){
			//cout<<operand<<endl;
			PostFixInsert(operand,false,postfix,&last);
		}
		else {
			operatr=operand[0];
			if(S.empty() || operatr=='(' ){
				//cout<<operatr<<endl;
				S.push(operatr);
			}
			else if ( operatr== ')'){
				while( S.top() != '(' ){
					//cout<<S.top()<<" ";
					string opn(1,S.top());
					//opn=S.top();
					PostFixInsert(opn,true,postfix,&last);
					S.pop();	
				}

				//cout<<endl;
				S.pop();
			}
			else {
				while( !S.empty() && precedence(S.top()) >= precedence(operatr) ){
					string opn(1,S.top());
					//opn=S.top();
					//cout<<S.top()<<" ";
					PostFixInsert(opn,true,postfix,&last);			
					S.pop();
					if(!S.empty() && S.top()=='(')
						break;
				}
				//cout<<endl;
				S.push(operatr);	
			}
		}
		exp=exp->next;
		//isOperand=1-isOperand;
	}
	while(!S.empty()){
		//cout<<S.top()<<" ";
		string opn(1,S.top());
		PostFixInsert(opn,true,postfix,&last);			
		S.pop();
	}
}

float evaluateExp(PostFix *postfix){
	stack <float> S;
	float num1, num2;
	while(postfix!=NULL){
		if(postfix->isNum){
			S.push(postfix->num);
		}
		else{
			num1=S.top();
			S.pop();
			num2=S.top();
			S.pop();
			switch(postfix->opn){
				case '*':
					S.push(num2 * num1);
					break;
				case '+':
					S.push(num2 + num1);
					break;
				case '-':
					S.push(num2 - num1);
					break;
				case '/':
					S.push(num2 / num1);
					break;
				case '%':
					S.push(int(num2) % int(num1));
					break;
			}
		}
		postfix=postfix->next;
	}
	return S.top();
}

int main(){
	string exp;
	//getline(cin,exp);
	//exp="11+22*(33/44-55)*(66+77*88)-99";
	//exp="11+22*(33/(44-55))+1";
	exp=removeSpaces(exp);
	EXP *sepExp=NULL,*tmp;
	PostFix *postfix=NULL,*tmp2;
	separateExp(exp,&sepExp);
	tmp=sepExp;
	while(tmp!=NULL){
		cout<<tmp->data<<" ";
		tmp=tmp->next;
	}
	cout<<endl;
	toPostfix(sepExp, &postfix);
	cout<<endl;
	tmp2=postfix;
	while(tmp2!=NULL){
		if( tmp2->isNum )
			cout<<tmp2->num<<" ";
		else
			cout<<tmp2->opn<<" ";
		//cout<<postfix->str<<" ";
		tmp2=tmp2->next;
	}
	cout<<endl;
	cout<<evaluateExp(postfix)<<endl;
	return 0;
}


/*

void toPostfix(EXP *exp, PostFix **postfix){
	stack <char> S;
	string operand, opn;
	char operatr;
	int isOperand=1;
	PostFix *nd,*last=NULL;
	cout<<33<<" ";
	while(exp!=NULL){
		cout<<11<<" ";
		operand=exp->data;
		//cout<<operand;
		if( isOperand ){
			cout<<operand<<" ";
			PostFixInsert(operand,false,postfix,&last);
		}
		else {
			operatr=operand[0];
			if(S.empty() || operatr=='(' ){
				cout<<operatr<<" ";
				S.push(operatr);
			}
			else if ( operatr== ')'){
				while( S.top() != '(' ){
					cout<<S.top()<<" ";
					string opn(1,S.top());
					//opn=S.top();
					PostFixInsert(opn,true,postfix,&last);
					S.pop();	
				}
				S.pop();
			}
			else {
				while( !S.empty() && precedence(S.top()) >= precedence(operatr) ){
					string opn(1,S.top());
					//opn=S.top();
					cout<<S.top()<<" ";
					PostFixInsert(opn,true,postfix,&last);			
					S.pop();
					if(!S.empty() && S.top()=='(')
						break;
				}
				S.push(operatr);	
			}
		}
		exp=exp->next;
		isOperand=1-isOperand;
	}
	while(!S.empty()){
		cout<<S.top()<<" ";
		string opn(1,S.top());
		PostFixInsert(opn,true,postfix,&last);			
		S.pop();
	}
}


*/
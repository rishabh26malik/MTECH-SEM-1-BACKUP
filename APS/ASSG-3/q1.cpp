#include<bits/stdc++.h>
using namespace std;

struct tuple1{
    int first, second, index;
};
typedef struct tuple1 tuple1;

bool cmp(tuple1 a, tuple1 b){
    if(a.first < b.first)
        return true;
    else if(a.first==b.first && a.second < b.second)
        return true;
    //else if(a.first==b.first && a.second == b.second)
    //    return true;
    return false;
}

int main()
{
    string str;
    cin>>str;
    vector <int> power;
    int j, i, n=str.length(), pow=1;
    int P[100][100];
    while(pow <= 100000){
        power.push_back(pow);
        pow*=2;
    }
    cout<<"after power makeing...\n";
    tuple1 L[n];
    cout<<"step 1 - ";
    for(i=0;i<n;i++){
        P[0][i]=str[i]-'a';
        cout<<P[0][i]<<" ";
    }
    cout<<endl;
    int step=1;
    for(i=1; i<power[i-1]<n && i<n; i++, step++){
        for(j=0;j<n;j++){
            L[j].index=j;
            L[j].first=P[i-1][j];
            L[j].second=(j+power[i-1]<n) ? P[i-1][j+power[i-1]] : -1;
        }
        sort(L, L+n, cmp);
        for(j=0;j<n;j++){
            cout<<L[j].index<<"  "<<L[j].first<<"  "<<L[j].second<<endl;
        }
        for(j=0; j<n ;j++){
            P[i][L[j].index] = ((j>1 && L[j].first==L[j-1].first && L[j].second==L[j-1].second) ? P[i][L[j-1].first] : j);
        }
        cout<<"step "<<step<<"- ";
        for(j=0;j<n;j++)
            cout<<P[step][j]<<" ";
        cout<<endl;
        cout<<"--------------------------\n\n";
    }
 	return 1;
}

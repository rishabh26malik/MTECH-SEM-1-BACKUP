#include<bits/stdc++.h>
using namespace std;

struct tuple1{
    int first, second, index;
    pair <int,int>p;
};
typedef struct tuple1 tuple1;

bool cmp(tuple1 a, tuple1 b){
    if(a.p.first < b.p.first)
        return true;
    else if(a.p.first==b.p.first && a.p.second < b.p.second)
        return true;
    //else if(a.first==b.first && a.second == b.second)
    //    return true;
    return false;
}

void print(vector <tuple1> suffix, int n, vector<int> rank){
    for(int i=0;i<n;i++){
        cout<<suffix[i].index<<" "<<suffix[i].p.first<<" "<<suffix[i].p.second<<endl;
    }
    for(int i=0;i<n;i++)
        cout<<rank[i]<<" ";
    cout<<"\n-----------------\n";
}

void kasai(string str, vector <tuple1> suffix, int n, vector<int> &lcp){
    int i, j, k=0, len=0;
    
    for(k=0;k<n;k++){
        i=suffix[k].index;
        j=suffix[k+1].index;
        len=0;
        if(k==n-1){
            len=0;
            lcp[k]=len;
            continue;
        }

        cout<<i<<j<<endl;
        while(i<n && j<n){
            cout<<str[i];
            if(str[i]==str[j])
                len++;
            else
                break;
            i++;
            j++;
        }
        cout<<endl;
        lcp[k]=len;
        //if(len>0)
        //    len=len-1;
    }
}

void minLexStr(string str, vector <tuple1> suffix, int n){
    int i, tmp=n;
    i=suffix[0].index;
    while(tmp--){
        cout<<str[i];
        i=(i+1)%n;
    }
    cout<<endl;
}

int main()
{
    //string str="smallma";
    //string str="small";
    string str="banana";
    //cin>>str;
    int j, i, n=str.length(), pow=1, mn, mx, k;
    vector <tuple1> suffix(n);
    vector<int> lcp(n,0);
    vector <int> rank(n,-1);
    for(i=0;i<n;i++){
        suffix[i].index=i;  
        suffix[i].p.first=str[i]-'a';
        suffix[i].p.second=(i+pow < n) ? str[i+pow]-'a' : -1;
    }
    //print(suffix,n);
    sort(suffix.begin(), suffix.end(), cmp);
    //print(suffix,n,rank);
    pow=4;
    while(pow<2*n){
        int next, pos=0;
        int prev=suffix[0].p.first;
        suffix[0].p.first=pos;
        rank[suffix[0].index]=0;
        for(i=1;i<n;i++){
            
            if(suffix[i].p.first==prev && suffix[i].p.second==suffix[i-1].p.second){
                prev=suffix[i].p.first;
                suffix[i].p.first=pos;
            }
            else{                
                prev=suffix[i].p.first;
                pos+=1;
                suffix[i].p.first=pos;
            }
            rank[suffix[i].index]=i;
            //suffix[i].second=(next < n)? suffix[rank[next]].second: -1; 
        
        }
        //for(i=0;i<n;i++){
        //    rank[suffix[i].index]=i;
        //}
        for (int i = 0; i < n; i++) 
        { 
            int nextindex = suffix[i].index + pow/2; 
            suffix[i].p.second = (nextindex < n)? 
                                  suffix[rank[nextindex]].p.first: -1; 
        }
        sort(suffix.begin(), suffix.end(), cmp);
        //print(suffix,n,rank);
        pow*=2;
    }
    for(i=0;i<n;i++){
        cout<<suffix[i].index<<" "<<str.substr(suffix[i].index)<<endl;
    }

    minLexStr(str, suffix, n);

    kasai(str, suffix, n, lcp);
    for(i=0;i<n;i++)
        cout<<lcp[i]<<" ";
    cout<<endl;
    vector <int> pal(n,0);
    cin>>k;
    mx=-1;
    for(i=0;i<n-k;i++){
        mn=INT_MAX;
        for(j=i;j<i+k;j++){
            mn=min(mn,lcp[j]);
        }
        cout<<mn<<" ";
        mx=max(mx,mn);
    }
    cout<<endl;
    cout<<mx;
 	return 1;
}

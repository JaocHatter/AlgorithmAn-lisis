#include<bits/stdc++.h>
#define forn(i,a,n) for(int i=a;i<n;i++)
#define pb push_back
using namespace std;
int main(){
    int n,s;
    vector<int> coins;
    scanf("%d %d",&n,&s);
    forn(i,0,n){
        int k;
        cin>>k;
        coins.pb(k);
    }
    vector<int> ways(s+1,INT_MAX);
    ways[0] = 0;
    for(int i = 1;i<=s;i++){
        for(int x: coins){
            if(i - x >= 0){
                if(ways[i-x]!=INT_MAX){
                    ways[i] = min(ways[i],ways[i-x]+1);
                }
            }
        }
    }
    int rpt = ways[s] != INT_MAX? ways[s]:-1;
    cout<<rpt;
    return 0; 
}
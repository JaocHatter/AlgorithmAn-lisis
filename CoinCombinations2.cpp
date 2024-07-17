#include<bits/stdc++.h>
#define forn(i,a,n) for(int i=a;i<n;i++)
#define pb push_back
#define ll long long
using namespace std;
const ll MOD = 1e9+7;
int main(){
    int n,s;
    vector<int> coins;
    scanf("%d %d",&n,&s);
    forn(i,0,n){
        int k;
        cin>>k;
        coins.pb(k);
    }
    vector<int> ways(s+1,0);
    ways[0] = 1;
    for(int i = 1;i<=s;i++){
        for(int x: coins){
            if(i - x >= 0){
                if(ways[i-x]!=0){
                    ways[i] += 1;
                    ways[i]%=MOD;
                }
            }
        }
    }
    cout<<ways[s];
    return 0; 
}
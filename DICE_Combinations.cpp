#include<bits/stdc++.h>
#define ll long long
#define forn(i,n) for(int i=0;i<n;i++)
using namespace std;

const ll MOD = 1e9+7;
int main(){
    vector<ll> ways(1000000,0);
    ways[0] = 1;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=6;j++){
            if(i - j >= 0){
                if(ways[i-j] != 0){
                    ways[i] += ways[i-j];
                    ways[i]%=MOD;
                }
            }else break;
        }
    }
    cout<<ways[n];
    return 0;
}
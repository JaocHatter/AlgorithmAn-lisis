#include<bits/stdc++.h>
#define forn(i,a,n) for(int i=a;i<n;i++)
#define pii pair<int,int>
using namespace std;
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));
    vector<pii> obj(n);
    forn(i,0,n) scanf("%d",&obj[i].first);
    forn(j,0,n) scanf("%d",&obj[j].second);
    forn(i,1,n+1){
        forn(j,1,m+1){
            dp[i][j] = dp[i-1][j];
            if(j - obj[i-1].first >= 0){
                dp[i][j] = max(dp[i][j],dp[i-1][j - obj[i-1].first]+obj[i-1].second);
            }
        }
    }
    cout<<dp[n][m]; 
    return 0;   
}
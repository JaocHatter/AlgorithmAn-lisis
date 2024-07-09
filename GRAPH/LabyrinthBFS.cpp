#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int> 
#define forn(i,n) for(int i=0;i<n;i++)
int a1,a2,b1,b2;
pii moves[4] = {{0,1},{1,0},{-1,0},{0,-1}};
int n,m;
bool visitados[1000][1000];
int dist[1000][1000];
char how[1000][1000],c;
int main(){
    scanf("%d %d",&n,&m);
    
    //itero por la tabla, si aparece #, no pasar por aca y marcar como visitado
    forn(i,n){  
        forn(j,m){
            scanf(" %c", &c);
            if(c == '#') visitados[i][j] = true;
            else if(c =='A'){
                a1 = i;
                a2 = j;
            }else if(c=='B'){
                b1 = i;
                b2 = j;
            }
        }
    }

    queue<pii> q;
    q.push({a1,a2});
    visitados[a1][a2] = true;
    while(!q.empty()){
        pii k = q.front();
        q.pop();
        forn(i,4){
            int mx = moves[i].first ,my = moves[i].second;
            int p1 = k.first + mx ,p2 = k.second + my; 
            if(p1 < n && p1 >= 0 && p2 < m && p2 >=0 && !visitados[p1][p2]){
                if(i == 0) how[p1][p2] = 'R'; 
                else if(i == 1) how[p1][p2] = 'D';
                else if(i == 2) how[p1][p2] = 'U';
                else if(i == 3) how[p1][p2] = 'L';
                visitados[p1][p2] = true;
                dist[p1][p2] = dist[k.first][k.second] + 1;
                q.push({p1,p2});
            }   
        }
    }

    if(!visitados[b1][b2]){
        cout<<"NO";
    }else{
        char success[1000000];
        int aux1 = b1,aux2 = b2;
        cout<<"YES"<<endl;
        cout<<dist[b1][b2]<<endl;
        for(int i = dist[b1][b2] ; i>0 ; i--){
            char x = how[aux1][aux2];
            success[i] = x;
            if(x == 'U'){
                aux1 = aux1 + 1;
            }else if(x == 'D'){
                aux1 = aux1 - 1;
            }else if(x == 'L'){
                aux2 = aux2 + 1;
            }else if(x == 'R'){
                aux2 = aux2 - 1;
            }
        }
        for(int i=1;i<=dist[b1][b2];i++) cout<<success[i];
    }
    return 0;
}
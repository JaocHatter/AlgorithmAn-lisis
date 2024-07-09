#include<bits/stdc++.h>
using namespace std;

void generateBinaryString(int n){
    string init = "";
    vector<string> stack = {init};
    while(!stack.empty()){
        string aux = stack.back();
        stack.pop_back();
        if(aux.length() == n){
            cout<<aux<<endl;
            continue;
        }
        for(int i=0;i<2;i++){
            string newstr = aux + to_string(i);
            stack.push_back(newstr);
        }
    }
}
int main(){
    int n;
    cin>>n;
    generateBinaryString(n);
    return 0;
}
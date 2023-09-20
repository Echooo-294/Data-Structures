#include "bp_tree.hpp"
#include "data.h"
#include <cstring>
#include <iostream>

using std::cout;

int main(){
    freopen("out.txt","w",stderr);
    const int N=20; // 0 <= N <= 400, or it will overflow
    bp_tree<int,char*> tree;
    for(int i = 20; i>=0 ; i--){
        tree.insert(i,phones[i]);
    }
    for(int i = 0; i < N; i ++){
        if(tree.find(i)){
            cout << "FOUNDED " << i << "\n";
        };
    }
}
#include<cstring>
using namespace std;

const int M = 20; // 哈希表的长度，同时也是取模运算的模数

// int ：取模
int h(int x){
    return x % M;
}

// char* : 直接求和取模
int h(char* x) {
    int i, sum;
    for (sum = 0, i = 0; x[i] != '\0'; i++) {
        sum += (int)x[i];
    }
    return sum % M;
}

// char* : 4位加权求和取模
int sfold(char* key){
    unsigned int *lkey = (unsigned int *)key;
    int intlength = strlen(key)/4;
    unsigned int sum = 0;
    for (int i = 0; i < intlength; i++)
        sum += lkey[i];

    // 处理字符串剩余不足四位的部分
    int extra = strlen(key) - intlength * 4;
    char temp[4];
    lkey = (unsigned int *)temp;
    lkey[0] = 0;
    for(int i=0;i<extra;i++)
        temp[i] = key[intlength*4+i];
    sum += lkey[0];

    return sum % M;
}
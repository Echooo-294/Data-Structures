#include <cstring>
#include <iostream>
using namespace std;

// 判断是否有错误产生，用于终止程序，打印错误信息
void Assert(bool mustTrue, char* str) {
    if (!mustTrue) {
        cout << str << endl;
        abort();
    }
}

// 哈希表中的存储的键值对结构
template <typename Key, typename E>
class KVpair {
   private:
    Key KEY; // 存储键
    E VALUE; // 存储值

   public:
    KVpair() {}

    KVpair(Key k, E e) {
        KEY = k;
        VALUE = e;
    }

    void setKey(Key k) { KEY = k; } // 设置键

    Key key() { return KEY; } // 返回键

    E value() { return VALUE; } // 返回值
};

// 书上多出来的结构，没发现有用在哪里
template <typename Key, typename E>
class Dictionary {};

// 使用线性探测、二次探测方法实现闭哈希表

// 哈希表本表
template <typename Key, typename E>
class hashdict : public Dictionary<Key, E> {
   private:
    KVpair<Key, E>* HT;  // 存放哈希表内容
    int M;               // 最大容量
    int currcnt;         // 当前哈希表存放元素数目
    Key EMPTY;           // 自定义零值

    // 通过注释的方式选用 探测函数
    // int p(Key K, int i) const { return i; }  // 简单的线性探测函数
    int p(Key K, int i) const { return i*i; }  // 简单的二次探测函数


    int h(int x) const { return x % M; }  // int 类型哈希函数，直接取模
    int h(char* x) {                      // char* 类型哈希函数，求和取模
        int i, sum;
        for (sum = 0, i = 0; x[i] != '\0'; i++) {
            sum += (int)x[i];
        }
        return sum % M;
    }

    void hashInsert(const Key&, const E&);  // 实现对于哈希表的插入
    E hashSearch(const Key&) const;         // 实现对于哈希表的查找

   public:
    hashdict(int sz, Key k) {  // 初始化哈希表
        M = sz;
        EMPTY = k;
        currcnt = 0;
        HT = new KVpair<Key, E>[sz];
        for (int i = 0; i < M; i++) {
            (HT[i]).setKey(EMPTY);  // 将所有位置都标记为空
        }
    }

    ~hashdict() { delete HT; }

    // 对外的查找接口，通过键在哈希表中找值
    E find(const Key& k) const { return hashSearch(k); }

    // 查询表中所存元素数目
    int size() { return currcnt; }

    // 对外的插入接口
    void insert(const Key& k, const E& it) {
        Assert(currcnt < M, "Hash is full");  // 哈希表已满
        hashInsert(k, it);
        currcnt++;
    }
};

// 哈希表中键值对插入的实现
template <typename Key, typename E>
void hashdict<Key, E>::hashInsert(const Key& k, const E& e) {
    int home;
    int pos = home = h(k);

    // 在插入的过程中，发现产生冲突时，就利用探测函数继续向前寻找空位置
    for (int i = 0; EMPTY != (HT[pos].key()); i++) { 
        pos = (home + p(k, i)) % M;
        Assert(k != (HT[pos]).key(), "Duplichates not allowed"); // 发现有重复的键值对
    }
    KVpair<Key, E> temp(k, e);  // 跳出循环后到达一个空位置，将键值对插入
    HT[pos] = temp;
}

// 哈希表中键值对查找的实现
template <typename Key, typename E>
E hashdict<Key, E>::hashSearch(const Key& k) const {
    int home;
    int pos = home = h(k);

    // 在查找的过程中，发现位置上并非想要寻找的键值对，说明产生冲突，继续使用探测函数进行寻找
    // 在查找的过程中，发现位置上是 EMPTY 标记时，说明这个键并没有被插入
    for (int i = 1; (k != (HT[pos]).key()) && (EMPTY != (HT[pos]).key()); i++) { 
        pos = (home + p(k, i)) % M;
    }
    if (k == (HT[pos]).key())  // 找到了键k
        return (HT[pos]).value();
    else
        return NULL;  // 找不到键k
}

// 简单的测试，输入想要进行的插入&查询操作，然后依次进行插入&查询操作
int main() {
    hashdict<int, int> hashTable(20, 0);
    int key, val, insert, find;
    cin >> insert >> find;
    for (int i = 0; i < insert; i++) {
        cin >> key >> val;
        hashTable.insert(key, val);
    }
    for (int i = 0; i < find; i++) {
        cin >> key;
        val = hashTable.find(key);
        cout << val << endl;
    }

    return 0;
}
#include <cstring>
#include <iostream>
using namespace std;

// 产生错误，用于终止程序，打印错误信息
void Assert(bool mustTrue, char* str) {
    if (!mustTrue) {
        cout << str << endl;
        abort();
    }
}

// 哈希表中的键值对结构
template <typename Key, typename E>
class KVpair {
   private:
    Key KEY;    // 存储键
    E VALUE;    // 存储值
    Key EMPTY;  // 自定义零值

   public:
    KVpair<Key, E>* next;  // 发生冲突时用于申请额外的空间

    KVpair() { next = nullptr; }

    KVpair(Key k, E e) {
        KEY = k;
        VALUE = e;
        next = nullptr;
    }

    void setKey(Key k) { KEY = k; }  // 设置键

    Key key() { return KEY; }  // 返回键

    E value() { return VALUE; }  // 返回值
};

// 哈希表本表
template <typename Key, typename E>
class hashdict {
   private:
    KVpair<Key, E>* HT;  // 存放哈希表内容
    int M;               // 最大容量
    Key EMPTY;           // 自定义零值
    int currcnt;         // 当前哈希表存放元素数目

    int h(int x) const { return x % M; }  // int 类型哈希函数，直接取模
    int h(char* x) {  // char* 类型哈希函数，求和取模
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
        // Assert(currcnt < M, "Hash is full");  
        // 哈希表已满x [开哈希可以一直申请新空间，就没有满了这个概念]

        hashInsert(k, it);
        currcnt++;
    }
};

// 哈希表中键值对插入的实现
template <typename Key, typename E>
void hashdict<Key, E>::hashInsert(const Key& k, const E& e) {
    int pos = h(k);

    KVpair<Key, E>* tempKV = new KVpair<Key, E>(k, e);
    KVpair<Key, E>* tmp = &HT[pos];

    if ((HT[pos]).key() == EMPTY) {
        HT[pos] = *tempKV;
    } else {
        while (tmp->next) { // 一直走到链表的末尾位置
            Assert(k != tmp->key(), "Duplichates not allowed"); // 发现有重复的键值对
            tmp = tmp->next;
        }
        tmp->next = tempKV; // 将新键值对插入在链表末尾
    }
}

// 哈希表中键值对查找的实现
template <typename Key, typename E>
E hashdict<Key, E>::hashSearch(const Key& k) const {
    int pos = h(k);

    KVpair<Key, E>* tmp = &HT[pos];
    while (tmp && tmp->key() != EMPTY) {
        if (k == tmp->key())  // 找到了键k
            return tmp->value();

        tmp = tmp->next; // 继续查找链表的下一节
    }

    return NULL;  // 当找遍对应的链表还没找到，说明键k不存在
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
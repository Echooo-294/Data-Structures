#include<bits/stdc++.h>

using namespace std;

//用来返回各个类型的EMPTYKEY
class EMPTY{            
public:
    operator int(){return -1;}
    operator unsigned(){return -1;}
    operator long long(){return -1;}
    operator string(){string ret="";return ret;}
    operator double(){return NAN;}
}EMPTYKEY;



//二三树结点类
template <typename Key, typename E>
class TTNode{           
public:
    E lval, rval;       //左右数的值
    Key lkey, rkey;     //左右数的索引(key)
    TTNode *left, *center, *right; //左中右三个pointer指向下一个TTNode
    
    // 构造一个空的TTNode
    TTNode(){  
        center = left = right = NULL;
        lkey = rkey = Key(EMPTYKEY);
    }
    
    // 构造一个TTNode,传递这个TTNode需要的所有成员值
    TTNode(Key lk, E lv, Key rk, E rv, TTNode<Key,E>* p1, TTNode<Key,E>* p2, TTNode<Key,E>* p3){
        lkey = lk, rkey = rk, lval = lv, rval = rv;
        left = p1, center = p2, right = p3;
    }
    ~TTNode(){}
    
    //判断该点是否为叶结点
    bool isleaf() {return left==NULL;}
    
    // 在原先TTNode中加入一个TTNode(这个TTNode只有一个值), 进行<合并>或者<分裂>
    TTNode<Key,E> * add(TTNode<Key, E>* it){
        if(rkey == Key(EMPTYKEY)){      //这个时候原先的TTNode只有一个值,所以直接进行<合并>
            if(lkey < it->lkey){ // 说明:如果子树中进行插入过了,这个插入就是中子树中进行的
                rkey = it->lkey, rval = it->lval;
                right = it->center, center = it->left; // 书上这里应该又写错了
            }
            else {
                rkey = lkey, rval = lval, right = center;
                lkey = it->lkey, lval = it->lval;
                center = it->center, left = it->left; // 书上这里写it->center应该又写错了 
            }
            return this;
        }
        else if(it->lkey <= lkey){          // 从左边插入来的结点
            center = new TTNode<Key,E>(rkey, rval, Key(EMPTYKEY), NULL, center, right, NULL);
            rkey = Key(EMPTYKEY), rval = NULL, right = NULL;
            left = it; // 书上这里好像又错了(也说不上错,就是写多了没必要的)
            return this;
        }
        else if(it->lkey < rkey){
            it->center = new TTNode<Key,E>(rkey, rval, Key(EMPTYKEY), NULL, it->center, right, NULL);
            center = it->left, it->left = this;
            rkey = Key(EMPTYKEY), rval = NULL, right = NULL;
            return it;
        }
        else {
            TTNode<Key,E>* n1 = new TTNode<Key,E>(rkey, rval, Key(EMPTYKEY), NULL, this, it, NULL);
            rkey = Key(EMPTYKEY), rval = NULL;
            return n1;
        }
    }
};


//二三树类
template <typename Key, typename E>
class TTTree{
public:
    TTNode<Key, E> * ROOT;

    TTTree():ROOT(NULL){}
    ~TTTree(){}
    //查找元素的辅助函数
    E findhelp(TTNode<Key, E> * root, Key k) const{
        if(root == NULL) return NULL;
        if(k == root->lkey) return root->lval;
        if(k == root->rkey) return root->rval;

        if(k < root->lkey) return findhelp(root->left, k);
        else if(root->rkey == Key(EMPTYKEY)) return findhelp(root->center, k);  // 其实我个人感觉用EMPTYKEY判断倒不如用right指针是否为NULL来判断
        else if(k < root->rkey) return findhelp(root->center, k);
        else  return findhelp(root->right, k);
    }
    //通过键值k查找元素,返回元素的值
    E find(Key k) const{
        return findhelp(ROOT, k);
    }

    //插入一个新的二三结点的辅助函数
    TTNode<Key, E> * inserthelp(TTNode<Key, E> *rt, const Key k, const E e){
        TTNode<Key, E> * ret;//辅助的TTNode指针用来返回.
        if(rt == NULL) 
            return new TTNode<Key ,E>(k, e, Key(EMPTYKEY), NULL, NULL, NULL, NULL); //如果插入过程中根为NULL(意味着这是一棵崭新的tttree),就新建一个根.
        
        if(rt->isleaf())
            return rt->add(new TTNode<Key,E>(k, e, Key(EMPTYKEY), NULL, NULL, NULL, NULL));

        // 插入左边
        if(k < rt->lkey){
            ret = inserthelp(rt->left, k, e);
            if(ret->rkey != Key(EMPTYKEY)) return rt;  \
            // 书上的这里应该是想判断是否需要在rt结点这里进行插入操作.
            // 但是书上与之配套的add()函数并不会在<分裂>后总是返回非原结点,
            // 也就是说要么修改add()函数要么修改这里的判断逻辑,我就在这里进行修改了.大家可以对照书上(第三版P365)代码看一下.
            else return rt->add(ret);
        }
        // 插入中间
        else if((rt->rkey == Key(EMPTYKEY)) || (k < rt->rkey)){
            ret = inserthelp(rt->center, k, e);
            if(ret->rkey != Key(EMPTYKEY)) return rt; //同line94,上一个类似if的逻辑一致
            else return rt->add(ret);
        }
        // 插入右边
        else {
            ret = inserthelp(rt->center, k, e);
            if(ret->rkey != Key(EMPTYKEY)) return rt; 
            else return rt->add(ret);
        }
    }
    TTNode<Key, E> * insert(Key k, E e){
        return ROOT = inserthelp(ROOT, k, e);
    }

    // 对某个结点的值进行修改,返回修改是否成功信息
    bool modifyhp(TTNode<Key, E> *rt, Key k, E e){
        if(rt == NULL) return false;
        if(k == rt->lkey){
            rt->lval = e;
            return true;
        }
        if(k == rt->rkey){
            rt->rval = e;
            return true;
        }

        if(k < rt->lkey) return modifyhp(rt->left, k, e);
        else if(rt->rkey == Key(EMPTYKEY)) return modifyhp(rt->center, k, e);
        else if(k < rt->rkey) return modifyhp(rt->center, k, e);
        else return modifyhp(rt->right, k, e);
    }
    bool modify(Key k, E e){
        return modifyhp(ROOT, k, e);
    }

    // 打印这个tttree来检验
    void pthp(TTNode<Key, E> * rt){
        cout<<"lkey:"<<rt->lkey<<" "<<"lval:"<<rt->lval<<" "<<"rkey:"<<rt->rkey<<" "<<"rval:"<<rt->rval<<"\n";
        if(rt->left) pthp(rt->left);
        if(rt->center) pthp(rt->center);
        if(rt->right) pthp(rt->right);
    }
    void pt(){
        pthp(ROOT);
    }
};


// 测试函数
// 输入op码:
// 1 的时候,输入 x y .向23树插入键值为x, 数值为y的元素
// 2 的时候,输入 x   .查询23树中键值为x的元素的数值
// 3 的时候,输入 x y .将23树中键值为x的元素的数值修改为y
void test(){
    TTTree<string, int> mp;
    string str;
    int x, op;
    while(cin>>op){
        if(op==1){
            cin>>str>>x;
            mp.insert(str, x);
        }
        else if(op==2){
            cin>>str;
            x = mp.find(str);
            cout<<x<<"\n";
        }
        else {
            cin>>str>>x;
            if(mp.modify(str, x))
                cout<<"successfully modified\n";
            else 
                cout<<"the Key is undifined\n";

        }
    }
    
}
/* 
test_data_in:
1 abc 129
3 ad 123
1 lh 111
2 abc
1 kxx -1345
2 ad
2 lg
2 lh
3 lh -34234
2 lh

 */
/* 
test_data_out:
the Key is undifined
129
0
0
111
successfully modified
-34234
 */
/* 
数据说明:
第一行没找到ad,所以输出"the Key is undifined"
第二行找到abc,值为129
第三行没找到ad,输出默认值(NULL)0,(后面有需要可以修改代码的val赋值NULL部分,将NULL改成需要的)
第四行同第三行
第五行找到lh,输出111
第六行找到lh,修改成功
第七行找到lh,输出其值-34234
 */

signed main(){
    
    test();
    return 0; 
}
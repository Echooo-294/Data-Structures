#pragma once

#ifdef TMDBG
#include <iostream>
#define LOG(...) fprintf(stderr, "%s: Line %d:\t", __FILE__, __LINE__); \
PRINT(__VA_ARGS__);
template <typename... X>
void PRINT(X... args){
    ((std::cerr << args),...);
}
#else
#define LOG(...)
#define PRINT(...)
#endif

// The number of records_ (and keys_) in a leaf node
const int LEAF_MAXN = 3;
// The number of get_node_ptr (and keys_) in an internal node
const int INTER_MAXN = 3;

const int LEAF_MID_POS = (LEAF_MAXN  + 1) / 2;
const int INTER_MID_POS = (INTER_MAXN) / 2;

const int LEAF_MINN = (LEAF_MAXN  + 1) / 2;
const int INTER_MINN = (INTER_MAXN  + 1) / 2;

// Abstract class definition for b_plus_trees
template <typename key_t, typename record_t>
class bp_node {
   public:
    bp_node* l_ptr;
    bp_node* r_ptr;                    // Links to siblings
    // virtual ~bp_node() {}              // Base destructor
    virtual bool is_leaf() const = 0;  // True if node is a leaf
    virtual bool is_full() const = 0;  // True if node is full
    virtual int size() const = 0;      // Current num of records_
    virtual int max_size() const =0;
    virtual int min_size() const =0;
    // virtual bp_node* remove(int pos) =0;
    virtual key_t* keys() = 0;  // Return array of keys
};

#ifdef TMDBG
#include <map>
#include <string>
const char* NICK_NAMES[]{
    "Acorn",   "Beetles", "Crab",    "Daisy",  "Elk",    "Fern",
    "Gerbil",  "Hazel",   "Iguana",  "Jester", "Koi",    "Ladybug",
    "Maracas", "Ninja",   "Octopus", "Plum",   "Quartz", "Reptile",
    "Saturn",  "Turtle",  "Unicorn", "Venus",  "Wasp",   "Xylophone",
    "Yalk",    "Zeppelin"};
std::map<bp_node<int,char*>*,const char*> map_nick;
auto get_nick = [i = 0] (bp_node<int,char*>* addr) mutable {
    auto it = map_nick.find(addr);
    if(it!=map_nick.end()){
        return it->second;
    }else{
        const char* name = NICK_NAMES[i];
        i=(i+1)%26;
        map_nick.insert(std::pair(addr,name));
        return name;
    }
};
template<typename T,int sz>
auto arr_to_str(T (&arr)[sz]){
    std::string ans;
    ans.append("{");
    for(int i = 0; i < sz ; i++){
        ans.append(std::to_string(arr[i]));
        if(i!=sz-1) ans.append(", ");
    }
    ans.append("}");
    return ans;
}
template<typename T>
auto arr_to_str(T* arr,int sz){
    std::string ans;
    ans.append("{");
    for(int i = 0; i < sz ; i++){
        ans.append(std::to_string(arr[i]));
        if(i!=sz-1) ans.append(", ");
    }
    ans.append("}");
    return ans;
}
template<int sz>
auto arr_to_str(bp_node<int,char*>* (&arr)[sz]){
    std::string ans;
    ans.append("{");
    for(int i = 0; i < sz ; i++){
        ans.append(get_nick(arr[i]));
        if(i!=sz-1) ans.append(", ");
    }
    ans.append("}");
    return ans;
}
auto arr_to_str(char** arr,int sz){
    std::string ans;
    ans.append("{");
    for(int i = 0; i < sz ; i++){
        ans.append(arr[i]);
        if(i!=sz-1) ans.append(", ");
    }
    ans.append("}");
    return ans;
}
#endif
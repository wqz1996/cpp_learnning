#include<iostream>
#include<vector>
#include<string>
using namespace std;
class trie_node{
public:
    int cnt;
    trie_node* next[26];
    trie_node(){
        cnt=1;
        for(int i=0;i<26;i++){
            next[i]=nullptr;
        }
    }
};
int main(){
    trie_node* root=new trie_node();
    int n=0;
    cin>>n;
    vector<string> strs(n);
    for(int i=0;i<n;i++){
        string tmp;
        cin>>tmp;
        strs[i]=tmp;
        trie_node* p=root;
        for(int j=0;j<tmp.length();j++){
            if(p->next[tmp[j]-'a']!=nullptr){
                p->next[tmp[j]-'a']->cnt++;
            }
            else{
                p->next[tmp[j]-'a']=new trie_node();
            }
            p=p->next[tmp[j]-'a'];
        }
    }
    for(int i=0;i<n;i++){
        trie_node* p=root;
        int j=0;
        for(;j<strs[i].length();j++){
            if(p->next[strs[i][j]-'a']->cnt == 1){
                cout<<strs[i].substr(0,j+1)<<endl;
                break;
            }
            p=p->next[strs[i][j]-'a'];
        }
        if(j==strs[i].length()){
            cout<<strs[i]<<endl;
        }
    }
    return 0;
}
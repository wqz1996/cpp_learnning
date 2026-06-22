#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
#include<ctime>
#include< unordered_map>
#include< unordered_set>
#include<hash_map>
#include<hash_set>
#include<assert.h>
#include<set>
#include<map>
using namespace std;
/*************2两数相加*****************************/
// 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
//使用哈希表复制出全部的节点，并且将节点再链接起来
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> originToClone;
        Node* p = head;
        //第一次遍历将全部节点拷贝出来，并赋值
        while (p != nullptr) {
            originToClone[p] = new Node(p->val);
            p = p->next;
        }
        p = head;
        //第二次遍历将拷贝节点的next和random指针链接好
        while (p != nullptr) {
            originToClone[p]->next = originToClone[p->next];
            originToClone[p]->random = originToClone[p->random];
            p = p->next;
        }
        return originToClone[head];
    }
};

//拼接+拆分
//原节点 1->新节点 1 -> 原节点 2 -> 新节点 2 -> .....
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr)
            return nullptr;
        Node* cur = head;
        // 在原节点后面创建一个和原节点val相同的节点
        while (cur != nullptr) {
            Node* tmp = new Node(cur->val);
            tmp->next = cur->next;
            cur->next = tmp;
            cur = tmp->next;
        }
        cur = head;
        // cur指向的时原节点，cur->next是复制的节点，复制节点的random指向，cur->random->next，也就是原节点复制出来的
        while (cur != nullptr) {
            if (cur->random != nullptr)
                cur->next->random = cur->random->next;
            cur = cur->next->next;
        }

        // 拆分两个链表
        cur = head->next;
        Node *pre = head, *res = head->next;
        while (cur->next != nullptr) {
            pre->next = pre->next->next;
            cur->next = cur->next->next;
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = nullptr;
        return res;
    }
};
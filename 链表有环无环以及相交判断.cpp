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
using namespace std;
/******************判断链表是否是回文结构，例1->2->2->1*******************************************/
struct Node {
	int data;
	Node* next;
	Node(int x):data(x),next(NULL){}
};
Node* creatlist(int val) {//新建一个值为val的节点
	Node* node = new Node(val);
	node->next = NULL;
	return node;
}
int getElem(Node* node, int i) {
	int j = 1;
	Node* head;
	head = node->next;//指向链表第一个节点
	while (head != NULL && j < i) {//从第一个节点到第i个节点遍历
		head = head->next;
		j++;
	}
	if (!head || j > i) {//没找到第i个节点
		return NULL;
	}
	return head->data;
}
void tail_insert(Node* node, Node* insert) {
	Node* head=node;
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = insert;
}
void top_insert(Node* node, Node* insert) {
	Node* head = node;
	insert->next = head->next;
	head->next = insert;
}
void list_insert(Node* node, int i, int insert) {
	Node* head = node->next;
	Node* insert_node;
	insert_node = (Node*)malloc(sizeof(Node));
	int j = 1;
	while (head != NULL && j < i) {
		head = head->next;
		j++;
	}
	insert_node->data = insert;
	insert_node->next = head->next;
	head->next = insert_node;

}
void Printlist(Node* head) {//打印链表
	Node* node = head;
	if (node == NULL) {
		cout << "NULL" << endl;
		return;
	}
	while (node->next != NULL) {
		cout << node->data << "->";
		node = node->next;
	}
	cout << node->val << "->" << "NULL" << endl;

}
int DeleteNode(Node* node, int data) {
	Node* head = node;
	Node* temp;
	while (head->next != NULL) {
		temp = head;
		head = head->next;
		if (head->data == data) {
			if (head->next == NULL) {
				temp->next = NULL;
				free(head);
			}
			else {
				temp->next = head->next;
				free(head);
			}
			return 0;
		}
	}
	cout << "there is no such a node" << endl;
	return -1;
}
void delete_i_node(Node* node, int i) {
	Node* head = node;
	int j = 1;
	Node* temp;
	while (head->next != NULL && j < i) {
		head = head->next;
		j++;
	}
	temp = head->next;
	head->next = temp->next;
	free(temp);

}
void reverse_list(Node* node) {
	Node* head = node->next;
	Node* pback;
	if (head == NULL || head->next == NULL) {
		return;
	}
	while (head->next != NULL) {
		pback = head->next;
		if (head == node->next)
			head->next = NULL;
		else {
			head->next = node->next;
		}
		node->next = head;
		head = pback;
	}
	top_insert(node,head);
}
Node* reverse_node(Node* node) {//链表逆序
	Node* pre = NULL;
	Node* cur = head;
	while (cur != NULL) {
		ListNode* next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
	
}
/*****************荷兰国旗链表******************/
//Node* islandlist(Node* node) {
//	Node* less;
//	Node* equal;
//	Node* more;
//
//}
/*********************判断链表是否有环*****************************/
Node* hasloop(Node* node) {
	Node* cur=node->next;
	unordered_set<Node*> hash;
	unordered_set<Node*>::iterator t;
	while (cur != NULL) {
		if (hash.find(cur) == hash.end()) {
			hash.insert(cur);
			cur = cur->next;
		}
		else {
			return cur;
		}
		
		
	}
	return NULL;

}
/***************************快慢指针判断链表是否有环***************************************/
Node* getLoopNode(Node* head) {
	if (head == NULL || head->next == NULL || head->next->next == NULL) {
		return NULL;
	}
	Node* n1 = head->next;//慢指针
	Node* n2 = head->next->next;//快指针
	while (n1 != n2) {
		if (n2->next == NULL || n2->next->next == NULL)//快指针指向空则无环
			return NULL;
		n1 = n1->next;
		n2 = n2->next->next;
	}
	n2 = head;//快指针回到头节点
	while (n1 != n2) {//调整快指针为一次走一步,n1与n2相遇的节点即第一个入环节点
		n1 = n1->next;
		n2 = n2->next;
	}
	return n1;
}
/*********************判断两个链表(有环或无环)是否相交*********************/
Node* noloop(Node* head1, Node* head2) {//无环链表的相交问题
	if (head1 == NULL || head2 == NULL) {
		return NULL;
	}
	Node* cur1 = head1;
	Node* cur2 = head2;
	int n = 0;//两个链表的长度差值
	while (cur1->next != NULL) {
		cur1 = cur1->next;
		n++;
	}
	while (cur2->next!=NULL)
	{
		cur2 = cur2->next;
		n--;
	}
	if (cur1 != cur2)//若尾节点一致则一定不相交
		return NULL;
	cur1 = n > 0 ? head1 : head2;//将长度长的链表头节点给cur1
	cur2 = cur1 == head1 ? head2 : head1;//将另一个链表的头节点给cur2
	n = abs(n);
	while (n != 0) {//先让cur1运动两个链表的长度差值
		cur1 = cur1->next;
		n--;
	}
	while (cur1 != cur2) {//共同运动到相遇的节点即为相交节点
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;

}
Node* bothloop(Node* head1, Node* head2) {//两个有环链表的相交问题
	if (head1->next == NULL || head2 == NULL) {
		return NULL;
	}
	Node* loop1 = getLoopNode(head1);
	Node* loop2 = getLoopNode(head2);
	if (loop1 == loop2) {//复用单链表相交问题
		Node* cur1 = head1;
		Node* cur2 = head2;
		int n = 0;
		while (cur1 != loop1) {
			cur1 = cur1->next;
			n++;
		}
		while (cur2 != loop1) {
			cur2 = cur2->next;
			n--;
		}
		cur1 = n > 0 ? head1 : head2;
		cur2 = cur1 == head1 ? head2 : head1;
		n = abs(n);
		while (n != 0) {
			cur1 = cur1->next;
			n--;
		}
		while (cur1 != cur2) {
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;

	}
	else {
		Node* cur1 = loop1->next;
		while (cur1 != loop1) {
			if (cur1 == loop2) {//从loop1继续向下遍历，如果遇到loop2则相交，否则不想交
				return loop1;
			}
			cur1 = cur1->next;
		}
		return NULL;
	}
	

}
Node* getintersectNode(Node* head1, Node* head2) {//判断链表是否相交，返回相交节点
	if (head1 == NULL || head2 == NULL) {
		return NULL;
	}
	Node* loop1 = getLoopNode(head1);
	Node* loop2 = getLoopNode(head2);
	if (loop1 == NULL && loop2 == NULL) {
		return noloop(head1, head2);//无环链表相交问题
	}
	if (loop1 != NULL && loop2 != NULL) {
		return bothloop(head1, head2);//两个有环链表相交问题
	}
	return NULL;//有环链表与无环链表不能相交
}
int main()
{	
	//Node* head=creat_node(0);
	//for (int i = 1; i < 10; i++) {
	//	tail_insert(head, creat_node(i));
	//}
	//Printlist(head);
	///*reverse_list(head);*/
	//Node* h=reverse_node(head);
	//Printlist(h);
	unordered_map<string, int> hash;
	hash_map<string, int> map;
	unordered_map<string, int>::iterator t;
	hash.insert({ "zuo", 31 });
	hash.insert({ "yao", 2 });
	hash.insert({ "laozhang", 46 });
	t=hash.find("yao");
	cout << hash["yao"] << endl;
	if (t != hash.end())
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;

}


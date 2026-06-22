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
/******************二叉树先序、中序、后续遍历*******************************************/
struct tree {
	int data;
	struct tree* left;
	struct tree* right;

};
struct P_tree {//带parent指针的树,根节点parent->NULL
	int data;
	struct P_tree* left;
	struct P_tree* right;
	struct P_tree* parent;
};
tree* creatTree()
{
	string data;
	tree* T;
	cin >> data;
	//结点不存在
	if (data == "#")
	{
		T = NULL;
	}
	else
	{
		T = (tree*)malloc(sizeof(tree));//新建tree节点
		T->data = stoi(data);//将string转为int
		T->left = creatTree();
		T->right = creatTree();
	}
	return T;
}
/**************递归版先序遍历******************///中左右
void preOrderResur(tree* head) {//先打印当前节点，再打印左子树，再打印右子树
	if (head == NULL) {
		return;
	}
	cout << head->data << " ";
	preOrderResur(head->left);
	preOrderResur(head->right);
}
/**************递归版中序遍历******************///左中右
void inOrderResur(tree* head) {//先打印左子树，再打印当前节点，再打印右子树
	if (head == NULL) {
		return;
	}

	inOrderResur(head->left);
	cout << head->data << " ";
	inOrderResur(head->right);
}
/******************递归版后序遍历*******************************///左右中
void behindOrderResur(tree* head) {//先打印左子树，再打印右子树，再打印当前节点
	if (head == NULL) {
		return;
	}

	behindOrderResur(head->left);
	behindOrderResur(head->right);
	cout << head->data << " ";
}
/**************非递归版先序遍历******************/
void preOrderUnResur(tree* head) {
	if (head != NULL) {
		stack<tree*> s;
		s.push(head);
		while (!s.empty()) {
			head = s.top();//弹出栈顶元素
			s.pop();
			cout << head->data << " ";
			if (head->right != NULL)//先压右子树
				s.push(head->right);
			if (head->left != NULL)//后压左子树
				s.push(head->left);
		}
	}

}
/*************非递归版中序遍历*************************/
void inOrderUnResur(tree* head) {
	if (head != NULL) {
		stack<tree*> s;
		while (!s.empty() || head != NULL) {
			if (head != NULL) {//将左边界全部压栈
				s.push(head);
				head = head->left;
			}
			else {//当前节点为NULL，打印并弹出栈顶，当前节点向右
				head = s.top();//拿出栈顶作为当前节点
				s.pop();
				cout << head->data << " ";//打印栈顶元素
				head = head->right;//打印的那个节点的右孩子
			}

		}
	}

}
/*****************非递归版后序遍历************************/
void behindOrderUnResur(tree* head) {
	if (head != NULL) {
		stack<tree*> s1;
		stack<tree*> help;
		s1.push(head);
		while (!s1.empty()) {
			head = s1.top();
			s1.pop();
			help.push(head);//辅助栈，将中右左顺序压入栈，弹出得到左右中

			if (head->left != NULL) {//有左子树先压左
				s1.push(head->left);
			}
			if (head->right != NULL) {//有右子树后压右
				s1.push(head->right);
			}
		}
		while (!help.empty()) {//逆序打印
			cout << help.top()->data << " ";
			help.pop();
		}
	}
}
/******************找当前节点的后继节点（后继节点：中序遍历中的下一个节点）***************************/
P_tree* getMostleft(P_tree* node) {//找到最左节点
	if (node == NULL)
		return node;
	while (node->left != NULL) {//有左子树则一直向左
		node = node->left;
	}
	return node;
}
P_tree* getSuccessorNode(P_tree* node) {
	if (node == NULL)
		return node;
	if (node->right != NULL) {//如果有右子树,找到右子树最左的节点
		return getMostleft(node->right);
	}
	else {//如果没有右子树
		P_tree* parent = node->parent;
		while (parent != NULL && parent->left != node) {//当前节点不是父节点的左孩子,parent != NULL用来判断整个树最右的节点，该节点没有后继
			node = parent;//当前节点走到父节点位置
			parent = node->parent;//得到父节点的父节点
		}
		return parent;//当前节点时parent的左孩子，则parent为初始节点的后继节点
	}


}
/***************二叉树序列化以及反序列化*********************************/
/***********先序序列化************/
string serialByPre(tree* head) {

	if (head == NULL)
		return "#_";//记录NULL
	string res = to_string(head->data) + "_";
	res += serialByPre(head->left);//记录左树
	res += serialByPre(head->right);//记录右树
	return res;

}
/***************反序列化******************/
tree* reconPreOrder(char*& str) {//char*& 影响函数外指针的值，相当于操作外部指针
	if (*str == '#') {
		str++;//跳过'#'
		str++;//跳过'_'
		return NULL;
	}
	int value = 0;
	while (*str != '_') {//遇到'_'之前的字符，将char转换为int值
		value = 10 * value + (int)((*str) - '0');
		str++;
	}
	str++;//跳过'_'
	tree* head = new tree;
	head->data = value;
	head->left = reconPreOrder(str);
	head->right = reconPreOrder(str);
	return head;

}
tree* reconBypreString(char* str) {//反序列化主函数
	if (str == NULL || *str == '#')
		return NULL;
	return reconPreOrder(str);
}
/************************************************************************************/
/*******************平衡二叉树*************************/
class ReturnData {
public:
	bool isB;
	int h;
	ReturnData(bool isB, int h) {
		this->isB = isB;
		this->h = h;
	}
};

ReturnData isbanlance(tree* head) {
	if (head == NULL)
		return ReturnData(false, 0);
	ReturnData leftdata = isbanlance(head->left);//得到左子树高度
	ReturnData rightdata = isbanlance(head->right);//得到右子树高度
	if (leftdata.isB == false)
		return ReturnData(false, 0);
	if (rightdata.isB == false)
		return ReturnData(false, 0);
	if (abs(leftdata.h - rightdata.h) > 1)
		return ReturnData(false, 0);
	return ReturnData(true, max(leftdata.h, rightdata.h) + 1);
}
bool isB(tree* head) {
	return isbanlance(head).isB;
}
/************************判断是完全二叉树**********************************************/
bool isCBT(tree* head) {
	if (head == NULL)
		return true;
	queue<tree*> q;
	bool leaf = false;
	tree* L = NULL;
	tree* R = NULL;
	q.push(head);
	while (!q.empty()) {
		head = q.front();
		q.pop();
		L = head->left;
		R = head->right;
		if ((leaf && (L != NULL || R != NULL))//到了叶节点检测阶段，但是有左孩子或者右孩子则不是叶节点，因此不是完全二叉树
			|| (L == NULL && R != NULL)) {//左孩子为空，右孩子不为空则一定不是完全二叉树
			return false;
		}
		if (L != NULL) {//宽度遍历（按层遍历）
			q.push(L);
		}
		if (R != NULL) {
			q.push(R);
		}
		else {//当遇到左右孩子不全的节点，开始检查是否为叶节点
			leaf = true;
		}

	}
	return true;
}
/**************************已知完全二叉树，求节点个数，时间复杂度低于O(N)****************************************/
//满二叉树，高度h，则节点个数为(2^h)-1
int mostleftlevel(tree* head, int level) {//求当前节点最左边界是多少层
	while (head != NULL) {
		head = head->left;
		level++;
	}
	return level - 1;
}
int nodeNumOfTree(tree* head, int level, int h) {//level当前层数，h为全局变量树的深度
	if (level == h)
		return 1;
	if (mostleftlevel(head->right, level + 1) == h) {
		return ((1 << (h - level)) + nodeNumOfTree(head->right, level + 1, h));//1<<(h-level)->2^(h-level)
	}
	else {
		return ((1 << (h - level - 1)) + nodeNumOfTree(head->left, level + 1, h));
	}
}
int nodeNUM(tree* head) {
	if (head == NULL)
		return 0;
	return nodeNumOfTree(head, 1, mostleftlevel(head, 1));
}
/********************************************************************/
int main()
{
	string prestr{ "1_2_#_3_#_#_4_#_#_" };//"1_2_#_3_#_#_4_#_#_"
	string s{ "1_2_4_#_#_5_#_#_3_#_#_" };
	tree* head;
	char* s_char = (char*)prestr.c_str();//string to char*

	//head = creatTree();
	//preOrderResur(head);
	//cout << endl;

	//s = serialByPre(head);
	//cout << s;
	//cout << endl;

	char* s_char_ = (char*)s.c_str();
	head = reconBypreString(s_char_);
	preOrderResur(head);
	cout << endl;
	cout << nodeNUM(head) << endl;
	return 0;

}


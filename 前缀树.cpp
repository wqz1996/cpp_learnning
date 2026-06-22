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
/***************前缀树*****************/
class Trie {
private:
	// 最多R个指向子节点的链接，其中每个链接对应字母表数据集中的一个字母，这里取26个英文字母，R=26。
	Trie* next[26];
	// 指定节点是对应键的结尾还是只是键前缀
	bool isWord;
public:
	/** Initialize your data structure here. */
	// 构造函数
	Trie() {
		isWord = false;
		for (int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
	}

	/** Inserts a word into the trie. */
	// 插入键 时间复杂度O(m)，m为键长。空间复杂度O(m)，最坏的情况下新插入的键没有公共前缀。
	// 通过搜索Trie树来插入键。从根开始搜索它对应于第一个键字符的链接。
	void insert(string word) {
		// 用于指向每一层节点，进行搜索的操作。
		Trie* t = this;
		// 遍历插入键的每一个字符
		for (char c : word) {
			// 如果链接不存在，创建一个新节点，并将它与父节点的链接相连，该链接与当前的键字符相匹配
			if (!t->next[c - 'a']) {
				t->next[c - 'a'] = new Trie();
			}
			// 链接存在，沿着链接移动到树的下一个子层。算法继续搜索下一个键字符
			t = t->next[c - 'a'];
		}
		// 直到到达键的最后一个字符，然后将当前节点标记为结束节点。此时的当前节点已经移动到键的最后字符所在的节点
		t->isWord = true;
	}

	/** Returns if the word is in the trie. */
	// 查找键 时间复杂度O(m)，最坏的情况下m为键长。空间复杂度O(1)
	bool search(string word) {
		// 用于指向每一层节点，进行搜索的操作。
		Trie* t = this;
		// 遍历查找键的每一个字符
		for (char c : word) {
			// 如果链接不存在，查找失败
			if (!t->next[c - 'a']) {
				return false;
			}
			// 链接存在，沿着链接移动到树的下一个子层。算法接续查找下一个键字符。
			t = t->next[c - 'a'];
		}
		// 直到到达最后一个字符，返回该键字符节点的isWord，如果为false，待查键是Trie树中另一个键的前缀。
		return t->isWord;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	// 查找Trie树中的键前缀
	bool startsWith(string prefix) {
		// 用于指向每一层节点，进行搜索的操作。
		Trie* t = this;
		// 遍历查找前缀的每一个字符
		for (char c : prefix) {
			// 如果链接不存在，查找失败
			if (!t->next[c - 'a']) {
				return false;
			}
			// 链接存在，沿着链接移动到树的下一个子层。算法接续查找下一个键字符。
			t = t->next[c - 'a'];
		}
		// 直到到达最后一个字符，由于是查找前缀，而不是整个键，所以返回true
		return true;
	}
};

int main()
{
	
	return 0;

}


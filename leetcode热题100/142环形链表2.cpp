#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		if (head == NULL || head->next == NULL || head->next->next == NULL)
			return NULL;
		ListNode* slow = head->next;
		ListNode* fast = head->next->next;
		while (slow!=fast) {
			if (fast->next == NULL || fast->next->next == NULL)
				return NULL;
			slow = slow->next;
			fast = fast->next->next;
		}
		fast = head;
		while (slow != fast) {
			slow = slow->next;
			fast = fast->next;
		}
		return fast;
	}
};
// 链表快慢指针模板
//

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow)
                break;
        }
        if (fast == nullptr || fast->next == nullptr)
            return nullptr;
        fast = head;
        while (fast != slow) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};
int main()
{


	return 0;
}


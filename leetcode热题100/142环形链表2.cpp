#include <cstddef> // NULL：第 7 行首次使用
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


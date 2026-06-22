 class Solution {
 public:
	 ListNode* removeNthFromEnd(ListNode* head, int n) {
		 assert(n >= 0);
		 ListNode* dummyNode = new ListNode(0);
		 dummyNode->next = head;
		 ListNode* p= dummyNode;
		 ListNode* q= dummyNode;
		 for (int i = 0; i < n + 1; i++) {
			 assert(q);//q不为空
			 q = q->next;//将q指向n+1位置
		 }
		 while (q != NULL) {//同时移动p和q，使得q指向NULL，则p指向待删除的前一个节点
			 p = p->next;
			 q = q->next;
		 }
		 ListNode* delNode = p->next;
		 p->next = delNode->next;
		 delete delNode;
		 ListNode* retNode = dummyNode->next;
		 delete dummyNode;
		 return retNode;
	 }
 };
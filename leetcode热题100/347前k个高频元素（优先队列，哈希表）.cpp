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
/************347前k个高频元素*******************/
//给定非空数组，返回出现频率前k高的元素
//注意k的合法性
class Solution {//O(Nlogk)
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		assert(k > 0);
		unordered_map<int, int> freq;//(元素，频率)
		for (int i = 0; i < nums.size(); i++)//统计每个元素出现频率
			freq[nums[i]]++;
		assert(k <= freq.size());
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;//pair(频率，元素) 最小堆
		for (unordered_map<int, int>::iterator it = freq.begin(); it != freq.end(); it++) {
			if (q.size() == k) {//队列中有k个元素，将遍历的下一个元素与队列中最小元素比较
				if (it->second > q.top().first) {
					q.pop();
					q.push(make_pair(it->second, it->first));
				}
			}
			else {
				q.push(make_pair(it->second, it->first));
			}
		}
		vector<int> res;
		while (!q.empty()) {
			res.push_back(q.top().second);
			q.pop();
		}
		return res;
	}
};
int main() {
	
	return 0;
} 
#include <queue> // priority_queue：第 19 行首次使用
#include <vector> // vector：第 13 行首次使用
#include <unordered_map> // unordered_map：第 15 行首次使用
#include <cassert> // assert：第 14 行首次使用
#include <utility> // pair, make_pair：第 19 行首次使用
#include <functional> // greater：第 19 行首次使用
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
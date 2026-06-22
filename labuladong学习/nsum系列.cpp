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
#include<assert.h>
#include<set>
#include<map>
using namespace std;
/*********nsum问题**********/
//twosum
class Solution {
public:
	/*******************返回索引*************************************/
	vector<int> twoSum(vector<int>& nums, int target) {//暴力法
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[i] + nums[j] == target)
					return vector<int>{i, j};
			}
		}
		throw(invalid_argument("There is no solution!"));
	}
	vector<int> twoSum1(vector<int>& nums, int target) {//哈希表存储
		unordered_map<int, int>  indexmap;
		int n = nums.size();
		for (int i = 0; i < n; i++) {//遍历数组
			int other = target - nums[i];//缓存target-nums[i]
			if (indexmap.find(other) != indexmap.end() && indexmap[other] != i)//找到数组中找到other并且索引不同
				return vector<int>{i, indexmap[other]};
			indexmap[nums[i]] = i;//记录数字和索引			
		}
		throw(invalid_argument("There is no solution!"));
	}
	/********************返回数字************************************/
		//不返回索引时，可以使用双指针，先排序后进行搜索
	vector<int> twoSum2(vector<int>& nums, int target) {//双指针
		sort(nums.begin(), nums.end());
		int p1 = 0;
		int p2 = nums.size() - 1;
		while (p1 < p2) {
			int sum = nums[p1] + nums[p2];
			if (sum > target)
				p2--;
			else if (sum < target)
				p1++;
			else
				return vector<int>{nums[p1], nums[p2]};
		}
		throw(invalid_argument("There is no solution!"));
	}
	//返回所有两数组成target的集合,不能重复
	vector<vector<int>> twoSum3(vector<int>& nums, int target) {//双指针
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());//先排序再用双指针
		int p1 = 0;
		int p2 = nums.size() - 1;
		while (p1 < p2) {
			int sum = nums[p1] + nums[p2];
			int  left = nums[p1], right = nums[p2];
			if (sum > target)
				while (p1 < p2 && nums[p2] == right)//同样跳过相同元素的遍历，提高效率
					p2--;
			else if (sum < target)
				while (p1 < p2 && nums[p1] == left)//同样跳过相同元素的遍历，提高效率
					p1++;
			else {
				res.push_back({ nums[p1],nums[p2] });//只有这个会出现重复情况
				//去掉重复元素的遍历
				while (p1 < p2 && nums[p1] == left)
					p1++;
				while (p1 < p2 && nums[p2] == right)
					p2--;
			}

		}
		return res;
	}
};
/*******************3sum*************************/
//可以复用2sum的程序
class Solution1 {
private:
	vector<vector<int>> twoSum(vector<int>& nums, int index, int target) {//双指针
		vector<vector<int>> res;
		//sort(nums.begin(), nums.end());//先排序再用双指针//已经排序过了不用再排序
		int p1 = index;//从index开始找
		int p2 = nums.size() - 1;
		while (p1 < p2) {
			int sum = nums[p1] + nums[p2];
			int  left = nums[p1], right = nums[p2];
			if (sum > target)
				while (p1 < p2 && nums[p2] == right)//同样跳过相同元素的遍历，提高效率
					p2--;
			else if (sum < target)
				while (p1 < p2 && nums[p1] == left)//同样跳过相同元素的遍历，提高效率
					p1++;
			else {
				res.push_back({ nums[p1],nums[p2] });//只有这个会出现重复情况
				//去掉重复元素的遍历
				while (p1 < p2 && nums[p1] == left)
					p1++;
				while (p1 < p2 && nums[p2] == right)
					p2--;
			}

		}
		return res;
	}
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		if (nums.size() < 3)
			return vector<vector<int>>{};
		return threeSumtarget(nums, 0);//和为0的三个数
	}
	vector<vector<int>> threeSumtarget(vector<int>& nums, int target) {
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());

		for (int i = 0; i < nums.size() - 2; i++) {//遍历到倒数第三个数即可
			if (nums[i] > target)//第一个数大于target则后面数加和一定大于target
				break;//如果target是负数则应该去掉
			int twotarget = target - nums[i];//求两数之和的target
			vector<vector<int>> twores = twoSum(nums, i + 1, twotarget);//从nums[i]下一个开始找两数之和
			for (vector<int> two : twores) {//将两数排序的结果每个后面都加上nums[i]
				two.push_back(nums[i]);
				res.push_back(two);
			}
			while (i < nums.size() - 1 && nums[i] == nums[i + 1])//跳过重复数字
				i++;
		}
		return res;
	}

};
/*******************4sum*************************/
class Solution2 {
private:
	vector<vector<int>> twoSum(vector<int>& nums, int index, int target) {//双指针
		vector<vector<int>> res;
		//sort(nums.begin(), nums.end());//先排序再用双指针//已经排序过了不用再排序
		int p1 = index;//从index开始找
		int p2 = nums.size() - 1;
		while (p1 < p2) {
			int sum = nums[p1] + nums[p2];
			int  left = nums[p1], right = nums[p2];
			if (sum > target)
				while (p1 < p2 && nums[p2] == right)//同样跳过相同元素的遍历，提高效率
					p2--;
			else if (sum < target)
				while (p1 < p2 && nums[p1] == left)//同样跳过相同元素的遍历，提高效率
					p1++;
			else {
				res.push_back({ nums[p1],nums[p2] });//只有这个会出现重复情况
				//去掉重复元素的遍历
				while (p1 < p2 && nums[p1] == left)
					p1++;
				while (p1 < p2 && nums[p2] == right)
					p2--;
			}

		}
		return res;
	}
	vector<vector<int>> threeSumtarget(vector<int>& nums, int index, int target) {
		vector<vector<int>> res;
		//sort(nums.begin(), nums.end());//foursum主函数已经排序
		for (int i = index; i < nums.size() - 2; i++) {//从index开始穷举,找到倒数第三个数即可
			int twotarget = target - nums[i];//求两数之和的target
			vector<vector<int>> twores = twoSum(nums, i + 1, twotarget);//从nums[i]下一个开始找两数之和
			for (vector<int> two : twores) {//将两数排序的结果每个后面都加上nums[i]
				two.push_back(nums[i]);
				res.push_back(two);
			}
			while (i < nums.size() - 1 && nums[i] == nums[i + 1])//跳过重复数字
				i++;
		}
		return res;
	}
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		int n = nums.size();
		if (n < 4)
			return vector<vector<int>> {};
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < n - 3; i++) {//找到倒数第四个数即可
			//if(nums[i]>target)//如果target为负数则去掉此句
			//break;
			int threetarget = target - nums[i];
			vector<vector<int>> threeres = threeSumtarget(nums, i + 1, threetarget);
			for (vector<int> three : threeres) {
				three.push_back(nums[i]);
				res.push_back(three);
			}
			while (i < n - 1 && nums[i] == nums[i + 1])
				i++;
		}
		return res;
	}
};
/*******************4nsum********使用递归结构*****************/
class Solution3 {
private:
	vector<vector<int>>  Nsumtarget(vector<int>& nums, int n, int start, int target) {
		int sz = nums.size();
		vector<vector<int>> res;
		if (n == 2) {//2sum问题
			int p1 = start;//从start开始双指针查找
			int p2 = sz - 1;
			while (p1 < p2) {
				int sum = nums[p1] + nums[p2];
				int left = nums[p1];
				int right = nums[p2];
				if (sum < target) {
					while (p1 < p2 && nums[p1] == left)
						p1++;
				}
				else if (sum > target) {
					while (p1 < p2 && nums[p2] == right)
						p2--;
				}
				else {
					res.push_back({ nums[p1],nums[p2] });
					while (p1 < p2 && nums[p1] == left)
						p1++;
					while (p1 < p2 && nums[p2] == right)
						p2--;
				}
			}
		}
		else {
			for (int i = start; i < sz; i++) {
				vector<vector<int>> Sub = Nsumtarget(nums, n - 1, i + 1, target - nums[i]);//(n-1)sum递归调用，将问题缩小为2sum计算后回溯
				for (vector<int> arr : Sub) {
					arr.push_back(nums[i]);
					res.push_back(arr);
				}
				while (i < sz - 1 && nums[i] == nums[i + 1])//去重
					i++;
			}
		}
		return res;
	}
public:
	vector<vector<int>> NSum(vector<int>& nums, int n, int target) {
		int sz = nums.size();
		if (sz < n)//若size<n则不可能有组合
			return vector<vector<int>>{};

		sort(nums.begin(), nums.end());//调用Nsum之前排序

		return Nsumtarget(nums, n, 0, target);
	}

};
/****************使用nsum结构测试4sum程序******************/
class Solution {
private:
	vector<vector<int>>  Nsumtarget(vector<int>& nums, int n, int start, int target) {
		int sz = nums.size();
		vector<vector<int>> res;
		if (n == 2) {
			int p1 = start;
			int p2 = sz - 1;
			while (p1 < p2) {
				int sum = nums[p1] + nums[p2];
				int left = nums[p1];
				int right = nums[p2];
				if (sum < target) {
					while (p1 < p2 && nums[p1] == left)
						p1++;
				}
				else if (sum > target) {
					while (p1 < p2 && nums[p2] == right)
						p2--;
				}
				else {
					res.push_back({ nums[p1],nums[p2] });
					while (p1 < p2 && nums[p1] == left)
						p1++;
					while (p1 < p2 && nums[p2] == right)
						p2--;
				}
			}
		}
		else {
			for (int i = start; i < sz; i++) {
				vector<vector<int>> Sub = Nsumtarget(nums, n - 1, i + 1, target - nums[i]);
				for (vector<int> arr : Sub) {
					arr.push_back(nums[i]);
					res.push_back(arr);
				}
				while (i < sz - 1 && nums[i] == nums[i + 1])
					i++;
			}
		}
		return res;
	}
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		int n = nums.size();
		if (n < 4)
			return vector<vector<int>> {};
		sort(nums.begin(), nums.end());//调用Nsum之前排序
		return Nsumtarget(nums, 4, 0, target);
	}
};
int main() {

	vector<int> arr = { 1,0,-1,0,-2,2 };

	return 0;
}
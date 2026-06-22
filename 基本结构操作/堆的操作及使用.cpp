#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>
#include<queue>
using namespace std;
void printvec(vector<int> nums)
{
	for (int i = 0; i < nums.size(); i++)
		cout << nums[i] << ' ';
	cout << endl;
}
bool less_cmp(const int& a, const int& b)//自定义比较方法，等同于less<int>()
{
	return a < b;
}
bool greater_cmp(const int& a, const int& b)
{
	return a > b;
}
int main() {
	int arr[] = { 3,2,4,1,5 };
	vector<int> nums(arr, arr + sizeof(arr)/sizeof(int));//创建vector容器 注：vector和deque都可以作为底层容器，但是list不允许
	make_heap(nums.begin(), nums.end(), greater<int>());//创建小顶堆
	printvec(nums);

	make_heap(nums.begin(), nums.end());//创建大顶堆或make_heap(nums.begin(), nums.end(), less<int>())
	printvec(nums);

	nums.push_back(6);//在vector数组中加入一个元素
	push_heap(nums.begin(), nums.end(), less<int>());//将插入元素后的堆重新排列为大顶堆
	printvec(nums);

	pop_heap(nums.begin(), nums.end(), less<int>());//弹出堆顶,弹出后并未删除该元素，是将顶部与底部交换，若想删除需要加nums.pop_back()操作
	printvec(nums);

	nums.pop_back();//弹出堆底
	printvec(nums);




}

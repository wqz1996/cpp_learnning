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
using namespace std;
/*******************桶排序*******************************************/
//给定一个数组，求排序后，相邻两个数的最大差值 时间O(N),且不基于比较排序
//1）一共N个数，准备N+1个桶
//2)遍历后找到max和min，若max=min则数组全部元素相等
//3)将min放在0号桶，将max放在最后的桶，将中间等分为N-1个桶，分别放入以后中间一定存在一个空桶(否定最大差值来自同一个桶)，保证最大差值是桶的最小值和下一个桶的最大值。
//4)统计每个桶的3个数据，（桶中最大最小值）min,max,（是否进入过值）bool
int bucket(long num, long len, long min_num, long max_num) {//确定数字num放入第几号桶
	return (int)((num - min_num) * len / (max_num - min_num));
}
int MaxGap(int arr[], int len) {
	int min_num = INT_MAX;//将数值设为系统最大
	int max_num = INT_MIN;//将数值设为系统最小
	for (int i = 0; i < len; i++) {
		min_num = min(arr[i], min_num);//寻找数组中最小值
		max_num = max(arr[i], max_num);//寻找数组中最大值

	}
	if (max_num == min_num)
		return 0;
	/*********************[hasnum, maxs, ,mins]为三个元素组成的一个桶,一共有N+1个************************************/
	bool* hasnum = new bool[len + 1]{false};//必须给初始false，否则初始为true
	int* maxs = new int[len + 1];
	int* mins = new int[len + 1];
	/****************************************************/
	int bid = 0;
	for (int i = 0; i < len; i++) {//重新遍历整个数组
		bid = bucket(arr[i], len, min_num, max_num);//确定当前数字对应桶的标号
		mins[bid] = hasnum[bid] ? min(mins[bid], arr[i]) : arr[i];//若桶里有值则保留待加入的值与原有值的最小值，若没有值则直接放入待加入值
		maxs[bid] = hasnum[bid] ? max(maxs[bid], arr[i]) : arr[i];//同上
		hasnum[bid]= true;//放入一个数后，改变标记
	}
	int res = 0;
	int lastmax = maxs[0];//前一个桶的最大值与下一个桶的最小值为相邻元素，且最大差值出现在不同的桶中
	for (int i = 1; i <= len; i++) {
		if (hasnum[i]) {//找下一个非空桶的min与前一个桶的最大值做差
			res = max(res,mins[i] - lastmax);//记录每次前一个桶的最大值与后一个桶的最小值的差值，保留最大的差值
			lastmax = maxs[i];//位置移动到下一个桶
		}
	}
	return res;

}
int main()
{
	int arr[5] = { 1,3,9,2,5 };
	int len = sizeof(arr) / sizeof(int);
	cout<<MaxGap(arr,len)<<endl;

	return 0;

	
}


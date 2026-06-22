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
// 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
// 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
class Solution {
public:
	// dp[i]表示s[0..i-1]是否能被拆分若干个在wordDict里面的单词
    // j为s[0..i-1]中的分割点，将s[0..i-1]分为s[0..j-1] 以及 s[j..i-1]
    // 记s1 = s[0..j-1] 记 s2 = s[j..i-1]，若s1和s2都可由wordDict中单词组成，则s1+s2也可以
    // 由dp的定义，dp[j] = s[0..j-1]，因此s1可以由dp[j]判断，s2需要进行check判断是否在wordDict中
    // 综上状态转移方程如下：
    // dp[i] = dp[j] && check(s[j..i-1])
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(),wordDict.end());
        int n = s.length();
        vector<bool> dp(n+1,false);
        dp[0] = true; // 默认空字符合法
		for(int i = 1; i<=n;i++){
            for(int j =0;j<i;j++){
                if(dp[j] && wordSet.count(s.substr(j,i-j))){
                    dp[i] = true;
                    break; // 提前退出，找到符合条件的即可，不必找出所有组合
                }
            }
        }
        return dp[n];
    }
};

#include <algorithm> // 使用处：第 18 行的 sort(
#include <string> // 使用处：第 11 行的 string
#include <vector> // 使用处：第 11 行的 vector
#include <unordered_map> // 使用处：第 12 行的 unordered_map
using namespace std;
//49. 字母异位词分组
//给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，
//但排列不同的字符串。
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		unordered_map<string, int> stringmap;//int为res的下标，代表应该放在res的第几行
		vector<vector<string>> res;
		string temp;
		int sub = 0;
		for (auto str : strs) {
			temp = str;
			sort(temp.begin(), temp.end());
			if (stringmap.find(temp) != stringmap.end()) {//找到了temp
				res[stringmap[temp]].push_back(str);//temp下标中压入str
			}
			else {
				vector<string> vec(1, str);//没找到temp则res新开启一行
				res.push_back(vec);
				stringmap[temp] = sub++;//记录temp对应的res的sub行
			}
				
		}
		return res;
	}
};
int main()
{
	vector<string> strs{ "eat", "tea", "tan", "ate", "nat", "bat" };
	Solution().groupAnagrams(strs);
	return 0;
}


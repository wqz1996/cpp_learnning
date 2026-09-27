#include <iostream> // cout, endl：第 25 行首次使用
#include <string> // string：第 9 行首次使用
#include <vector> // vector：第 21 行首次使用
#include <cassert> // assert：第 29 行首次使用
using namespace std;
/*************手机字母组合*****************/
class Solution {
private:
	const string letterMap[10] = {//数字对应的字母
		" ",//0
		"",//1
		"abc",//2
		"def",//3
		"ghi",//4
		"jkl",//5
		"mno",//6
		"pqrs",//7
		"tuv",//8
		"wxyz"//9
	};
	vector<string> res;
	void findComination(const string& digits, int index, const string& s) {//dights输入的数字字符，index,递归用，s当前的组合字符
		if (index == digits.size()) {
			res.push_back(s);
			cout << "get :" << s << ", return" << endl;//递归结束，回溯上一个
			return;
		}
		char c = digits[index];
		assert(c >= '0' && c <= '9' && c != '1');
		string letters = letterMap[c - '0'];//查找当前数字代表的字符串
		for (int i = 0; i < letters.size(); i++) {
			cout << "digits[" << index << "]=" << c << ", use " << letters[i] << endl;//递归过程
			findComination(digits, index + 1, s + letters[i]);
		}
		cout << "digits[" << index << "]=" << c << " complete,return" << endl;//循环结束
		return;

	}
public:
	vector<string> letterCombinations(string digits) {
		res.clear();
		if (digits == "")
			return res;
		findComination(digits, 0, "");
		return res;
	}

};
int main()
{
	vector<string> res = Solution().letterCombinations("23");
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << endl;
	return 0;
}


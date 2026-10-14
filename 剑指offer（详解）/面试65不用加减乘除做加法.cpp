using namespace std;
//面试题65. 不用加减乘除做加法
// 写一个函数，求两个整数之和，要求在函数体内不得使用 
//“+”、“-”、“*”、“/” 四则运算符号。
//使用二进制位运算进行加法求解，每一位用异或求解该位是0或1
//进位用与运算求解
class Solution {
public:
	int add(int a, int b) {
		int carry = 0;
		int sum = 0;//或者sum初始为a，return sum即可
		while (b != 0) {//直至无进位产生
			sum = a ^ b;//异或求无进位的和
			carry = (unsigned int)(a & b) << 1;//与运算后左移一位得进位的值
			a = sum;
			b = carry;
		}
		return a;//当b==0时，如果return sum则return 0
		
	}
};
int main()
{

	return 0;
}


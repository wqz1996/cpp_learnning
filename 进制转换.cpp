//10进制转化为2~36进制
string intToA(long long n, int radix)    //n是待转数字，radix是指定的进制
{
	string ans = "";
	do {
		long long t = n % radix;
		if (t >= 0 && t <= 9)    ans += t + '0';
		else ans += t - 10 + 'a';
		n /= radix;
	} while (n != 0);    //使用do{}while（）以防止输入为0的情况
	reverse(ans.begin(), ans.end());
	return ans;
}
//2~36进制转化为10进制
int Atoint(string s,int radix)    //s是给定的radix进制字符串
{
    int ans=0;
    for(int i=0;i<s.size();i++)
    {
        char t=s[i];
        if(t>='0'&&t<='9') ans=ans*radix+t-'0';
        else ans=ans*radix+t-'a'+10;
    }
        return ans;
}
//36->10进制转换防止溢出
long long changeint(string s)
{
	long long ans = 0;
	bool flag = true;
	for (int i = 0; i < s.size(); i++)
	{
		if (i == 0 && s[i] == '-') {
			flag = false;
			continue;
		}
		if ((s[i] < '0' || s[i]>'9') && (s[i] > 'z' || s[i] < 'a'))
			return 0;
		if (ans > INT64_MAX) {
			return flag ? INT64_MAX : INT64_MIN;
		}
		char t = s[i];
		if (t >= '0' && t <= '9') {
			if (ans > INT64_MAX / 36 || ans < INT64_MIN / 36) {
				if(t>'0')
					return flag ? INT64_MAX : INT64_MIN;				
			}
			ans = ans * 36 + t - '0';
			
		}			
		else {
			if (ans > INT64_MAX / 36 || ans < INT64_MIN / 36) {
				if (t > '0')
					return flag ? INT64_MAX : INT64_MIN;				
			}
			ans = ans * 36 + t - 'a' + 10;
		}
			
	}
	if (ans > INT64_MAX) {
		return flag ? INT64_MAX : INT64_MIN;
	}
	return flag?ans:-ans;
}
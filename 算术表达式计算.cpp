#include <stdio.h>

/*
C primer plus P331
fgets()可用来替代gets，fgets使用第二个参数限制读入的字符数来解决溢出问题（gets会有这个问题）
fgets的第二个参数指明了读入字符的最大数量，若为n，则读入n-1个字符(若读入n-1个字符且未遇到换行符，并使第n个字符为\0)，或读到第一个换行符为止；
该函数会将换行符储存在字符串中（gets会丢弃换行符）；
第3个参数指明要读入的文件，若从键盘读入，则参数为stdin
若读到文件结尾，则返回空指针（NULL）
与fputs配对使用（若要显示在计算机显示器上，则第二个参数为stdout）,puts函数会在待输出字符串末尾添加一个换行符，而fputs不会。
*/

/*
一步步来，做完每一步先验证一下

参考数据结构与算法分析-C语言描述 P52-56

1. 检查合法性
2. 中缀表达式转为后缀表达式
3. 计算后缀表达式
后缀表达式没有必要知道任何优先规则

一个测试用例：
原数中缀表达式：1+2*3+(4*5+6)*7
转换后的后缀表达式：（加整数结束标志@的对比）
    代码实际输出：1@2@3@*+4@5@*6@+7@*+
    你期望的输出：123*+45*6+7*+
计算结果应为：189

！！还要考虑负数...
*/

int judge(char *s){
    char stack[101]="";
    int i;
    int top=-1;
    for(i=0;s[i]!='\0';i++){
        if(s[i]==' '){ // 跳过空格
            continue;
        }
        if(s[0]!=' ' && (s[0]<'0' || s[0]>'9') && (s[0]!='(') && (s[0]!='-')){ // 第一个非空格字符一定是数字或左括号或负号才合法
            return 0;
        }
        if((s[i]<'0' || s[i]>'9') && s[i]!='(' && s[i]!=')' &&
           (s[i]!='+') && s[i]!='-' && s[i]!='*' && s[i]!='/'){
            return 0; // 含不合法字符
        }
        if(s[i]=='('){ // 括号要成对
            top++;
            stack[top] = s[i];
        }
        if(s[i]==')'){
            if(top!=-1 && stack[top]=='('){
                top--; // 出栈左括号
            }else{
                return 0; // 括号不配对
            }
        }
    }
    if(top==-1){ // 不管有无入栈操作，遍历结束后，若合法总应是-1，若有括号且均成对，则栈为空
        return 1;
    }else{
        return 0;
    }
}

// 感觉空想有点绕，但是明确目的和返回值作用后就好多了
// 运算符在何时入栈：栈顶优先级更低时入栈，故返回0时需要入栈，返回1时需要出栈
int priority(char *stack, char cal, int top) // 判断cal与栈顶字符的优先级，栈顶优先级更低时返回0，优先级等于或高于时返回1
{
    switch(cal){
        case '+':
        case '-':
            return 1; // 栈顶无论是什么字符，都高于或等于+-，即没有比+-更低的优先级
        case '*':
        case '/':
            if(stack[top]=='+' || stack[top]=='-'){
                return 0; // 栈顶是+-时，优先级低于*、/
            }else{
                return 1;
            }
         // 如果是 ( ，则直接入栈
        case '(':
            if(stack[top]=='('){
                return 1;
            }else{
                return 0; // 除(，栈顶无论是其他什么字符，都低于该字符
            }
    }
}

int convert(char *s,char *stack) // 中缀表达式(s)转为后缀表达式(stack)，返回存储后缀表达式的栈的栈顶
{
    int i;
    char calstack[101]=""; // 运算符栈
    int caltop=-1;
    int top=-1;
    for(i=0;s[i]!='\0';i++){
        if(s[i]>='0' && s[i]<='9'){ // 数字字符直接入栈，先不处理
            top++;
            stack[top]=s[i];
        }
        if(s[i]=='+' || s[i]=='-' ||  s[i]=='*' || s[i]=='/' || s[i]=='('){
            // 当遇到运算符时，则之前压入表达式栈的若为数字字符，则该整数已处理完毕，加上自定义结束符；
            // ！！注意还要考虑运算符后和右括号前的整数，尤其是中缀表达式最后一个整数的情况
            if(stack[top]>='0' && stack[top]<='9'){
                top++;
                stack[top] = '@'; // 标志一个整数结束，便于后续计算
            }
            if(s[i]=='-'){ // 处理负数情况，若为负号，直接入栈
                if(s[i-1]=='+' || s[i-1]=='-' || s[i-1]=='*' || s[i-1]=='/' || s[i-1]=='('){
                    top++;
                    stack[top]='#'; // 标志负数（以免后面无法判断是减号还是负数）
                    continue;
                }
            }
            if(caltop==-1){ // 运算符栈为空，直接入栈
                caltop++;
                calstack[caltop]=s[i];
            }else{
                while(priority(calstack,s[i],caltop)==1){ // 出栈，栈内优先级相同或更高，需出栈直至遇到优先级更低的运算符（出栈放到后缀表达式中）
                    if(calstack[caltop] == '('){ // 特例，左括号只有遇到右括号时才出栈
                        break;
                    }
                    top++;
                    stack[top]=calstack[caltop];
                    caltop--;
                    if(caltop==-1){ // ！！运算符栈为空时结束判断
                        break;
                    }
                }
                // 入栈，出栈完成后再将该运算符入栈（此时栈顶运算符优先级更低）
                caltop++;
                calstack[caltop] = s[i];
            }
        }
        if(s[i]==')'){
            if(stack[top]>='0' && stack[top]<='9'){ // 右括号前的整数
                top++;
                stack[top] = '@'; // 标志一个整数结束，便于后续计算
            }
            while(calstack[caltop]!='('){ // 出栈直至遇到对应的(（前面已保证括号合法性）
                top++;
                stack[top] = calstack[caltop];
                caltop--;
            }
            caltop--;  // 左括号出栈，但不用保存，后缀表达式中不存在括号（没有优先级规则，只有四则运算符）
        }
    }
    // 中缀表达式最后一个整数(中缀表达式读取结束时，中缀最后一个字符应是右括号 或 数字字符，故在此处也要处理；右括号的情况在上面的遍历中已经处理了)
    if(stack[top]>='0' && stack[top]<='9'){
        top++;
        stack[top] = '@'; // 标志一个整数结束，便于后续计算
    }
    while(caltop!=-1){ // 输入读取完毕，将剩下的运算符栈元素弹出直至栈为空
        top++;
        stack[top]=calstack[caltop];
        caltop--;
    }
    top++;
    stack[top]='\0';
 //   printf("%s\n",stack);
    return (top-1);
}

int main()
{
    char s[101];
    while(gets(s)!=NULL){ // 使用fgets好像有点问题，先用gets
        char stack[250]=""; // 储存后缀表达式
        int nstack[101]={0}; // 计算后缀表达式用的栈，存放整数
        int ntop=-1;
        int top;
        int i,j,k;
        int a;
        int b;
        int res=0;
        if(judge(s)==0){ // 有不合法字符或表达式开头不合法或括号不合法
            printf("\n");
            break;
        }

        top = convert(s,stack); // 中缀表达式转为后缀表达式

        // 注意计算肯定是要从头开始遍历的呀！0~top（命名好像有点问题，先不管了...）
        // 计算后缀表达式：遇到一个数就将其推入整数栈中，遇到一个运算符就弹出两个数，并将计算结果入栈，后缀表达式栈为空时，整数栈顶为计算结果
        for(i=0;i<=top;i++){
       //     printf("stack[%d]=%c\n",top,stack[top]);
            if(stack[i]=='@'){ // @标志一个整数结束，即接下来是一个整数，将数字字符转换为整数并入栈，如：中缀为12，入栈后从顶到底为@21，故倒着先输出的是低位
                j=i;
                j--;
                ntop++; // 准备入栈，！！注意nstack[ntop]也要清0，因为出栈时只是单纯的更改栈顶下标，此处要从0开始计算整数值才可以 ！！
                for(k=1,nstack[ntop]=0; j!=-1 && (stack[j]>='0' && stack[j]<='9'); j--,k*=10){
                    nstack[ntop] = nstack[ntop] + (stack[j] - '0') * k;
                }
                if(j!=-1 && stack[j]=='#'){ // 处理负数
                    nstack[ntop] = 0 - nstack[ntop]; // 如：0-1=-1
                }
  //              printf("j=%d,nstack[%d] = %d\n",j,ntop,nstack[ntop]);
            }
            if(stack[i]=='+' || stack[i]=='-' || stack[i]=='*' || stack[i]=='/'){
                b = nstack[ntop];
                ntop--;
                a = nstack[ntop];
                ntop--;
  //              printf("stack[%d]=%c,a=%d,b=%d\n",i,stack[i],a,b);
                switch(stack[i]){ // 注意break....
                    case '+':
                        res = a+b;
  //                      printf("a+b=%d\n",res);
                        break;
                    case '-':
                        res = a-b;
                        break;
                    case '*':
                        res = a*b;
  //                      printf("a*b=%d\n",res);
                        break;
                    case '/':
                        res = a/b; // 按整数处理，暂不考虑除不尽的情况
                        break;
                }
                ntop++;
                nstack[ntop] = res; // 计算结果入栈
  //              printf("nstack[%d] = %d\n",ntop,nstack[ntop]);
            }
        }
        printf("%d\n",nstack[ntop]);
    }

    return 0;
}
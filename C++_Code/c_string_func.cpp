/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-04-28 14:45:19
 */

#include <iostream>
using namespace std;

int main()
{

    char c[] = {'h', 'e', 'l', 'l', 'o'};
    // 未定义行为, c没有以 '\0' 结束
    // cout << strlen(c) <<endl;
    cout << sizeof(c) << endl;                              // 5
    char c1[]={'a','b','\0','d','e'};
    cout << strlen(c1) << ", " << sizeof(c1) << endl;       // 2, 5
    char c2[]="\\123456\123456\t";
    cout << strlen(c2) << ", " << sizeof(c2) << endl;       // 12, 13
    char d[] = {1,2,3,0,4,5,6};
    cout << strlen(d) << ", " << sizeof(d) << endl;         // 3, 7

    char st1[12]= "Yes", st2[5]= "No", st3[7]= "Or";
    cout<< strcat(strcat(st1,st3), st2) << endl;            // YesOrNo

    const char *p= "hello";
    cout << strcmp(p, "hello") << endl;                     // 比较字符串的内容
    return 0;
}


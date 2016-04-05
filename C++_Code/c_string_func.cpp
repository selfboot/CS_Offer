/*
* @Author: xuezaigds@gmail.com
* @Last Modified time: 2016-03-02 11:10:14
*/

#include <iostream>
using namespace std;

int main()
{

    char ca[] = {'h', 'e', 'l', 'l', 'o'};
    cout << strlen(ca) << endl; // 5
    char c1[]={'a','b','\0','d','e'};
    cout << strlen(c1) << endl; // 2
    char c2[]="\\123456\123456\t"; // 12
    cout << strlen(c2) << endl;
    char st1[12]= "Yes", st2[5]= "No", st3[7]= "Or";
    cout<< strcat(strcat(st1,st3), st2) << endl;

    const char *p= "hello";
    cout << strcmp(p, "hello") << endl;     // 比较字符串的内容
    return 0;
}

/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-31 18:57:14
 */

#include <iostream>
using namespace std;

class cs
{
public:
    cs(int i): data(i)  { cout << "cs(" << i <<") constructor!" << endl; }
    ~cs() { cout << "cs destructor,i(" << data << ")" << endl; }

    cs& operator=(const cs& other)
    {
        data = other.data;
        cout << "cs operator=()" << endl;
        return *this;
    }

    int get_i() const { return data; }
    void change(int i)  { data = i; }

private:
    int data;
};

cs get_cs()
{
    static int i = 0;
    return cs(i++);
}

int main()
{
    // 合法
    (get_cs() = cs(2)).change(323);
    get_cs() = cs(2);// operator=()
    get_cs().change(32);

    // 右值只能被 const 引用
    const cs& ref = get_cs();
    cout << "Here last cs object get from get_cs has not been destructed.\n";

    return 0;
}

/*
 * @Last Modified time: 2016-08-27 21:13:26
 */

//模板类作为友元时要先有声明
template <typename T>
class SmartPtr;

template <typename T>
class U_Ptr     //辅助类
{
private:
    //该类成员访问权限全部为private，因为不想让用户直接使用该类
    friend class SmartPtr<T>;      //定义智能指针类为友元，因为智能指针类需要直接操纵辅助类

    //构造函数的参数为基础对象的指针
    U_Ptr(T *ptr) :p(ptr), count(1) { }

    //析构函数
    ~U_Ptr() { delete p; }
    //引用计数
    int count;

    //基础对象指针
    T *p;
};

template <typename T>
class SmartPtr   //智能指针类
{
public:
    SmartPtr(T *ptr) :rp(new U_Ptr<T>(ptr)) { }      //构造函数
    SmartPtr(const SmartPtr<T> &sp) :rp(sp.rp) { ++rp->count; }  //复制构造函数
    SmartPtr& operator=(const SmartPtr<T>& rhs) {    //重载赋值操作符
        ++rhs.rp->count;     //首先将右操作数引用计数加1，
        if (--rp->count == 0)     //然后将引用计数减1，可以应对自赋值
            delete rp;
        rp = rhs.rp;
        return *this;
    }

    T & operator *()        //重载*操作符
    {
        return *(rp->p);
    }
    T* operator ->()       //重载->操作符
    {
        return rp->p;
    }


    ~SmartPtr() {        //析构函数
        if (--rp->count == 0)    //当引用计数减为0时，删除辅助类对象指针，从而删除基础对象
            delete rp;
        else
            cout << "还有" << rp->count << "个指针指向基础对象" << endl;
    }
private:
    U_Ptr<T> *rp;  //辅助类对象指针
};

int main()
{
    int *i = new int(2);
    {
        SmartPtr<int> ptr1(i);
        {
            SmartPtr<int> ptr2(ptr1);
            {
                SmartPtr<int> ptr3 = ptr2;

                cout << *ptr1 << endl;
                *ptr1 = 20;
                cout << *ptr2 << endl;

            }
        }
    }
    return 0;
}

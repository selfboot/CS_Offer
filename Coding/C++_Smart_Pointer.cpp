/*
 * @Last Modified time: 2016-08-27 21:09:29
 */

class Point
{
public:
    Point(int xVal = 0, int yVal = 0) :x(xVal), y(yVal) { }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }

private:
    int x, y;
};

class U_Ptr
{
private:

    friend class SmartPtr;
    U_Ptr(Point *ptr) :p(ptr), count(1) { }
    ~U_Ptr() { delete p; }

    int count;
    Point *p;
};

class SmartPtr
{
public:
    SmartPtr(Point *ptr) :rp(new U_Ptr(ptr)) { }
    SmartPtr(const SmartPtr &sp) :rp(sp.rp) { ++rp->count; }

    SmartPtr& operator=(const SmartPtr& rhs) {
        ++rhs.rp->count;
        if (--rp->count == 0)
            delete rp;
        rp = rhs.rp;
        return *this;
    }

    ~SmartPtr() {
        if (--rp->count == 0)
            delete rp;
        else
            cout << "Remain " << rp->count << " pointers point to Point object." << endl;
    }

    Point & operator *()        //重载*操作符
    {
        return *(rp->p);
    }
    Point* operator ->()       //重载->操作符
    {
        return rp->p;
    }

private:
    U_Ptr *rp;
};


int main()
{
    //定义一个基础对象类指针
    Point *pa = new Point(10, 20);
    cout << pa->getX ()<< endl;

    //定义三个智能指针类对象，对象都指向基础类对象pa
    //使用花括号控制三个指针指针的生命期，观察计数的变化
    {
        SmartPtr sptr1(pa);//此时计数count=1
        {
            SmartPtr sptr2(sptr1); //调用复制构造函数，此时计数为count=2
            {
                SmartPtr sptr3=sptr1; //调用赋值操作符，此时计数为count=3
                cout<<sptr3->getX()<<endl;
                cout<<(*sptr3).getX()<<endl;
            }
            //此时count=2
        }
        //此时count=1；
    }
    //此时count=0；pa对象被delete掉,取不到原来的值
    cout << pa->getX ()<< endl;
    return 0;
}

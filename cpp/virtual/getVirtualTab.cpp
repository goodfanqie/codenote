/*================================================================
*   Copyright (C) 2023 Goodfanqie. All rights reserved.
*   
*   File   name：getVirtualTab.cpp
*   Created  by：Goodfanqie
*   Create Date：2023.02.21.
*   Description：get the virtual table address
*
================================================================*/

/* 首先需要明白的几点：
 * 1. 同一个类的对象的虚表地址是一样的，虚表是类的共同财产
 * 2. 虚表是一块专门存放类的虚函数地址的内存
 * 3. 当实现一个对象的时候，构造器分配空间，指向虚表的指针始终是在第一个，也就是说这个指针的地址就是对象地址
 * 4. 对象地址的前八个字节存放虚表地址.
 */


#include <iostream>
using namespace std;
class base {
    public:
        int a;
    public:
        virtual void showa() 
        {
            cout << "base::a" << endl;
        }
};

int main()
{
    base b;
    cout << sizeof(b) << endl;  // 大小
    cout << &b << endl;         // 对象的地址
    cout << (int*)&b << endl;   // 通过对象地址的前八位取地址就能找到指向虚表的指针地址
    cout << *(int*)&b << endl;  // 对指针取址就可以找到虚表
}


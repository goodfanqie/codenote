学习笔记，欢迎指针！

## 多态与虚函数

**多态**按字面的意思就是多种形态。当类之间存在层次结构，并且类之间是通过继承关联时，就会用到多态。C++ 多态意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数。下面的实例中，基类 Shape 被派生为两个类，如下所示：

```c++
#include <iostream> 
using namespace std;
 
class Shape {
   protected:
      int width, height;
   public:
      Shape( int a=0, int b=0)
      {
         width = a;
         height = b;
      }
      int area()
      {
         cout << "Parent class area :" <<endl;
         return 0;
      }
};
class Rectangle: public Shape{
   public:
      Rectangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Rectangle class area :" <<endl;
         return (width * height); 
      }
};
class Triangle: public Shape{
   public:
      Triangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Triangle class area :" <<endl;
         return (width * height / 2); 
      }
};
// 程序的主函数
int main( )
{
   Shape *shape;
   Rectangle rec(10,7);
   Triangle  tri(10,5);
 
   // 存储矩形的地址
   shape = &rec;
   // 调用矩形的求面积函数 area
   shape->area();
 
   // 存储三角形的地址
   shape = &tri;
   // 调用三角形的求面积函数 area
   shape->area();
   
   return 0;
}

// 结果：
// Parent class area ：
// Parent class area ：
```

导致错误输出的原因是，调用函数 area() 被编译器设置为基类中的版本，这就是所谓的**静态多态**，或**静态链接** - 函数调用在程序执行前就准备好了。有时候这也被称为**早绑定**，因为 area() 函数在程序编译期间就已经设置好了。

但现在，让我们对程序稍作修改，在 Shape 类中，area() 的声明前放置关键字 **virtual**，如下所示：

```cpp
class Shape {
   protected:
      int width, height;
   public:
      Shape( int a=0, int b=0)
      {
         width = a;
         height = b;
      }
      virtual int area()
      {
         cout << "Parent class area :" <<endl;
         return 0;
      }
};
结果：
Rectangle class area :
Triangle class area :
```

此时，编译器看的是指针的内容，而不是它的类型。因此，由于 tri 和 rec 类的对象的地址存储在 *shape 中，所以会调用各自的 area() 函数。

正如您所看到的，每个子类都有一个函数 area() 的独立实现。这就是**多态**的一般使用方式。有了多态，您可以有多个不同的类，都带有同一个名称但具有不同实现的函数，函数的参数甚至可以是相同的。

**总结可得：** **虚函数的调用取决于指向或者引用的对象的类型，而不是指针或者引用自身的类型**

这样的虚函数所达成的多态有什么用处呢？

如上诉例子所述：**假如我们想给三角形或者长方形的长或者宽（三角形的边长）增加5个单位长度，那么我们只需要定义一个函数即可：**

```c++
void add_length(shape &s) {
	s.width += 5;
}
```

不管传进来的是什么对象，只要是shape的派生类就可以实现增加长度的目的。

**总结可得： 虚函数使得我们可以创建一个统一的基类指针列表，不同子类的函数无需知道子类的对象究竟是什么**



## 虚函数的默认参数

```cpp
#include <iostream>
using namespace std;

class Base
{
public:
    virtual void fun ( int x = 0 )
    {
        cout << "Base::fun(), x = " << x << endl;
    }
};

class Derived : public Base
{
public:
    // 这里的virtual关键字可以省略，因为只要基类里面被声明为虚函数，那么在子类中默认都是虚的
    // 或者定义为 virtual void fun ( int x = 10)
    virtual void fun ( int x )
    {
        cout << "Derived::fun(), x = " << x << endl;
    }
};


int main()
{
    Derived d1;
    Base *bp = &d1;
    bp->fun();
    return 0;
}
```

上述代码的输出始终为：

```c++
Derived::fun(), x = 0
```

原因与总结：

+ 默认参数是静态绑定的，虚函数是动态绑定的。默认参数的使用需要看指针或者引用本身的类型，而不是对象的类型。
+ **Never  redefine function’s inherited default parameters value.）**



## 虚函数表

我们先来看一个小段代码：

```c++
#include <iostream>
#include <type_traits>

using namespace std;

class base {
    public:
        virtual void tt() {};
};

class normal {
    public:
        void tt() {};
};

class derived : test {
    public:
        virtual void tt() {};
};

int main()
{
    cout << "base size: " << sizeof(base) << endl;
    cout << "derived size: " << sizeof(derived) << endl;
    cout << "normal size: " << sizeof(normal) << endl;
}
```

![image-20230221190824371](https://goofanqie-1310329970.cos.ap-nanjing.myqcloud.com/blogimg/image-20230221190824371.png)

从上述结果我们可以看到：

虽然这三个类都是只定义了一个函数tt，但是经过sizeof出来的类型大小却不一致，普通类型只有1个字节大小，而继承中的基类与派生类却都有着8个字节的大小，这是为什么呢：

其实为了实现c++的多态，c++使用了一种动态绑定的技术。这个技术的核心就是虚函数表，通过虚函数表来实现动态绑定。

### 类的虚表

每一个包含了虚函数的类都包含一个虚表，我们知道，当一个类（A）继承另一个类（B）时，类 A 会继承类 B 的函数的调用权。所以如果一个基类包含了虚函数，那么其继承类也可调用这些虚函数，换句话说，一个类继承了包含虚函数的基类，那么这个类也拥有自己的虚表。这就是为什么基类与派生类的大小相同的原因。

看一个例子:

```c++
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};
```

类 A 的虚表如图 1 所示。

![image-20230221192824104](https://goofanqie-1310329970.cos.ap-nanjing.myqcloud.com/blogimg/image-20230221192824104.png)

虚表是一个指针数组，其元素是虚函数的指针，每个元素对应一个虚函数的函数指针。**普通非虚函数是不需要经过虚函数表的调用的，所以虚函数表的元素并不包括普通函数的函数指针**，虚函数表在编译器阶段就已经构造出来了，也就是说虚函数的指针赋值发生在编译阶段。

### 虚函数表指针

虚表不是属于某个具体的对象，而是属于整个类的，就像静态对象成员一样，这是属于整个类而不是单个对象。在实际函数的调用中，为了让调用能够找到对象的虚表，每一个包含虚表的类的对象都拥有一个虚表指针，编译器在类中添加了一个指针，`*_vptr`用来指向虚表，这样当类的对象在创建时便拥有了这个指针，且这个指针的值会被设置为指向该类的虚表地址。

![image-20230221202652438](https://goofanqie-1310329970.cos.ap-nanjing.myqcloud.com/blogimg/image-20230221202652438.png)

上面指出，一个继承类的基类如果包含虚函数，那个这个继承类也有拥有自己的虚表，故这个继承类的对象也包含一个虚表指针，用来指向它的虚表。

### 动态绑定的实现

示例代码：

```c++
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};

class B : public A {
public:
    virtual void vfunc1();
    void func1();
private:
    int m_data3;
};

class C: public B {
public:
    virtual void vfunc2();
    void func2();
private:
    int m_data1, m_data4;
};
```

类 A 是基类，类 B 继承类 A，类 C 又继承类 B。类 A，类 B，类 C，其对象模型如下图 3 所示。:

![image-20230221204044568](https://goofanqie-1310329970.cos.ap-nanjing.myqcloud.com/blogimg/image-20230221204044568.png)

由于这三个类都有虚函数，故编译器为每个类都创建了一个虚表，即类 A 的虚表（A vtbl），类 B 的虚表（B vtbl），类 C 的虚表（C vtbl）。类 A，类 B，类 C 的对象都拥有一个虚表指针，`*__vptr`，用来指向自己所属类的虚表。

类 A 包括两个虚函数，故 A vtbl 包含两个指针，分别指向`A::vfunc1()`和`A::vfunc2()`。
类 B 继承于类 A，故类 B 可以调用类 A 的函数，但由于类 B 重写了`B::vfunc1()`函数，故 B vtbl 的两个指针分别指向`B::vfunc1()`和`A::vfunc2()`。
类 C 继承于类 B，故类 C 可以调用类 B 的函数，但由于类 C 重写了`C::vfunc2()`函数，故 C vtbl 的两个指针分别指向`B::vfunc1()`（指向继承的最近的一个类的函数）和`C::vfunc2()`。

虽然图 3 看起来有点复杂，但是只要抓住“**对象的虚表指针用来指向自己所属类的虚表，虚表中的指针会指向其继承的最近的一个类的虚函数，同时需要注意的是，派生类的虚表中会有基类中的所以虚函数实现，如果派生类自己重载了某个虚函数，那么需表中的该函数将指向派生类实现”**这个特点，便可以快速将这几个类的对象模型在自己的脑海中描绘出来。

非虚函数的调用不用经过虚表，故不需要虚表中的指针指向这些函数。

假设我们定义一个类 B 的对象。由于 `bObject`是类 B 的一个对象，故`bObject`包含一个虚表指针，指向类 B 的虚表。

```
int main() 
{
    B bObject;
}
```

现在，我们声明一个类 A 的指针`p`来指向对象`bObject`。虽然`p`是基类的指针只能指向基类的部分，但是虚表指针亦属于基类部分，所以`p`可以访问到对象`bObject`的虚表指针。`bObject`的虚表指针指向类 B 的虚表，所以`p`可以访问到 B vtbl。如图 3 所示。

```
int main() 
{
    B bObject;
    A *p = & bObject;
}
```

当我们使用`p`来调用`vfunc1()`函数时，会发生什么现象？

```
int main() 
{
    B bObject;
    A *p = & bObject;
    p->vfunc1();
}
```

程序在执行`p->vfunc1()`时，会发现`p`是个指针，且调用的函数是虚函数，接下来便会进行以下的步骤。

首先，根据虚表指针`p->__vptr`来访问对象`bObject`对应的虚表。虽然指针`p`是基类`A*`类型，但是`*__vptr`也是基类的一部分，所以可以通过`p->__vptr`可以访问到对象对应的虚表。

然后，在虚表中查找所调用的函数对应的条目。由于虚表在编译阶段就可以构造出来了，所以可以根据所调用的函数定位到虚表中的对应条目。对于 `p->vfunc1()`的调用，B vtbl 的第一项即是`vfunc1`对应的条目。

最后，根据虚表中找到的函数指针，调用函数。从图 3 可以看到，B vtbl 的第一项指向`B::vfunc1()`，所以 `p->vfunc1()`实质会调用`B::vfunc1()` 函数。

如果`p`指向类 A 的对象，情况又是怎么样？

```c++
int main() 
{
    A aObject;
    A *p = &aObject;
    p->vfunc1();
}
```

当`aObject`在创建时，它的虚表指针`__vptr`已设置为指向 A vtbl，这样`p->__vptr`就指向 A vtbl。`vfunc1`在 A vtbl 对应在条目指向了`A::vfunc1()`函数，所以 `p->vfunc1()`实质会调用`A::vfunc1()`函数。

可以把以上三个调用函数的步骤用以下表达式来表示：

```c_++
(*(p->__vptr)[n])(p)
```

可以看到，通过使用这些虚函数表，即使使用的是基类的指针来调用函数，也可以达到正确调用运行中实际对象的虚函数。

我们把经过虚表调用虚函数的过程称为动态绑定，其表现出来的现象称为运行时多态。动态绑定区别于传统的函数调用，传统的函数调用我们称之为静态绑定，即函数的调用在编译阶段就可以确定下来了。

那么，什么时候会执行函数的动态绑定？这需要符合以下三个条件。

- 通过指针来调用函数
- 指针 upcast 向上转型（继承类向基类的转换称为 upcast，关于什么是 upcast，可以参考本文的参考资料）
- 调用的是虚函数

如果一个函数调用符合以上三个条件，编译器就会把该函数调用编译成动态绑定，其函数的调用过程走的是上述通过虚表的机制。

## Learn From

+ [虚函数表剖析](https://leehao.me/C-%E8%99%9A%E5%87%BD%E6%95%B0%E8%A1%A8%E5%89%96%E6%9E%90/)

+ 《c++ Primer》

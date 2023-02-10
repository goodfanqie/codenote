## std::chrono
要使用chrono库，需要#include<chrono>，其所有实现均在std::chrono namespace下。注意标准库里面的每个命名空间代表了一个独立的概念。所以下文中的概念均以命名空间的名字表示！ chrono是一个模版库，使用简单，功能强大，只需要理解三个概念：`duration、time_point、clock`

### Duration

`std::chrono::duration`表示一段时间，比如两个小时，12.88秒，半个时辰，等等，只要能换算成秒即可。

```cpp
template <class Rep, class Period = ratio<1> > class duration;
```



其中`Rep`表示一种数值类型，用来表示Period的数量，比如int dloat double。示例：

ratio<3600, 1>        hours

ratio<60, 1>          minutes

ratio<1, 1>           seconds

ratio<1, 1000>        microseconds

ratio<1, 1000000>     microseconds

ratio<1, 1000000000>  nanosecons

按照对应关系其实很快就能了解这个duration的用法，就是与秒的对应关系
```cpp
typedef std::chrono::duration<int> seconds_type;
typedef std::chrono::duration<int, std::milli> milliseconds_type;
typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;
```

事实上ratio的这个模板的原型：

```cpp
template <intmax_t N, intmax_t D = 1> class ratio;
```

**N代表分子，D代表分母，所以ratio表示的是一个分数值。注意，我们自己可以定义Period，比如ratio<1,-2>表示单位时间是-0,5秒，同理3600/1就是3600秒也就是小时**

具体实例见：[duration.cpp](./duration.cpp)


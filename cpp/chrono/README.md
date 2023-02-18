## std::chrono
chrono是一个模版库，使用简单，功能强大，只需要理解三个概念：`duration、time_point、clock`

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

### clocks

std::chrono::system_clock 它表示当前的系统时钟，系统中运行的所有进程使用now()得到的时间是一致的。每一个clock类中都有确定的time_point, duration, Rep, Period类型。操作有：

+ `now()` 当前时间time_point
+ `to_time_t() time_point`转换成time_t秒
+ `from_time_t() 从time_t`转换成time_point

典型的应用是计算时间日期：

```cpp
// system_clock example
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

int main ()
{
  using std::chrono::system_clock;

  std::chrono::duration<int,std::ratio<60*60*24> > one_day (1);

  system_clock::time_point today = system_clock::now();
  system_clock::time_point tomorrow = today + one_day;

  std::time_t tt;

  tt = system_clock::to_time_t ( today );
  std::cout << "today is: " << ctime(&tt);

  tt = system_clock::to_time_t ( tomorrow );
  std::cout << "tomorrow will be: " << ctime(&tt);

  return 0;
}
```

### 最主要的应用

```cpp
auto end_time = chrono::steady_clock::now();
auto ms = chrono::duration_cast<chrono::milliseconds>(end_time start_time).count();
```

**计算时间差**

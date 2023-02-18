/*================================================================
*   Copyright (C) 2023 Goodfanqie. All rights reserved.
*   
*   File   name：clocks.cpp
*   Created  by：Goodfanqie
*   Create Date：2023.02.10.
*   Description：
*
================================================================*/


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
  // time_t才是输出形式
  std::time_t tt;

  tt = system_clock::to_time_t ( today );
  std::cout << "today is: " << ctime(&tt);

  tt = system_clock::to_time_t ( tomorrow );
  std::cout << "tomorrow will be: " << ctime(&tt);

  return 0;
}

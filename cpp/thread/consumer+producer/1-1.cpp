/*================================================================
*   Copyright (C) 2023 Goodfanqie. All rights reserved.
*   
*   File   name：1-1.cpp
*   Created  by：Goodfanqie
*   Create Date：2023.02.10.
*   Description：单消费者-单生产者模型
*
================================================================*/

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

// 循环队列的大小
static const int repository_size = 10;
// 生产的产品数量
static const int item_total = 20;

// 互斥量，保护产品缓冲区
std::mutex mtx;

// 条件变量——产品缓冲区不满
std::condition_variable repo_not_full;
// 条件变量——产品缓冲区不空
std::condition_variable repo_not_empty;

// 产品缓冲区，主要的解决问题区域
int item_buffer[repository_size];

// 消费者读取产品的位置
static std::size_t read_position = 0; 
// 生产者写入产品的位置
static std::size_t write_position = 0;

// 秒,c++ 11新功能
std::chrono::seconds second(1);

void produce_item(int i)
{
    std::unique_lock<std::mutex> lck(mtx);
    while (((write_position + 1) % repository_size) == read_position) {
        std::cout << "Producer is waiting for an empty slot..." << std::endl;
        repo_not_full.wait(lck);
    }

    item_buffer[write_position] = i; // 写入产品
    write_position++;

    if(write_position == repository_size)
    {
        write_position = 0;
    }


    // 通知消费者产品库不为空
    repo_not_empty.notify_all();
    lck.unlock();
}

int consume_item()
{
    int data;
    std::unique_lock<std::mutex> lck(mtx);
    // item buffer is empty, just wait here.
    while(write_position == read_position)
    {

    }

}



































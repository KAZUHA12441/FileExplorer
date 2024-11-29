// FileExplorer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "Explorer.hpp"
#include <iostream>


//线程库？
int main()
{
    Explorer_n::Explorer* explorer = new Explorer_n::Explorer();
    while(1)
    {
        explorer->Run();


    }

    return  0;
}

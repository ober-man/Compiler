#include <iostream>

extern "C" 
{
    void __pcl_print(int n) 
    {
        std::cout << n << std::endl; 
    }

    int __pcl_scan() 
    {
        int n;
        std::cin >> n;
        return n;
    }

    /*void __pcl_start();*/
}

/*
int main()
{
    __pcl_start();
    return 0;
}*/
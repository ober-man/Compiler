#include <iostream>
#include <exception>

#include "driver/driver.hpp"

int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        std::cout << "Error: no input file" << std::endl;
        return -1;
    }

    Driver driver(argv[1]);
    //Driver driver("scope.txt");
    try 
    {
        driver.parse();
    } 
    catch (const std::exception& ex) 
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

#include <iostream>
#include <exception>
#include <filesystem>

#include "driver/driver.hpp"
#include "codegen/codegen.hpp"

std::unique_ptr<CodeGen> globalCodeGen = nullptr;

int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        std::cout << "Error: no input file" << std::endl;
        return -1;
    }

    Driver driver(argv[1]);
    globalCodeGen = std::make_unique<CodeGen>();
    std::string outfile = std::filesystem::path(argv[1]).filename().string() + ".ll";

    try 
    {
        driver.parse();
        globalCodeGen->printIR(outfile);
    } 
    catch (const std::exception& ex) 
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

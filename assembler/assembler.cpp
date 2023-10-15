#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

void trim_string(std::string& in_string)
{
    auto it = in_string.end();
    --it;
    while (*it == ' ')
    {
        in_string.pop_back();
        --it;
    }
}

short unsigned int parse_opcode(const std::string& operation)
{
    std::map<std::string, unsigned short int> opcodemap;
    opcodemap = {{"JNS", 0x0},
                 {"LOAD", 0x1},
                 {"STORE", 0x2},
                 {"ADD", 0x3},
                 {"SUBT", 0x4},
                 {"INPUT", 0x5},
                 {"OUTPUT", 0x6},
                 {"HALT", 0x7},
                 {"SKIPCOND", 0x8},
                 {"JUMP", 0x9},
                 {"CLEAR", 0xA},
                 {"ADDI", 0xB},
                 {"JUMPI", 0xC}};

    return opcodemap[operation];
}

short unsigned int parse_line(const std::string& line, std::map<std::string, unsigned short int>& symbol_table)
{
    std::string operation;
    std::string address;
    unsigned short int opcode;
    unsigned short int addr;
    std::cout << "LINE:" << line << std::endl;
    operation = line.substr(9, 8);
    trim_string(operation);
    std::cout << "OPERATION:" << operation << std::endl;
    if (operation[0] == '!')
    {
        try 
        {
            return std::stoi(operation.substr(1), nullptr, 16);
        }
        catch(...)
        {
            std::cout << "stoi error" << std::endl;
        }
    }
    opcode = parse_opcode(operation);
    address = line.substr(19);
    trim_string(address);
    std::cout << "ADDRESS:" << address << std::endl;
    if (address[0] == '#')
    {
        address = address.substr(1);
        addr = symbol_table[address];
    }
    else
    {
        try 
        {
            addr = std::stoi(address, nullptr, 16);
        }
        catch(...)
        {
            std::cout << "stoi error" << std::endl;
        }
    }
    return (opcode * 4096 + addr);
}

void first_pass(std::string& infilestr, std::map<std::string, unsigned short int>& symbol_table)
{
    unsigned short int LC = 0x100;
    std::string line_buffer;
    std::ifstream infile;
    infile.open(infilestr);
    if (!infile)
    {
        std::cout << "FILE NOT FOUND" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (getline(infile, line_buffer))
    {
        if (line_buffer[0] != '*')
        {
            if (line_buffer[0] == '#')
            {
                std::string label = line_buffer.substr(1,8);
                trim_string(label);
                symbol_table[label] = LC;
            }

            ++LC;
        }
    }
}

std::vector<unsigned short int> second_pass(std::string& infilestr, std::map<std::string, unsigned short int>& labels)
{
    std::vector<unsigned short int> machine_code;
    unsigned short int LC = 0x0;
    std::string line_buffer;
    std::ifstream infile;
    infile.open(infilestr);
    if (!infile)
    {
        std::cout << "FILE NOT FOUND" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (getline(infile, line_buffer))
    {
        if (line_buffer[0] != '*')
        {
            machine_code.push_back(parse_line(line_buffer, labels));
        }
    }
    return machine_code;
}

void output_to_file(std::string& outfilestr, std::vector<unsigned short int> machine_code)
{
    std::ofstream outfile(outfilestr);
    if (outfile.is_open())
    {
        for (auto& x : machine_code)
        {
            outfile << std::hex << std::setw(4) << std::setfill('0') << x << "\n";
        }

    }
    else
    {
        std::cout << "OUTPUT FILE ERROR" << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::string infilestr(argv[1]);
    std::string outfilestr(argv[2]);
    std::map<std::string, unsigned short int> symbol_table;
    std::vector<unsigned short int> machine_code;
    first_pass(infilestr, symbol_table);
    machine_code = second_pass(infilestr, symbol_table);
    output_to_file(outfilestr, machine_code);
    std::cout << "Program Assembled" << std::endl;
    std::cin.get();  
    return 0;
}
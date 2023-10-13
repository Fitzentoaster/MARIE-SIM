#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

//Main Men Size
#define MAIN_MEM_SIZE 0xFFF

//OpCodes
#define JNS 0
#define LOAD 1
#define STORE 2
#define ADD 3
#define SUBT 4
#define INPUT 5
#define OUTPUT 6
#define HALT 7
#define SKIPCOND 8
#define JUMP 9
#define CLEAR 0xA
#define ADDI 0xB
#define JUMPI 0xC

struct Instruction
{
    unsigned short int opcode;
    unsigned short int addr;
};

class Marie
{
    private:
        //Registers and Main Memory
        signed short int main_memory[MAIN_MEM_SIZE + 1];  //Main Memory Array
        signed short int AC;                              //Accumulator
        signed short int MAR;                             //Mem Address Register
        signed short int MBR;                             //Mem Buffer Register
        signed short int PC;                              //Program Counter
        signed short int IR;                              //Instruction Register
        signed short int InREG;                           //Input Register
        signed short int OutREG;                          //Output Register

    public:

        //Constructor, initialize mem and regs to 0x0
        Marie()
        {
            init_registers();
            init_main_memory();
        }

        //Init registers to 0, except PC which inits to 0x100
        void init_registers()
        {
            AC = 0x0;
            MAR = 0x0;
            MBR = 0x0;
            PC = 0x100;
            IR = 0x0;
            InREG = 0x0;
            OutREG = 0x0;
        }

        //Dump Memory and end pgm
        void end_program()
        {
            dump_main_memory();
            dump_registers();
            exit(EXIT_SUCCESS);
        }

        //Init main memory to 0000s
        void init_main_memory()
        {
            for (int i = 0; i <= MAIN_MEM_SIZE; ++i)
            {
                main_memory[i] = 0x0;
            }
        }

        //ABEND 
        void abnormal_end(int soc)
        {
            std::cout << "ABEND: SOC : " << soc << std::endl;
            end_program();
        }

        //Program Loading Error
        void load_prog_error()
        {
            std::cout << "ERROR LOADING PROGRAM" << std::endl;
            end_program();
        }

        //Load Main Memory: use command line inputfile to load MEM
        void load_main_memory(std::string infilestr)
        {
            std::string line_buffer;
            std::ifstream infile;
            infile.open(infilestr);
            if (!infile)
            {
                load_prog_error();
            }
            unsigned short int opcode;
            unsigned short int addr;
            int cur_mem_loc = 0x100;
            while (getline(infile, line_buffer))
            {
                if (line_buffer.length() > 4 || line_buffer.length() < 1)
                {
                    load_prog_error();
                }
                std::string opc = line_buffer.substr(0, 1);
                try 
                {
                    opcode = std::stoi(opc, nullptr, 16);
                }
                catch (...)
                {
                    load_prog_error();
                }
                std::string adr = line_buffer.substr(1, 3);
                try 
                {
                    addr = std::stoi(adr, nullptr, 16);
                }
                catch (...)
                {
                    load_prog_error();
                }
                main_memory[cur_mem_loc] = addr + (opcode * 0x1000);
                ++cur_mem_loc;
                if (cur_mem_loc > 0xFFF)
                {
                    load_prog_error();
                }
            }
        }

        //Core Dump
        void dump_main_memory()
        {
            std::cout << "MAIN MEMORY DUMP" << std::endl;
            int j = 0x0;
            for (size_t i = 0; i <= MAIN_MEM_SIZE; ++i)
            {
                std::cout << std::setfill('0') << std::setw(3) << i << ":" << std::hex << std::setw(4)  << main_memory[i] << " ";
                ++j;
                if (j == 0x10)
                {
                    std::cout << std::endl;
                    j = 0;
                }
            }
        }

        //Register Dump
        void dump_registers()
        {
            std::cout << std::endl;
            std::cout << "REGISTERS DUMP" << std::endl;
            std::cout << "ACCUMULATOR     = " << std::setfill('0') << std::hex << std::setw(4) << AC << std::endl;
            std::cout << "MEM ADDR REG    = " << MAR << std::setw(4) << std::hex << std::endl;
            std::cout << "MEM BUFFER REG  = " << MBR << std::setw(4) << std::hex << std::endl;
            std::cout << "PROGRAM COUNTER = " << std::setw(4) << std::hex << PC << std::endl;
            std::cout << "INSTRUCTION REG = " << std::setw(4) << std::hex << IR << std::endl;
            std::cout << "INPUT REGISTER  = " << std::setw(2) << std::hex << InREG << std::endl;
            std::cout << "OUTPUT REGISTER = " << std::setw(2) << std::hex << OutREG << std::endl;
        }

        //Parse an instruction into the Instruction format
        Instruction parse_instruction(short unsigned int inst)
        {
            if (inst > 0xCFFF)
            {
                abnormal_end(1);
            }
            Instruction return_inst;
            std::stringstream inst_ss;
            inst_ss << std::hex << std::setfill('0') << std::setw(4) << inst;
            std::string inst_str(inst_ss.str());
            std::string opc = inst_str.substr(0, 1);
            try 
            {
                return_inst.opcode = std::stoi(opc, nullptr, 16);
            }
            catch(...)
            {
                abnormal_end(1);
            }
            std::string adr = inst_str.substr(1, 3);
            try
            {
                return_inst.addr = std::stoi(adr, nullptr, 16);
            }
            catch(...)
            {
                abnormal_end(5);
            }
            
            return return_inst;
        }

        //Run Program Function
        void run_program()
        {
            while (PC <= 0xFFF)
            {
                run_current_instruction();
            }
        }

        //Fetch the current instruction and run it
        void run_current_instruction()
        {
            Instruction inst = parse_instruction(main_memory[PC]);
            MAR = PC;
            IR = main_memory[MAR];
            ++PC;
            MAR = inst.addr;
            MBR = main_memory[MAR];
            execute_instruction(inst);
        }

        //JNS Instruction execution
        void execute_JNS(Instruction& inst)
        {
            MBR = PC;
            main_memory[MAR] = MBR;
            MBR = inst.addr;
            AC = 1;
            AC = AC + MBR;
            PC = AC;
        }

        //LOAD Instruction execution
        void execute_LOAD()
        {
            AC = MBR;
        }

        //STORE Instruction execution
        void execute_STORE()
        {
            MBR = AC;
            main_memory[MAR] = MBR;
        }

        //ADD Instruction execution
        void execute_ADD()
        {
            AC += MBR;
        }

        //SUBT Instruction execution
        void execute_SUBT()
        {
            AC -= MBR;
        }

        //INPUT Instruction execution
        void execute_INPUT()
        {
            std::cout << "Paused for input:" << std::endl;
            std::cin >> InREG;
            AC = InREG;
        }

        //OUTPUT Instruction execution
        void execute_OUTPUT()
        {
            OutREG = AC;
            std::cout << AC << std::endl;
        }

        //HALT Instruction execution
        void execute_HALT()
        {
            end_program();
        }

        //SKIPCOND Instruction execution
        void execute_SKIPCOND(Instruction& inst)
        {
            if (inst.addr == 0x800)
            {
                PC = (AC > 0)? PC + 1: PC;
            }
            else if (inst.addr == 0x400)
            {
                PC = (AC == 0)? PC + 1: PC;
            }
            else if (inst.addr == 0x000)
            {
                PC = (AC < 0)? PC + 1: PC;
            }
        }

        //JUMP Instruction execution
        void execute_JUMP(Instruction& inst)
        {
            PC = inst.addr;
        }

        //CLEAR Instruction execution
        void execute_CLEAR()
        {
            AC = 0;
        }

        //ADDI Instruction execution
        void execute_ADDI()
        {
            MAR = MBR;
            MBR = main_memory[MAR];
            AC += MBR;
        }

        //JUMPI Instruction execution
        void execute_JUMPI()
        {
            PC = MBR;
        }

        //Parse opcode and execute instruction
        void execute_instruction(Instruction& inst)
        {
            switch (inst.opcode)
            {
                case JNS:
                    execute_JNS(inst);
                    break;
                case LOAD:
                    execute_LOAD();
                    break;
                case STORE:
                    execute_STORE();
                    break;
                case ADD:
                    execute_ADD();
                    break;
                case SUBT:
                    execute_SUBT();
                    break;
                case INPUT:
                    execute_INPUT();
                    break;
                case OUTPUT:
                    execute_OUTPUT();
                    break;
                case HALT:
                    execute_HALT();
                    break;
                case SKIPCOND:
                    execute_SKIPCOND(inst);
                    break;
                case JUMP:
                    execute_JUMP(inst);
                    break;
                case CLEAR:
                    execute_CLEAR();
                    break;
                case ADDI:
                    execute_ADDI();
                    break;
                case JUMPI:
                    execute_JUMPI();
                    break;
                                
            }
        }
};

int main(int argc, char** argv)
{
    Marie myMarie;
    std::string infile(argv[1]);
    myMarie.load_main_memory(infile);
    std::cout << "Program Loaded. Press enter to run." << std::endl;
    std::cin.get();    
    myMarie.run_program();
    myMarie.end_program();
    return 0;
}
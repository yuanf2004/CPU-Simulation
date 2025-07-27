#include "cpu.h"
#include <iostream>

class CentralProcessingUnit{

private:
    Registers r;
    RandomAccessMemory ram;
    ArithmeticLogicUnit alu;
    ControlUnit cu;

public:
    //Constructor
    CentralProcessingUnit()
        :alu(&r, &ram), cu(&r, &ram)
    {
    };

    void run(){
        // Run the CPU by giving it inputs

        uint16_t user_i;

        while(1){
            // Test Input Format A: XXXX XXXX XXXX XXXX
            // ADDI - REGDEST - REGA - IMM
            // Test Input A Actual: 1000 1111 0000 0111
            // ADDI - REG 15 - REG 0 - 7
            // Add immediate to register 15 what register 0 is (0) and 7
            // So, register 15 should now hold 7

            // Test Input Format B: XXXX XXXX XXXXXXXX
            // STORE - REGSRC - MEMLOC
            // Test Input B Actual: 0001 1111 01111111
            // STORE - REGISTER 3 - MEMLOC 15
            // Now, memory location 127 should contain 7

            std::cout << "Enter your instruction: \n";
            std::cin >> user_i;
            std::cout << std::endl;
            cu.decode_instruction(user_i);
            std::cout << r.get_data_general_purpose_register(15);
        }
    }




};
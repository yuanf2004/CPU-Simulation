#include "cpu.h"
#include <iostream>

    //Constructor
    CentralProcessingUnit::CentralProcessingUnit()
        :alu(&r, &ram), cu(&r, &ram, &alu)
    {};

    void CentralProcessingUnit::run(){
        // Run the CPU by giving it inputs
        
        uint16_t user_i;
        
        while(1){
            std::cout << "Enter your instruction: \n";
            std::cin >> user_i;
            cu.decode_instruction((uint16_t) user_i);
            std::cout << "Register 12 currently holds: ";
            std::cout << r.get_data_general_purpose_register(12) << std::endl;
        }
    };



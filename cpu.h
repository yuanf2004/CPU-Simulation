#ifndef CPU_H
#define CPU_H

#include "stdint.h"
#include "ram.h"
#include "registers.h"
#include "alu.h"
#include "cu.h" 
#include "assembler.h"
#include <string>
#include <iostream>
#include <limits>

class CentralProcessingUnit{
private:
    Registers r;
    RandomAccessMemory ram;
    ArithmeticLogicUnit alu;
    ControlUnit cu;
    Assembler asmb;
    
public: 
    CentralProcessingUnit();
    void run_continuous_loop(void);
    void run_assembly_file(std::string assembly_fpath);
    uint16_t test_run_assembly_file(std::string assembly_fpath, std::string optype);
};

#endif
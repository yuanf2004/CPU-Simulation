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
    bool str_to_instr(std::string *s, uint16_t *ui);
};

#endif
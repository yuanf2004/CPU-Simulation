#ifndef ALU_H
#define ALU_H

#include "stdint.h"
#include "registers.h"
#include "ram.h"

class ArithmeticLogicUnit{
private:
    Registers *r;
    RandomAccessMemory *ram;
public:
    ArithmeticLogicUnit(Registers *r, RandomAccessMemory *ram);
    void alu_load(uint16_t regdest, uint16_t memloc);
    void alu_store(uint16_t regsrc, uint16_t memloc);
    void alu_add(uint16_t regdest, uint16_t rega, uint16_t regb);
    void alu_sub(uint16_t regdest, uint16_t rega, uint16_t regb);
    void alu_and(uint16_t regdest, uint16_t rega, uint16_t regb);
    void alu_or(uint16_t regdest, uint16_t rega, uint16_t regb);
    void alu_xor(uint16_t regdest, uint16_t rega, uint16_t regb);
    void alu_not(uint16_t regdest, uint16_t rega);
    void alu_addi(uint16_t regdest, uint16_t rega, uint16_t imm);
    void alu_subi(uint16_t regdest, uint16_t rega, uint16_t imm);
    void alu_andi(uint16_t regdest, uint16_t rega, uint16_t imm);
    void alu_ori(uint16_t regdest, uint16_t rega, uint16_t imm);
    void alu_xori(uint16_t regdest, uint16_t rega, uint16_t imm);
    void alu_jmp();
    void alu_jz();
    void alu_jnz();
};

#endif
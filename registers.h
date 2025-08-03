#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

class GeneralPurposeRegister {
private:    
    uint16_t data;
public:
    uint16_t get_data(void);
    void update_data(uint16_t d);
    void reset_data(void);
};

class InstructionRegister{
private:
    uint16_t data;
public:
    uint16_t get_data();
    void update_data(uint16_t id);
    void reset_data(void);
};

class ProgramCounter{
    private: 
        uint16_t address;
    public:
        uint16_t get_address(void);
        void set_address(uint16_t a);
        void reset_address(void);
};

class Registers{

private:
    GeneralPurposeRegister gpr[32];
    InstructionRegister ir;
    ProgramCounter pc;

    void init_general_purpose_registers(void){
    // On instantiation, populate general purpose registers with 0 
        for(int i = 0; i < 32; i++){
            gpr[i].update_data(0);
        }
    };
    
    void init_instruction_register(void){
    // On instantiation, populate instruction registers with 0
        ir.update_data(0);
    };

    void init_program_counter(void){
    // On instantiation, initialize program counter to be 0
        pc.set_address(0);
    };

public:
    Registers(void);
    uint16_t get_data_general_purpose_register(uint16_t reg);
    void update_general_purpose_register(uint16_t reg, uint16_t data);
    void clear_all_general_purpose_registers(void);
    void clear_instruction_register(void);
    void clear_program_counter(uint16_t addr);
    void update_program_counter(uint16_t addr);
    uint16_t get_program_counter(void);
    void update_instruction_register(uint16_t data);
    uint16_t get_instruction_register(void);
};

#endif
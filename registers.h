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

    void init_general_purpose_registers(void);
    void init_instruction_register(void);
    void init_program_counter(void);

public:
    Registers(void);
    uint16_t get_data_general_purpose_register(uint16_t reg);
    void update_general_purpose_register(uint16_t reg, uint16_t data);
    void clear_all_general_purpose_registers(void);
    void clear_instruction_register(void);
    void clear_program_counter(uint16_t addr);
};

#endif
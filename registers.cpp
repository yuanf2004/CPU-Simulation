#include "stdint.h"
#include "registers.h"

// GeneralPurposeRegister Class

    uint16_t GeneralPurposeRegister::get_data(void){
        return data;
    };

    void GeneralPurposeRegister::update_data(uint16_t d){
        data = d;
    };

    void GeneralPurposeRegister::reset_data(void){
        data = 0;
    };

// InstructionRegister Class

    uint16_t InstructionRegister::get_data(){
        return data;
    };

    void InstructionRegister::update_data(uint16_t id){
        data = id;
    };

    void InstructionRegister::reset_data(void){
        data = 0;
    };   

// Program counter keeps track of next instruction address

    uint16_t ProgramCounter::get_address(void){
    // Get current address of program counters
        return address;
    };

    void ProgramCounter::set_address(uint16_t a){
        address = a;
    };

    void ProgramCounter::reset_address(void){
        address = 0;
    };

    Registers::Registers(void){
    // Constructor
        init_general_purpose_registers();
        init_instruction_register();
        init_program_counter();
    };

    uint16_t Registers::get_data_general_purpose_register(uint16_t reg){
        return gpr[reg].get_data();
    };

    void Registers::update_general_purpose_register(uint16_t reg, uint16_t data){
    // Update register i with data
        gpr[reg].update_data(data);
    };

    void Registers::clear_all_general_purpose_registers(void){
    // Clear all general purpose register values
        for(int i = 0; i < 32; i++){
            gpr[i].reset_data();
        }
    };

    void Registers::clear_instruction_register(void){
    // Clear instruction register
        ir.reset_data();
    };

    void Registers::clear_program_counter(uint16_t addr){
    // Set the program counter's address
        pc.set_address(addr);
    };

    void Registers::update_program_counter(uint16_t addr){
        pc.set_address(addr);
    }

    uint16_t Registers::get_program_counter(void){
        return pc.get_address();
    }

    void Registers::update_instruction_register(uint16_t data){
        ir.update_data(data);
    }

    uint16_t Registers::get_instruction_register(void){
        return ir.get_data();
    }

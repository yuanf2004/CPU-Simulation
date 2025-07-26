#include "stdint.h"

class GeneralPurposeRegister {
    // Hold values for general CPU purposes
private:    
    uint16_t data;

public:
    uint16_t get_data(void){
        return data;
    }

    void update_data(uint16_t d){
        data = d;
    }

    void reset_data(void){
        data = 0;
    }
};

class InstructionRegister{
// Hold data for current instruction (16-bit format)
private:
    uint16_t data;
    
public:
    uint16_t get_data(){
        return data;
    }

    void update_data(uint16_t id){
        data = id;
    }

    void reset_data(void){
        data = 0;
    }   
};

class ProgramCounter{
// Program counter keeps track of next instruction address
    private: 
        uint16_t address;

    public:

        uint16_t get_address(void){
        // Get current address of program counters
            return address;
        }

        void set_address(uint16_t a){
            address = a;
        }

        void reset_address(void){
            address = 0;
        }
};

class Registers{

private:
    // Array to hold all general purpose registers 
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
    Registers(void){
    // Constructor
        init_general_purpose_registers();
        init_instruction_register();
        init_program_counter();
    };

    uint16_t get_data_general_purpose_register(uint16_t reg){
        return gpr[reg].get_data();
    };

    void update_general_purpose_register(uint16_t reg, uint16_t data){
    // Update register i with data
        gpr[reg].update_data(data);
    };

    void clear_all_general_purpose_registers(void){
    // Clear all general purpose register values
        for(int i = 0; i < 32; i++){
            gpr[i].reset_data();
        }
    };

    void clear_instruction_register(void){
    // Clear instruction register
        ir.reset_data();
    };

    void clear_program_counter(uint16_t addr){
    // Set the program counter's address
        pc.set_address(addr);
    };
};

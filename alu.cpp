#include "alu.h"

    ArithmeticLogicUnit::ArithmeticLogicUnit(Registers *r, RandomAccessMemory *ram){
        this->r = r;
        this->ram = ram;
    };

    void ArithmeticLogicUnit::alu_load(uint16_t regdest, uint16_t memloc){
        uint16_t ram_data = ram->get_ramcell(memloc);
        r->update_general_purpose_register(regdest, ram_data);
    };

    void ArithmeticLogicUnit::alu_store(uint16_t regsrc, uint16_t memloc){
        uint16_t reg_data = r->get_data_general_purpose_register(regsrc);
        ram->update_ramcell(memloc, reg_data);    
    };

    void ArithmeticLogicUnit::alu_add(uint16_t regdest, uint16_t rega, uint16_t regb){
        uint16_t rega_data = r->get_data_general_purpose_register(rega);
        uint16_t regb_data = r->get_data_general_purpose_register(regb);
        r->update_general_purpose_register(regdest, (rega_data + regb_data));
    };

    void ArithmeticLogicUnit::alu_sub(uint16_t regdest, uint16_t rega, uint16_t regb){
        uint16_t rega_data = r->get_data_general_purpose_register(rega);
        uint16_t regb_data = r->get_data_general_purpose_register(regb);
        r->update_general_purpose_register(regdest, (rega_data - regb_data));
    };

    void ArithmeticLogicUnit::alu_and(uint16_t regdest, uint16_t rega, uint16_t regb){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    uint16_t regb_data = r->get_data_general_purpose_register(regb);
    r->update_general_purpose_register(regdest, (rega_data & regb_data));        
    };

    void ArithmeticLogicUnit::alu_or(uint16_t regdest, uint16_t rega, uint16_t regb){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    uint16_t regb_data = r->get_data_general_purpose_register(regb);
    r->update_general_purpose_register(regdest, (rega_data | regb_data));    
    };

    void ArithmeticLogicUnit::alu_xor(uint16_t regdest, uint16_t rega, uint16_t regb){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    uint16_t regb_data = r->get_data_general_purpose_register(regb);
    r->update_general_purpose_register(regdest, (rega_data ^ regb_data)); 
    };

    void ArithmeticLogicUnit::alu_not(uint16_t regdest, uint16_t rega){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, ~(rega_data));
    };

    void ArithmeticLogicUnit::alu_addi(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data + imm));
    };

    void ArithmeticLogicUnit::alu_subi(uint16_t regdest, uint16_t rega, uint16_t imm){    
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data - imm));
    };

    void ArithmeticLogicUnit::alu_andi(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data & imm));
    };

    void ArithmeticLogicUnit::alu_ori(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data | imm));
    };

    void ArithmeticLogicUnit::alu_xori(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data ^ imm));
    };

    void ArithmeticLogicUnit::alu_jmp(uint16_t jmpdest){
        // set the program counter to input address
        r->update_program_counter(jmpdest);

    };

    void ArithmeticLogicUnit::alu_beq(uint16_t rega, uint16_t regb, uint16_t jmpdest){
        uint16_t rega_val = r->get_data_general_purpose_register(rega);
        uint16_t regb_val = r->get_data_general_purpose_register(regb);

        // jump if equal
        if(rega_val == regb_val){
            r->update_program_counter(jmpdest);
        }
    };

    void ArithmeticLogicUnit::alu_bne(uint16_t rega, uint16_t regb, uint16_t jmpdest){
        uint16_t rega_val = r->get_data_general_purpose_register(rega);
        uint16_t regb_val = r->get_data_general_purpose_register(regb);

        // jump if not equal
        if(rega_val != regb_val){
            r->update_program_counter(jmpdest);
        }
    };





    

    




    


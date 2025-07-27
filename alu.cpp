#include "alu.h"

class ArithmeticLogicUnit{
    
    private:
        Registers *r;
        RandomAccessMemory *ram;

    public:
    ArithmeticLogicUnit(Registers *r, RandomAccessMemory *ram){
        // Constructor
        this->r = r;
        this->ram = ram;
    };

    void alu_load(uint16_t regdest, uint16_t memloc){
        uint16_t ram_data = ram->get_ramcell(memloc);
        r->update_general_purpose_register(regdest, ram_data);
    };

    void alu_store(uint16_t regsrc, uint16_t memloc){
        uint16_t reg_data = r->get_data_general_purpose_register(regsrc);
        ram->update_ramcell(memloc, reg_data);    
    };

    void alu_add(uint16_t regdest, uint16_t rega, uint16_t regb){
        uint16_t rega_data = r->get_data_general_purpose_register(rega);
        uint16_t regb_data = r->get_data_general_purpose_register(regb);
        r->update_general_purpose_register(regdest, (rega_data + rega_data));
    };

    void alu_sub(uint16_t regdest, uint16_t rega, uint16_t regb){
        uint16_t rega_data = r->get_data_general_purpose_register(rega);
        uint16_t regb_data = r->get_data_general_purpose_register(regb);
        r->update_general_purpose_register(regdest, (rega_data + rega_data));
    };

    void alu_and(uint16_t regdest, uint16_t rega, uint16_t regb){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    uint16_t regb_data = r->get_data_general_purpose_register(regb);
    r->update_general_purpose_register(regdest, (rega_data & regb_data));        
    };

    void alu_or(uint16_t regdest, uint16_t rega, uint16_t regb){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    uint16_t regb_data = r->get_data_general_purpose_register(regb);
    r->update_general_purpose_register(regdest, (rega_data | regb_data));    
    };

    void alu_xor(uint16_t regdest, uint16_t rega, uint16_t regb){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    uint16_t regb_data = r->get_data_general_purpose_register(regb);
    r->update_general_purpose_register(regdest, (rega_data ^ regb_data)); 
    };

    void alu_not(uint16_t regdest, uint16_t rega, uint16_t regb){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, ~(rega_data));
    };

    void alu_addi(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data + imm));
    };

    void alu_subi(uint16_t regdest, uint16_t rega, uint16_t imm){    
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data - imm));
    };

    void alu_andi(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data & imm));
    };

    void alu_ori(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data | imm));
    };

    void alu_xori(uint16_t regdest, uint16_t rega, uint16_t imm){
    uint16_t rega_data = r->get_data_general_purpose_register(rega);
    r->update_general_purpose_register(regdest, (rega_data ^ imm));
    };

    //TODO: To be filled out later
    void alu_jmp(){
    };

    //TODO: To be filled out later
    void alu_jz(){
    };

    //TODO: to be filled out later
    void alu_jnz(){
    };





    

    




    



};

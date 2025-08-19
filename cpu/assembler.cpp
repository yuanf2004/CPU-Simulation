#include "assembler.h"

Assembler::Assembler(){};

uint16_t Assembler::generate_instruction_code(std::string assembly_line){
        // generate an instruction based off of one line of assembly
        uint16_t instruction_code = 0x00;

        uint16_t op = fetch_op(assembly_line);
        // 4 bit msb representing opcode
        instruction_code |= (op << 12);
        uint16_t instruction_12_to_0 = fetch_non_op(op, assembly_line);

        // bitwise or with rest of instruction
        instruction_code |= instruction_12_to_0;
        return instruction_code;
};

std::vector<uint16_t> Assembler::generate_instruction_code_branch(std::string assembly_line){

    std::vector<uint16_t> instr_lines;
    uint16_t instruction_code = 0x00;

    // beq and bne take two lines of instructions
    uint16_t op = fetch_op(assembly_line);
    instruction_code |= (op << 12);

    uint16_t instruction_12_to_0 = fetch_non_op(op, assembly_line);
    instruction_code |= instruction_12_to_0;
    // add first line to vector
    instr_lines.push_back(instruction_code);

    std::vector<std::string> ls = line_split(assembly_line);

    // line to jump will always be at element 3
    uint16_t instruction_two = std::stoi(ls[3]);
    // add second line to vector
    instr_lines.push_back(instruction_two);

    return instr_lines;
}

std::vector<std::string> Assembler::line_split(std::string assembly_line){
    // helper function to split the line of assembly
    std::vector<std::string> asmb_components;
    std::istringstream iss(assembly_line);
    std::string word;
    while(iss >> word){
        asmb_components.push_back(word);
    }
    return asmb_components;
}

std::vector<std::string> Assembler::assembly_split(std::string fpath){
// take a .txt file and split up each line to be returned as a vector containing all
    std::string fpath_extend = "assembly_files/" + fpath;
    std::ifstream file(fpath_extend);
    std::string line;
    std::vector<std::string> assembly_lines;

    while(std::getline(file, line)){
        assembly_lines.push_back(line);
    };

    return assembly_lines;
};

uint16_t Assembler::fetch_op(std::string assembly_line){
    // case sensitive assembly 

    // op will be the 0th element of the vector
    std::string op = line_split(assembly_line).at(0);
    if(op == "load"){
        return 0x0;
    }
    else if(op == "store"){
        return 0x1;
    }
    else if(op == "add"){
        return 0x2;
    }
    else if(op == "sub"){
        return 0x3;
    }
    else if(op == "and"){
        return 0x4;
    }
    else if(op == "or"){
        return 0x5;
    }
    else if(op == "xor"){
        return 0x6;
    }
    else if(op == "not"){
        return 0x7;
    }
    else if(op == "addi"){
        return 0x8;
    }
    else if(op == "subi"){
        return 0x9;
    }
    else if(op == "andi"){
        return 0xA;
    }
    else if(op == "ori"){
        return 0xB;
    }
    else if(op == "xori"){
        return 0xC;
    }
    else if(op == "jmp"){
        return 0xD;
    }
    else if(op == "beq"){
        return 0xE;
    }
    else if(op == "bne"){
        return 0xF;
    }   
    // If error case
    return 0xFFFF;
};

uint16_t Assembler::fetch_non_op(uint16_t op, std::string assembly_line){
// return bits 12 to 0 of instruction depending on opcode
    std::vector<std::string> asmb_components = line_split(assembly_line);
    uint16_t instr = 0x0;
    switch(op){
        case(0x0):
            // load rd memloc
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_mem(asmb_components.at(2));
            return instr;
        case(0x1): 
            // store rs memloc
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_mem(asmb_components.at(2));
            return instr;
        case(0x2):
            // add rd ra rb    
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x3):
            // sub rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x4):
            // and rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x5):
            // or rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x6):
            // xor rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x7):
            // not rd ra
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            return instr;
        case(0x8):
            // addi rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0x9):
            // subi rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0xA): 
            // andi rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_imm(asmb_components.at(3));
        case(0xB):
            // ori rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0xC):
            // xori rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0xD):
            // jmp
            instr |= fetch_jmp(asmb_components.at(1));
            return instr;
        case(0xE):
            // beq
            // rega bits 11:8 
            // regb bits 7:4
            instr |= (fetch_rs(asmb_components.at(1), 'n') << 8);
            instr |= (fetch_rs(asmb_components.at(2), 'n') << 4);
            return instr;
        case(0xF):
            // bne
            // rega bits 11:8 
            // regb bits 7:4
            instr |= (fetch_rs(asmb_components.at(1), 'n') << 8);
            instr |= (fetch_rs(asmb_components.at(2), 'n') << 4);
            return instr;
        default:
            //error 
            return 0xFFFF;
    }
};

uint16_t Assembler::fetch_rs(std::string reg, char type){
    // splits the number from rs to get the bit representation
    std::string num_str;
    int bit_shift;

    if(type == 'd'){
        bit_shift = 8;
    }
    else if(type == 'a'){
        bit_shift = 4;
    }
    else if(type == 'b'){
        bit_shift = 0;
    }
    // type n for no shifts
    else if(type == 'n'){
        bit_shift = 0;
    }
    else{
        //error
        return 0xFFFF;
    }
    
    // grab number digits after rs
    for (char c : reg){
        if(std::isdigit(c)){
            num_str += c;
        }
    }

    if(!num_str.empty()){
        return static_cast<uint16_t>(std::stoi(num_str)) << bit_shift;
    }
    else{
        // error
        return 0xFFFF;
    }
};

uint16_t Assembler::fetch_imm(std::string imm){
    // return immediate value as an int, not a str
    return static_cast<uint16_t>(std::stoi(imm));
};

uint16_t Assembler::fetch_mem(std::string mem){
// decode the memory and return it as a uint
    std::string num_str;

    for(char c : mem){
        if(std::isdigit(c)){
            num_str += c;
        }
    }

    if(!num_str.empty()){
        return static_cast<uint16_t>(std::stoi(num_str));
    }
    // error return
    return 0xFFFF;
};

uint16_t Assembler::fetch_jmp(std::string line){
// decode the memory line to jump to
    return (uint16_t) std::stoi(line);
}
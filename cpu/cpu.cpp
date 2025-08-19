#include "cpu.h"

    //Constructor
    CentralProcessingUnit::CentralProcessingUnit()
        :alu(&r, &ram), cu(&r, &ram, &alu)
    {};

    //this feature does not support jmp, beq, and bne

    void CentralProcessingUnit::run_continuous_loop(void){
        // Run the CPU by giving it inputs
        //bool decode_ok = false;
        uint16_t user_i;
        std::string buffer_i;
        int loop_count = 0;
        
        while(1){

            // clear the input line when running program for the first time
            if(loop_count > 0){
                std::cout << "Enter your instruction: \n";
            }
            std::getline(std::cin, buffer_i);
            loop_count++;

            // exit program on user input
            if(buffer_i == "exit"){
                return;
            }

            if(!buffer_i.empty()){
                // use a vector to determine if user instruction 
                std::vector<std::string> buffer_split;
                std::stringstream iss(buffer_i);
                std::string word;
                while (iss >> word){
                    buffer_split.push_back(word);
                }

                // error handling for invalid commands
                std::string first_op;
                for(char c : buffer_split[0]){
                    if(std::isalpha(c)){
                        first_op += c;
                    }
                }

                // error handling for invalid commands
                if(valid_ops.find(first_op) == valid_ops.end()){
                    std::cout << "Invalid command, exiting...\n";
                    return;
                }

                // split up the memory type (reg/memloc) with the index
                std::string memory_index;
                std::string memory_type;

                // look for rs and memloc if vector is size 1
                if(buffer_split.size() == 1){
                    for(char c : buffer_split[0]){
                        if(std::isdigit(c)){
                            memory_index += c;
                        }
                        else{
                            memory_type += c;
                        }
                    }
                }

                // return memory data if index and type are populated
                if(!memory_index.empty() && !memory_type.empty()){
                    if(memory_type == "rs"){
                        if(std::stoi(memory_index) > 31){
                            std::cout << "Invalid register number!\n";
                            return;
                        }
                        uint16_t reg_value = r.get_data_general_purpose_register(std::stoi(memory_index));
                        std::cout << "Register " + memory_index + "'s value is: ";
                        std::cout << reg_value << "\n";
                    }
                    else if(memory_type == "memloc"){
                        if(std::stoi(memory_index) > 65535){
                            std::cout << "Invalid memory location number!\n";
                            return;
                        }
                        uint16_t memloc_value = ram.get_ramcell(std::stoi(memory_index));
                        std::cout << "Memory location " + memory_index + "'s value is: ";
                        std::cout << memloc_value << "\n";
                    }
                }
            
                uint16_t instr = asmb.generate_instruction_code(buffer_i);
                cu.decode_instruction(instr);
            } 
        }
    };

    void CentralProcessingUnit::run_assembly_file(std::string assembly_fpath){
         // run assembly file
       
        // NOTE: Assembly path is from the root of the project so it will always
        // be assembly_files/...

        // vector of assembly lines in text
        std::vector<std::string> asmb_lines = asmb.assembly_split(assembly_fpath);
        // stores instructions for ram
        std::vector<uint16_t> instruction_vector;

        // note: code may seem redundant, but is written to mimic an
        // actual cpu as closely as possible

        // codeblock: populate a buffer instruction vector to fill 
        // ram code segment
        for(int i = 0; i < asmb_lines.size(); i++){
            std::string s = asmb_lines[i];

            // handle double instruction add if beq or bne
            if(s.find("beq") != s.npos | s.find("bne") != s.npos){
                std::vector<uint16_t> buffer = asmb.generate_instruction_code_branch(s);
                for(uint16_t i : buffer){
                    instruction_vector.push_back(i);
                }
            }

            // else, do normal handling
            else{
                uint16_t instr =  asmb.generate_instruction_code(s);
                instruction_vector.push_back(instr);
            }
        }

        // codeblock: fill assembly with instructions
        for(int i = 0; i < instruction_vector.size(); i++){
            ram.update_ramcell(i, instruction_vector[i]);
        }

        // reset program counter before running assembly
        r.clear_program_counter();

        // codeblock: read from ram, stops reading when program realizes that pc
        // is at a line larger than the line length of the assembly .txt file input
        while(r.get_program_counter() < instruction_vector.size()){
            uint16_t program_counter = r.get_program_counter();
            // load into instruction register
            r.update_instruction_register(ram.get_ramcell(program_counter));

            // holds multiple instructions if opcode is beq, bne, etc...
            std::vector<uint16_t> many_instr_v;

            uint16_t opcode = r.get_instruction_register() >> 12;
            if(opcode == 0xE || opcode == 0xF){
                // add first instruction
                many_instr_v.push_back(r.get_instruction_register());
                // update and fetch second instruction, 16 bit jmp instr
                r.update_program_counter(program_counter+1);
                program_counter = r.get_program_counter();
                r.update_instruction_register(ram.get_ramcell(program_counter));
                // add second instruction
                many_instr_v.push_back(r.get_instruction_register());
            }

            // normal operation decoding 
            if(many_instr_v.empty()){
                // if not jmp, update pc
                if(r.get_instruction_register() >> 12 != 0xD){
                    cu.decode_instruction(r.get_instruction_register());
                    r.update_program_counter(program_counter+1);
                }
                // if jmp, don't update pc
                else{
                    cu.decode_instruction(r.get_instruction_register()); 
                }
            }
            // beq/bne operation decoding
            else{
                cu.decode_instruction(many_instr_v);
                // beq/bne should update pc by itself, thus no increment
            }
        }

    //todo: idea, instead of giving the warning make it so the code 
    //todo: just does not run at all.

    //  warning notice for code segment writing
        std::cout << "\nAssembly file finished processing!\n\n";
        std::cout << "\nWARNING: Your code segment of the RAM goes from memloc0 to ";
        std::cout << "memloc" << asmb_lines.size()-1 << ". ";
        std::cout << "If your assembly overwrites any of these memory locations, ";
        std::cout << "your program will not work.\n\n";

        std::cout << "What would you like to do now?\n";
        std::cout << "rs(number) - view value at register\n";
        std::cout << "memloc(number) - view value at memory location\n";
        std::cout << "exit - leave this program\n";

        while(1){
            std::string decision;
            std::cout << "What would you like to do now?\n";
            std::cin >> decision;
            
            if(decision == "exit"){
                return;
            }

            // variables to hold the instruction split
            std::string memory_index;
            std::string memory_type;

            // split the instruction into memory type and index
            if(decision.find("rs") != decision.npos || decision.find("memloc") != decision.npos){
                for(char c : decision){
                    if(std::isdigit(c)){
                        memory_index += c;
                    }
                    else{
                        memory_type += c;
                    }
                }

                // view register
                if(memory_type == "rs"){
                    if(std::stoi(memory_index) > 31){
                        std::cout << "Invalid register number!\n";
                        return;
                    }
                    std::cout << "Register " + memory_index + " holds: ";
                    std::cout << r.get_data_general_purpose_register(std::stoi(memory_index)) << "\n";
                }
                // view memory location
                else if(memory_type == "memloc"){
                    if(std::stoi(memory_index) > 65535){
                        std::cout << "Invalid memory location number!\n";
                        return;
                    }
                    std::cout << "Memory location " + memory_index + " holds: ";
                    std::cout << ram.get_ramcell(std::stoi(memory_index)) << "\n";
                }

            // invalid option retry
            }
            else{
                std::cout << "Not a valid option, please try again.\n";
            }
        }
    };

    uint16_t CentralProcessingUnit::test_run_assembly_file(std::string assembly_fpath, std::string optype){
        // run assembly file
       
        // NOTE: Assembly path is from the root of the project so it will always
        // be assembly_files/...

        // vector of assembly lines in text
        std::vector<std::string> asmb_lines = asmb.assembly_split(assembly_fpath);
        // stores instructions for ram
        std::vector<uint16_t> instruction_vector;

        // note: code may seem redundant, but is written to mimic an
        // actual cpu as closely as possible

        // codeblock: populate a buffer instruction vector to fill 
        // ram code segment
        for(int i = 0; i < asmb_lines.size(); i++){
            std::string s = asmb_lines[i];

            // handle double instruction add if beq or bne
            if(s.find("beq") != s.npos || s.find("bne") != s.npos){
                std::vector<uint16_t> buffer = asmb.generate_instruction_code_branch(s);
                for(uint16_t i : buffer){
                    instruction_vector.push_back(i);
                }
            }

            // else, do normal handling
            else{
                uint16_t instr =  asmb.generate_instruction_code(s);
                instruction_vector.push_back(instr);
            }
        }

        // codeblock: fill assembly with instructions
        for(int i = 0; i < instruction_vector.size(); i++){
            ram.update_ramcell(i, instruction_vector[i]);
        }

        // reset program counter before running assembly
        r.clear_program_counter();

        // codeblock: read from ram, stops reading when program realizes that pc
        // is at a line larger than the line length of the assembly .txt file input
        while(r.get_program_counter() < instruction_vector.size()){
            uint16_t program_counter = r.get_program_counter();
            // load into instruction register
            r.update_instruction_register(ram.get_ramcell(program_counter));

            // holds multiple instructions if opcode is beq, bne, etc...
            std::vector<uint16_t> many_instr_v;

            uint16_t opcode = r.get_instruction_register() >> 12;
            if(opcode == 0xE || opcode == 0xF){
                // add first instruction
                many_instr_v.push_back(r.get_instruction_register());
                // update and fetch second instruction, 16 bit jmp instr
                r.update_program_counter(program_counter+1);
                program_counter = r.get_program_counter();
                r.update_instruction_register(ram.get_ramcell(program_counter));
                // add second instruction
                many_instr_v.push_back(r.get_instruction_register());
            }

            // normal operation decoding 
            if(many_instr_v.empty()){
                // if not jmp, update pc
                if(r.get_instruction_register() >> 12 != 0xD){
                    cu.decode_instruction(r.get_instruction_register());
                    r.update_program_counter(program_counter+1);
                }
                // if jmp, don't update pc
                else{
                    cu.decode_instruction(r.get_instruction_register()); 
                }
            }
            // beq/bne operation decoding
            else{
                cu.decode_instruction(many_instr_v);
                // beq/bne should update pc by itself, thus no increment
            }
        }

        // rs5 here should return as 10 based on "test_beqbne.txt"
        if(optype == "beq"){
            uint16_t rs5 = r.get_data_general_purpose_register(5);
            return rs5;
        }
        // rs0 here should return as 3 based on "test_jmp.txt"
        else if(optype == "jmp"){
            uint16_t rs0 = r.get_data_general_purpose_register(0);
            return rs0;
        }
        else{
            return 0;
        }
    }


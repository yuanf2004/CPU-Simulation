#include "cpu.h"

    //Constructor
    CentralProcessingUnit::CentralProcessingUnit()
        :alu(&r, &ram), cu(&r, &ram, &alu)
    {};

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
                        uint16_t reg_value = r.get_data_general_purpose_register(std::stoi(memory_index));
                        std::cout << "Register " + memory_index + "'s value is: ";
                        std::cout << reg_value << "\n";
                    }
                    else if(memory_type == "memloc"){
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
        // Option to run assembly file
       
        // NOTE: Assembly path is from the root of the project so it will always
        // be assembly_files/...

        // vector of assembly lines in text
        std::vector<std::string> asmb_lines = asmb.assembly_split(assembly_fpath);
        // stores instructions for ram
        std::vector<uint16_t> instruction_vector;

        // note: this part may seem redundant but is done to mimic 
        // the cpu as closely as possible

        // populate the instruction vector
        for(std::string s : asmb_lines){
            uint16_t instr = asmb.generate_instruction_code(s);
            instruction_vector.push_back(instr);
        }

        // fill up ram with instructions
        for(int i = 0; i < asmb_lines.size(); i++){
            ram.update_ramcell(i, instruction_vector[i]);
        }

        //reset program counter before running assembly
        r.update_program_counter(0);

        //read from ram as long as program counter does not exceed assembly
        //.txt file size
        while(r.get_program_counter() < instruction_vector.size()){
            uint16_t program_counter = r.get_program_counter();
            // load into instruction register
            r.update_instruction_register(ram.get_ramcell(program_counter));


            
            // holds multiple instructions if opcode is beq, bne, etc...
            std::vector<uint16_t> many_instr_v;
            uint16_t opcode = r.get_instruction_register() >> 12;

            if(opcode == 0xE | opcode == 0xF){
                // add first instruction
                many_instr_v.push_back(r.get_instruction_register());
                // update and fetch new instruction
                r.update_program_counter(program_counter+1);
                r.update_instruction_register(ram.get_ramcell(program_counter));
                // add second instruction
                many_instr_v.push_back(r.get_instruction_register());
            }

            // handle decoding differently for if it is a regular or multi line
            // instruction(s)
            if(many_instr_v.empty()){
               cu.decode_instruction(r.get_instruction_register()); 
            }
            else{
                cu.decode_instruction(many_instr_v);
            }

            //iterate pc after line is read
            r.update_program_counter(program_counter+1);
        }

        //todo: idea, instead of giving the warning make it so the code 
        //todo: just does not run at all.

    // this will actually need to write to the memory all the instruction lines?
        bool cont = 1;
    //notice for code segment writing
        std::cout << "\nWARNING: Your code segment of the RAM goes from memloc0 to ";
        std::cout << "memloc" << asmb_lines.size()-1 << ". ";
        std::cout << "If your assembly overwrites any of these memory locations, ";
        std::cout << "your program will not work.\n\n";

        std::cout << "What would you like to do now?\n";
        std::cout << "rs(number) - view value at register\n";
        std::cout << "memloc(number) - view value at memory location\n";
        std::cout << "exit - leave this program\n";
        while(cont){
            std::string decision;
            std::cout << "What would you like to do now?\n";
            std::cin >> decision;
            if(decision == "exit"){
                return;
            }

            std::string memory_index;
            std::string memory_type;

            // split the instruction into memory type and index
            if(!decision.find("rs") | !decision.find("memloc")){
                for(char c : decision){
                    if(std::isdigit(c)){
                        memory_index += c;
                    }
                    else{
                        memory_type += c;
                    }
                }

                if(memory_type == "rs"){
                    std::cout << "Register " + memory_index + " holds: ";
                    std::cout << r.get_data_general_purpose_register(std::stoi(memory_index)) << "\n";
                }
                else if(memory_type == "memloc"){
                    std::cout << "Memory location " + memory_index + " holds: ";
                    std::cout << ram.get_ramcell(std::stoi(memory_index)) << "\n";
                }
            }
            else{
                std::cout << "Not a valid option, please try again.\n";
            }
        }
    };

    // Deprecated
    // bool CentralProcessingUnit::str_to_instr(std::string *s, uint16_t *ui){
    //     /* 
    //     Helper function to convert user input as a string into 
    //     binary instruction for the control unit 
    //     */
    //     // Check for 0b/0B prefix
    //     if(s->find("0b") == 0 || s->find("0B") == 0){
    //         *ui = std::stoul(*s, nullptr, 2);
    //         return true;
    //     }
    //     // Check for 0x/0X prefix
    //     else if(s->find("0x") == 0 || s->find("0X") == 0){
    //         // convert to uint
    //         *ui = std::stoul(*s, nullptr, 16);
    //         return true;
    //     }
    //     else{
    //         std::cout << "Invalid instruction input, must be 0x or 0b.\n";
    //         return false;
    //     }
    // };




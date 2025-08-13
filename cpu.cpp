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

        // TODO: Need to assign the instructions to the beginning of MEMLOC
        // and then read from the memloc instead of what i currently have, where
        // it is just splitting an assembly .txt file and reading it from a vector

        std::vector<std::string> asmb_lines = asmb.assembly_split(assembly_fpath);
        for(std::string s : asmb_lines){
            uint16_t instr = asmb.generate_instruction_code(s);
            cu.decode_instruction(instr);
        }
    // this will actually need to write to the memory all the instruction lines?
        bool cont = 1;
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




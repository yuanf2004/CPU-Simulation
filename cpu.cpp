#include "cpu.h"

    //Constructor
    CentralProcessingUnit::CentralProcessingUnit()
        :alu(&r, &ram), cu(&r, &ram, &alu)
    {};

    void CentralProcessingUnit::run_continuous_loop(void){
        // Run the CPU by giving it inputs
        
        bool decode_ok = false;
        uint16_t user_i;
        std::string buffer_i;
        
        while(1){
            std::cout << "Enter your instruction: \n";
            std::cin >> buffer_i;
            decode_ok = str_to_instr(&buffer_i, &user_i);
            if(decode_ok){
                cu.decode_instruction((uint16_t) user_i);
                std::cout << "Register 12 currently holds: ";
                std::cout << r.get_data_general_purpose_register(12) << std::endl;
            };
            decode_ok = true;
        }
    };

    void CentralProcessingUnit::run_assembly_file(std::string assembly_fpath){
    // Run assembly file option
    // TODO: Will most likely need to pass the file content or string or something for this one to run
    // this function will turn the file path and split into a vector of
    // each line of instructions
    std::vector<std::string> asmb_lines = asmb.assembly_split(assembly_fpath);
    // this will actually need to write to the memory all the instruction lines?
        
    };

    bool CentralProcessingUnit::str_to_instr(std::string *s, uint16_t *ui){
        /* 
        Helper function to convert user input as a string into 
        binary instruction for the control unit 
        */
        // Check for 0b/0B prefix
        if(s->find("0b") == 0 || s->find("0B") == 0){
            *ui = std::stoul(*s, nullptr, 2);
            return true;
        }
        // Check for 0x/0X prefix
        else if(s->find("0x") == 0 || s->find("0X") == 0){
            *ui = std::stoul(*s, nullptr, 16);
            return true;
        }
        else{
            std::cout << "Invalid instruction input, must be 0x or 0b.\n";
            return false;
        }
    };




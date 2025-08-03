#ifndef SIMULATION_H
#define SIMULATION_H

#include <set>
#include <filesystem>
#include "cpu.h"

namespace fs = std::filesystem;

class Simulation{
    private:
        // Remembers the user choice
        int user_choice;
        // Hold the choice for continuous instructions to CPU or Assembly input
        /*
        Program Type:
        0 (default) - Continuous Loop
        1 - Assembly
        */
        int program_type = 0; 
        // Holds the path of the selected assembly file
        std::string selected_assembly_file;
        // Valid choices for the setting used for comparison
        const std::set<int> valid_choices = {1,2,3};
        CentralProcessingUnit cpu;

    public:
        void setting(void);
        void run_sim(void);
        void change_program_type(void);
        void choose_assembly_file(void);
};
    
#endif
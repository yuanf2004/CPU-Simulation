#include "simulation.h"

void Simulation::setting(void){
// Setting menu
    std::cout << "Settings\n";
    std::cout <<"[1] Program Type\n[2] Select Assembly File\n";
    

}

void Simulation::change_program_type(void){
// Display options to change the program type
    std::string program_type_text;
    int program_type_buffer;
    
    if(program_type == 0){
        program_type_text = "Continuous Loop";    
    }
    else{
        program_type_text = "Assembly File";
    }

    std::cout << "Current Program Type: " + program_type_text + "\n";
    std::cout << "Enter Desired Program Type:\n[1] Continuous Loop\n[2] Assembly File\n";
    std::cin >> program_type_buffer;

    if(program_type_buffer != 0 && program_type_buffer != 1){
        std::cout << "Invalid choice, no changes made.\n";
    }
    else{
        program_type = program_type_buffer;
        std::cout << "Change made successfully!\n";
    }
};

void Simulation::choose_assembly_file(void){
    // Display text to choose assembly file to execute
    //TODO: Need to use the filesystem library to read through all .txt file names
};

void Simulation::run_sim(void){
// User interface for CPU simulation program
    //Display options in terminal
        user_choice = 0;
        std::cout << "Welcome to the CPU Simulator!\n"; 

        while(1){
            while(valid_choices.find(user_choice) == valid_choices.end()){
                std::cout << "What would you like to do?\n";
                std::cout << "[1] Run Simulation\n[2] Change Simulation Settings\n[3] Exit\n";
                std::cin >> user_choice;
                if(valid_choices.find(user_choice) == valid_choices.end()){
                    std::cout << "Not a valid option.\n";
                }
            }

            switch(user_choice){
                case 1:
                    // Run Simulation Depending on Option
                    break;
                case 2:
                    // Go to options
                    break;
                case 3:
                    return;
            }
            // Reset decision to go back to menu
            user_choice = 0;
        }
        //TODO: Need to add handling to exit program for the continuous loop and assembly options.
}
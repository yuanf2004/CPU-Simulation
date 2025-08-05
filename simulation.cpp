#include "simulation.h"

void Simulation::setting(void){
// Setting menu
    int setting_choice;
    std::cout << "Settings\n";
    std::cout <<"[1] Program Type\n[2] Select Assembly File\n";
    std::cin >> setting_choice;

    if(setting_choice == 1){
        change_program_type();
    }
    else if(setting_choice == 2){
        choose_assembly_file();
    }
    else{
        std::cout << "Invalid choice.\n";
        return;
    }
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
    // namespace for easier writing 

    std::unordered_map<int, std::string> assembly_files;
    
    std::cout << "Current Readable Assembly Files: \n";
    int i = 0;

    //Populate set with file names
    for(const auto& entry : fs::directory_iterator("assembly_files")){
        if(entry.is_regular_file()){
            i++;
            std::cout << "[" << i  << "] " << "\n";
            std::cout << entry.path().filename() << "\n";
            // populate hashmap
            assembly_files.insert({i, entry.path().filename()});
        }
    }
    int assembly_file_sel_buffer;
    std::cout << "Please enter your desired assembly file:\n";
    std::cin >> assembly_file_sel_buffer;
    if(assembly_file_sel_buffer > 1 && assembly_file_sel_buffer < i){
        selected_assembly_file = assembly_files.at(assembly_file_sel_buffer);
    }
    else{
        std::cout << "Invalid choice, file was not saved.\n";
    }
};

void Simulation::run_sim(void){
// User interface for CPU simulation program
    //Display options in terminal
        user_choice = 1;
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
                    // run simulation depending on option
                    if(program_type){
                        cpu.run_continuous_loop();
                    }
                    else{
                        cpu.run_assembly_file(selected_assembly_file);   
                    }
                    break;
                case 2:
                    // go to setting
                    setting();
                    break;
                case 3:
                    // exit program
                    return;
            }
            // Reset decision to go back to menu
            user_choice = 0;
        }
        //TODO: Need to add handling to exit program for the continuous loop and assembly options.
}

// Include necessary Standard Library headers
#include <integrator.hpp>

#include <iostream>

int main() 
{  
    // Define initial time, final time, step size
    // and number of states for numerical integration
    double t0 {0}, tf {5}, step_size {0.01};
    unsigned int select {0}, num_states {0};
  
    std::cout << "\nWelcome to the LTI state-space system numerical simulator" << std::endl;
    std::cout << std::endl;
    
    while (1)
    {
        std::cout << "=================================" << std::endl;
        std::cout << "Numerical integration parameters:" << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << "Number of state variables: " << num_states << std::endl;
        std::cout << "Initial simulation time: " << t0 << " [s]" << std::endl;
        std::cout << "Final simulation time: " << tf << " [s]" << std::endl;
        std::cout << "Simulation step-size: " << step_size << " [s]" << std::endl;
        std::cout << "=================================" << std::endl;
       
        std::cout << "1. Modify numerical integration paremeters" << std::endl;
        std::cout << "2. Read matrices from data directory and run simulation" << std::endl;
        std::cout << "3. Exit program" << std::endl;
        std::cout << "Please enter your selection: ";
        std::cin >> select; std::cout << std::endl;

        // Switch statement for main menu selection
        switch (select) 
        {
            case 1:
                std::cout << "Please enter the new numerical integration parameters." << std::endl;
                std::cout << "Initial simulation time (seconds): "; std::cin >> t0;
                std::cout << "Final simulation time (seconds): "; std::cin >> tf;
                std::cout << "Simulation step-size (seconds): "; std::cin >> step_size;
                std::cout << std::endl;
                break;

            case 2:
                
                switch(num_states)
                {
                    case 1:
                        simulate_system<Eigen::Matrix<double, 1, 1>>(t0, tf, step_size);
                        std::cout << "Simulation completed!" << std::endl;
                        std::cout << std::endl;
                        break;
                
                    case 2:
                        simulate_system<Eigen::Matrix<double, 2, 1>>(t0, tf, step_size);
                        std::cout << "Simulation completed!" << std::endl;
                        std::cout << std::endl;
                        break;
            
                    case 3:
                        simulate_system<Eigen::Matrix<double, 3, 1>>(t0, tf, step_size);
                        std::cout << "Simulation completed!" << std::endl;
                        std::cout << std::endl;
                        break;
            
                    case 4:
                        simulate_system<Eigen::Matrix<double, 4, 1>>(t0, tf, step_size);
                        std::cout << "Simulation completed!" << std::endl;
                        std::cout << std::endl;
                        break;
            
                    case 5:
                        simulate_system<Eigen::Matrix<double, 5, 1>>(t0, tf, step_size);
                        std::cout << "Simulation completed!" << std::endl;
                        std::cout << std::endl;
                        break;
            
                    case 6:
                        simulate_system<Eigen::Matrix<double, 6, 1>>(t0, tf, step_size);
                        std::cout << "Simulation completed!" << std::endl;
                        std::cout << std::endl;
                        break;
            
                    default:
                        std::cout << "Error: invalid number of state variables!" << std::endl;
                        std::cout << std::endl;
                        break;
                } break;
            
            case 3:
                return (0);

            default:
                std::cout << "Error: invalid selection from menu." << std::endl;
                break;
        }
    }
    return (0);
}

#include "Simulation.h"

#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
    srand(static_cast<unsigned int>(time(0)));                                     // O(1)

    std::cout << "-------------- Bunny Valley --------------------" << "\n";    // O(1)
    std::cout << " Starting the simulation..." << "\n";                         // O(1)
    std::cout << std::endl;                                                      // O(1)

    Simulation newGame;                                                           // O(1)
    
    while (newGame.getBunnyCount() > 0)              // O(t) where t is every iteration 
    {
        newGame.runOneTurn();                       // O(n^2) per turn 

        if (newGame.getBunnyCount() > 0)           // O(1)
        {
            std::cout << "\nPress Enter to continue...";      // O(1)
            std::cin.get();                                   //O(1)
        }
    }

    std::cout << "\nAll bunnies have gone extinct after "     // O(1)
        << newGame.getYear() << " years.\n";




    return 0;
}

// main() = O(t * n^2)

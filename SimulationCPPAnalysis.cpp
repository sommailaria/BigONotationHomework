#include "Simulation.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>

Simulation::Simulation()
{
  

    bunnies.push_back(new Bunny("Fluffy", "white", Gender::Female, 0));
    bunnies.back() ->announceBirth();

    bunnies.push_back(new Bunny("TipTap", "brown", Gender::Male, 0));
    bunnies.back()->announceBirth();

    bunnies.push_back(new Bunny("Gina", "grey", Gender::Female, 0));
    bunnies.back()->announceBirth();

    bunnies.push_back(new Bunny("Tamburino", "black", Gender::Male, 0));
    bunnies.back()->announceBirth();

    bunnies.push_back(new Bunny("Giulio Cesare", "gold", Gender::Radioactive, 0));
    bunnies.back()->announceBirth();

}

Simulation::~Simulation()
{
    for (Bunny* b : bunnies)       // O(n) where n is num of bunnies in bunnies
    { 
        delete b;                 // O(1)    
    }
}
// ~Simulation() = O(n)

int Simulation::getYear() const
{
    return year;                  // O(1)
}

//getYear() = O(1)

int Simulation::getBunnyCount() const
{
    return static_cast<int>(bunnies.size());   // O(1)
}

// getBunnyCount() = O(1)

void Simulation::runOneTurn()
{
    year += 1;                                                  // O(1)                                      
    std::cout << "\n";
    std::cout << "========================================\n";  // O(1)
    std::cout << "           BUNNY VALLEY\n";                   // O(1) 
    std::cout << "               YEAR " << year << '\n';        // O(1) 
    std::cout << "========================================\n\n"; // O(1) 

    std::cout << "--- Aging ---\n";
    for (Bunny* b : bunnies) {                               // O(n) where n is num of bunnies in bunnies                          
        b->aging();                                         //  O(1)
    } 
    bool foundMale = false;                                         // O(1)
    std::vector<std::string> femaleColor;                           // O(1)
    for (Bunny* b  : bunnies) {                                     // O(n) where n is num of bunnies in bunnies                                   
        if (b->getGender() == Gender::Male && b->isAdult()) {      // O(1)
            foundMale = true;                                      // O(1)
        }
        if (b->getGender() == Gender::Female && b->isAdult()) {    // O(1)
            femaleColor.push_back(b->getColor());                  // O(1)
        }
    }
    std::cout << "--- Births ---\n";                                               //O(1)
    if (foundMale) {                                                               // O(1)
        for (size_t i = 0; i < femaleColor.size(); i++) {                          // O(n) where n is num of colors in femaleColor
            int nameIndex = rand() % static_cast<int>(nameBank.size());            // O(1)
            std::string namePick = nameBank[nameIndex];                            // O(1)
            int genderPick = rand() % 2;                                           // O(1) 
            Gender babyGender = (genderPick == 0) ? Gender::Male : Gender::Female; // O(1)
            Bunny* newBunny = new Bunny(namePick, femaleColor[i], babyGender, 0);  // O(1)
            bunnies.push_back(newBunny);                                           // O(1)
            newBunny-> announceBirth();                                            // O(1)
        }
    }
    int findVampireBunnies = 0;                                                  // O(1)                                        
    for (Bunny* b : bunnies) {                                                  // O(n) where n is num of bunnies in bunnies
        if (b->isRadioactive()) {                                               // O(1)
            findVampireBunnies++;                                               // O(1)
        }
    }
    std::vector<int> collectEligibleBunnies{};                               // O(1)
    for (int i = 0; i < static_cast<int>(bunnies.size()); i++) {            // O(n) where n is num of bunnies in bunnies
        if (!bunnies[i]->isRadioactive()) {                                 // O(1)
            collectEligibleBunnies.push_back(i);                           // O(1)
        }
    }
    std::cout << "--- Infections ---\n";                                  // O(1)
    for (int i = 0; i < findVampireBunnies; i++)                          // O(n) where is num of bunnies in findVampire bunnies
    {
        if (collectEligibleBunnies.empty())                              // O(1)
        {
            break;                                                      // O(1)
        }
        int infectionChance = rand() % 100;                            // O(1)

        if (infectionChance < 30)                                     // O(1)
        {
            int pickIndex = rand() % static_cast<int>(collectEligibleBunnies.size());  // O(1)
            int pickBunny = collectEligibleBunnies[pickIndex];                         // O(1)
            bunnies[pickBunny]->gender = Gender::Radioactive;                          //O(1)
            bunnies[pickBunny]->canGetPregnant = false;                               // O(1)
            bunnies[pickBunny]->canMakeVampireBunny = true;                           // O(1)
            bunnies[pickBunny]->announceInfection();                                  // O(1)
            collectEligibleBunnies.erase(collectEligibleBunnies.begin() + pickIndex); // O(n) where n is num of bunnies
                                                                                      // in collectEligibleBunnies
        }
    }
        

    // Deaths (old age)
    std::cout << "--- Deaths ---\n";                                                  // O(1)
    for (auto it = bunnies.begin(); it != bunnies.end(); )                           // O(n) where n is num of bunnies in bunnies
    {
        if ((*it)->isTooOld())                                                       // O(1)
        {
            (*it)->announceDeath("old age");                                        // O(1)
            delete *it;                                                            // O(1)
            it = bunnies.erase(it);                                                // O(n)
        }
        else                                                                      // O(1)
        {
            ++it;                                                                 // O(1)
        }
    }

    // Food shortage
    if (bunnies.size() > 1000) {                                               // O(1)
        int half = bunnies.size() / 2;                                         // O(1) 
        std::vector<int> pickHalfBunnies{};                                   // O(1)
        for (int i = 0; i < static_cast<int>(bunnies.size()); i++) {          // O(n) where n is num of bunnies in bunnies    
            pickHalfBunnies.push_back(i);                                     // O(1)                                     
        }
        std::vector<int> condemnedBunnies{};                                   // O(1)
        for (int i = 0; i < half; i++) {                                       // O(n)
            int pickIndex = rand() % static_cast<int>(pickHalfBunnies.size()); // O(1)
            int pickBunny = pickHalfBunnies[pickIndex];                        // O(1)
            condemnedBunnies.push_back(pickBunny);                             // O(1)
            pickHalfBunnies.erase(pickHalfBunnies.begin() + pickIndex);        // O(n)
        }
        std::sort(condemnedBunnies.begin(), condemnedBunnies.end(), std::greater<int>()); // O(n log n)
        // O(c) where c is num of bunnies in condemnedBunnies
        for (int i = 0; i < static_cast<int>(condemnedBunnies.size()); i++)                
        {
            int deadIndex = condemnedBunnies[i];                                        // O(1)
            bunnies[deadIndex]->announceDeath("food shortage");                        // O(1)
            bunnies.erase(bunnies.begin() + deadIndex);                               // O(1)
        }
    }

    // runOneTurn = O(n^2)

    // Display all bunnies' details, sorted by age
    std::sort(bunnies.begin(), bunnies.end(), [](const Bunny* a, const Bunny* b) {  // O(n log n)
        return a->getAge() < b->getAge();                                           // O(1)
        });
    std::cout << "Current Bunny Population\n";                                      
    std::cout << "-------------------------------------------------------------\n"; 

    std::cout << std::left                                                          
        << std::setw(20) << "Name"                                                  
        << std::setw(6) << "Age"
        << std::setw(15) << "Color"
        << std::setw(15) << "Gender" << '\n';

    std::cout << "-------------------------------------------------------------\n";

    for (const Bunny* b : bunnies)                                                 //  O(n) where n is num of bunnies in bunnies
    {
        std::cout << *b << '\n';
    }

    std::cout << "-------------------------------------------------------------\n";
}


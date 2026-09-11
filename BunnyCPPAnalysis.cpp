#include "Bunny.h"

Bunny::Bunny(const std::string& givenName,
    const std::string& birthColor,
    const Gender& birthGender,
    const int& ageAtBirth)
{
    color = birthColor;
    name = givenName;
    gender = birthGender;
    age = ageAtBirth;

    canGetPregnant = (gender == Gender::Female);
    canMakeVampireBunny = (gender == Gender::Radioactive);
}

// Bunny::Bunny() = O(1)

void Bunny::announceBirth() const
{
    std::cout << "A new bunny is born! Their name is " 
        << name << ".\n";
} 

// announceBirth() = O(1);


void Bunny::aging()
{
    age += 1;                                       
    std::cout << name
        << " is now "
        << age
        << " years old.\n";    
} 
//aging() = O(1)


void Bunny::announceInfection() const
{
    std::cout << name
        << " has been infected and is now a vampire bunny!\n"; 
} 

// announceInfection() = O(1)


void Bunny::announceDeath(const std::string& cause) const
{
    std::cout << name
        << " has died of "
        << cause
        << ".\n";                                                     
} 

// announceDeath = O(1)

std::string Bunny::getColor() const
{
    return color;                                    
}

// getColor() = O(1)


Gender Bunny::getGender() const
{
    return gender;
}

// getGender() = O(1)

bool Bunny::isAdult() const
{
    return age >= 2 && !isRadioactive();
}

// isAdult = O(1)

bool Bunny::isRadioactive() const
{
    return gender == Gender::Radioactive;
}

// isRadioactive = O(1)

int Bunny::getAge() const
{
    return age;
}

// getAge = O(1)

std::string Bunny::getName() const
{
    return name;
}

// getName = O(1)

bool Bunny::isTooOld() const
{
    if (isRadioactive())
    {
        return age > 50;
    }

    return age > 10;
}

// isTooOld = O(1)


std::string genderToString(Gender g)
{
    switch (g)
    {
    case Gender::Male:
        return "Male";

    case Gender::Female:
        return "Female";

    case Gender::Radioactive:
        return "Radioactive";
    }

    return "Unknown";
}

// genderToString() = O(1)


std::ostream& operator<<(std::ostream& os, const Bunny& b)
{
    os << std::left
        << std::setw(20) << b.getName()
        << std::setw(6) << b.getAge()
        << std::setw(15) << b.getColor()
        << std::setw(15) << genderToString(b.getGender());

    return os;
}

// std::ostream& operator<< = O(1)


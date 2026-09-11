#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum class Positions
{
    goalkeeper = 1,
    forward = 2
};

struct referee
{
    std::string name{};
    int joinedMatches{};

    int refereeJoinMatch()
    {
        return joinedMatches++;
    }
};

class footballPlayer
{
public:
    std::string playerName{};
    int skillsLevel{};
    std::string team{};
    Positions position{};
    int matchesPlayed{};
    int goalsScored{};
};

class footballTeam
{
public:
    std::string teamName{};
    std::vector<footballPlayer> teamPlayers{};
    int points{};

    int  findKeeperSkill()
    {
        int keeperSkill = 0; // assignment - constant time O(1)

        // Comparison O(1), runs once per player
        // therefore number of times it is executed grows as team size grows
        // also the comparison does not stop once we've found the keeper

        for (std::size_t i = 0; i < teamPlayers.size(); i++)
        {
            if (teamPlayers[i].position == Positions::goalkeeper)
            {
                keeperSkill = teamPlayers[i].skillsLevel; // assignment - constant time O(1)
            }
        }

        return keeperSkill; // Return statement - (O1)
    }
};

// findkeeperSkill() -> O(n) where n is the number of players in teamPlayers

class footballMatch
{
public:
    int forwardAttacking(footballTeam& attacker, footballTeam& defender)
    {
        int keeperSkill = defender.findKeeperSkill(); //  O(n)
        int goalsCounter = 0; // Assignment -  O(1)

        // O(n) - Loop runs for n attackers in teamPlayers
        for (std::size_t i = 0; i < attacker.teamPlayers.size(); i++)
        {
            attacker.teamPlayers[i].matchesPlayed++; // Increment - O(1)

            if (attacker.teamPlayers[i].position == Positions::forward) // Comparison - O(1)
            {
                if (attacker.teamPlayers[i].skillsLevel >= 30) // Comparison -  O(1)
                {
                    goalsCounter += 2; // increment -  O(1)
                    attacker.teamPlayers[i].goalsScored += 2; // increment -     O(1)
                }
                else if (keeperSkill < attacker.teamPlayers[i].skillsLevel) // Comparison -  O(1)
                {
                    goalsCounter += 1; // increment - O(1)
                    attacker.teamPlayers[i].goalsScored += 1; // increment -  O(1)
                }
            }
        }

        return goalsCounter; //  return statement - constant O(1)
    };

    // forwardAttacking() -> O(n) where n is the num of attackers in teamPLayers (if teams have same size)

    void playMatch(footballTeam& teamA, footballTeam& teamB, referee& ref)
    {
        int teamAGoals = forwardAttacking(teamA, teamB); // forwardAttacking is O(n)
        int teamBGoals = forwardAttacking(teamB, teamA); // forwardAttacking is O(n)

        if (teamAGoals > teamBGoals) //  O(1)
        {
            teamA.points += 3; // O(1)
        }
        else if (teamBGoals > teamAGoals) //  O(1)
        {
            teamB.points += 3; // O(1)
        }
        else if (teamAGoals == teamBGoals) // O(1)
        {
            teamA.points += 1; //  O(1)
            teamB.points += 1; // O(1)
        }

        ref.refereeJoinMatch(); // function call which increases a variable - Constant O(1)
    }
};

// playMatch() = O(n)

bool compareTeamPoints(const footballTeam& teamA, const footballTeam& teamB)
{
    return teamA.points > teamB.points; // O(1)
}

// compareTeamPoints() = Constant O(1)

void printStandings(const std::vector<footballTeam>& allTeams)
{
    std::cout << "------ Standings ------- \n"; // O(1)

    for (std::size_t i = 0; i < allTeams.size(); i++) // O(n) where n is the size of allTeams
    {
        std::cout << allTeams[i].teamName << std::endl; // O(1)
        std::cout << allTeams[i].points << std::endl; // O(1)
    }
}

// printStandings() = O(n) where n is the size of allTeams

void printBestScorers(const std::vector<footballTeam>& allTeams)
{
    int bestGoals = 0; // O(1)

    // n = number of teams
    // m = number of players per team 
    // Nested loops: O(n * m)

    for (std::size_t i = 0; i < allTeams.size(); i++)
    {
        for (std::size_t j = 0; j < allTeams[i].teamPlayers.size(); j++)
        {
            if (allTeams[i].teamPlayers[j].goalsScored > bestGoals) // O(1)
            {
                bestGoals = allTeams[i].teamPlayers[j].goalsScored; //  O(1)
            }
        }
    }

    std::cout << "---------- Best Scorers: ---------" << std::endl; //  O(1)

    if (bestGoals > 0) //  O(1)
    {
        // Second time through the loop: O(n*m)

        for (std::size_t i = 0; i < allTeams.size(); i++)
        {
            for (std::size_t j = 0; j < allTeams[i].teamPlayers.size(); j++)
            {
                if (allTeams[i].teamPlayers[j].goalsScored == bestGoals) // O(1)
                {
                    std::cout << allTeams[i].teamPlayers[j].playerName << '\n'; // O(1)
                    std::cout << allTeams[i].teamPlayers[j].goalsScored << '\n'; //  O(1)
                }
            }
        }
    }
    else // O(1)
    {
        std::cout << "No goals have been scored yet..." << std::endl; // O(1)
    }
}

// printBestScorers() = O(nm) where n is number of teams and m is the num of players in each team

int main()
{
    footballTeam snake = { "Team Snake" };
    footballTeam ocelot = { "Team Ocelot" };
    footballTeam cobraUnit = { "Team Cobra Unit" };
    footballTeam foxHound = { "Team FoxHound" };

    footballPlayer nakedSnake = { "Naked Snake", 15, snake.teamName, Positions::forward };
    snake.teamPlayers.push_back(nakedSnake);

    footballPlayer solidSnake = { "Solid Snake", 22, snake.teamName, Positions::goalkeeper };
    snake.teamPlayers.push_back(solidSnake);

    footballPlayer venomSnake = { "Venom Snake", 45, snake.teamName, Positions::forward };
    snake.teamPlayers.push_back(venomSnake);

    footballPlayer youngOcelot = { "Young Ocelot", 26, ocelot.teamName, Positions::forward };
    ocelot.teamPlayers.push_back(youngOcelot);

    footballPlayer revolverOcelot = { "Revolver Ocelot", 29, ocelot.teamName, Positions::goalkeeper };
    ocelot.teamPlayers.push_back(revolverOcelot);

    footballPlayer liquidOcelot = { "Liquid Ocelot", 35, ocelot.teamName, Positions::forward };
    ocelot.teamPlayers.push_back(liquidOcelot);

    footballPlayer thePain = { "The Pain", 22, cobraUnit.teamName, Positions::forward };
    cobraUnit.teamPlayers.push_back(thePain);

    footballPlayer theSorrow = { "The Sorrow", 19, cobraUnit.teamName, Positions::goalkeeper };
    cobraUnit.teamPlayers.push_back(theSorrow);

    footballPlayer theFear = { "The Fear", 33 , cobraUnit.teamName, Positions::forward };
    cobraUnit.teamPlayers.push_back(theFear);

    footballPlayer psychoMantis = { "Psycho Mantis", 37 , foxHound.teamName, Positions::forward };
    foxHound.teamPlayers.push_back(psychoMantis);

    footballPlayer sniperWolf = { "Sniper Wolf", 29 , foxHound.teamName, Positions::forward };
    foxHound.teamPlayers.push_back(sniperWolf);

    footballPlayer liquidSnake = { "Liquid Snake", 33, foxHound.teamName, Positions::goalkeeper };
    foxHound.teamPlayers.push_back(liquidSnake);

    referee majorZero;
    majorZero.name = "Major Zero";

    std::vector <footballTeam> allTeams;
    allTeams.push_back(snake);
    allTeams.push_back(ocelot);
    allTeams.push_back(cobraUnit);
    allTeams.push_back(foxHound);

    footballMatch newMatch;

    // Nested loops together = O(n ^2) where n is num of teams
    for (std::size_t i = 0; i < allTeams.size(); i++) // O(n)
    {
        for (std::size_t j = i + 1; j < allTeams.size(); j++)
        {
            printStandings(allTeams);                                // O(n)
            printBestScorers(allTeams);                              // O(n * m) where m is num of players per team
            newMatch.playMatch(allTeams[i], allTeams[j], majorZero); // O(m)
            std::cout << "Starting the match! " << std::endl;         //  O(1)
            std::cout << std::endl;                                   //  O(1)
        }
    }

    // Match loop overall:
    // O(n^2) * O(n * m)
    // = O(n^3 * m)

    std::sort(allTeams.begin(), allTeams.end(), compareTeamPoints); // O(n log n)

    printStandings(allTeams); // O(n)
    printBestScorers(allTeams); // O(nm)

    std::cout << "Major Zero has joined " << majorZero.joinedMatches << " matches. \n"; // O(1)

    return 0;
}

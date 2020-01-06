#include <iostream>
#include <iomanip>

long int inventory;
long int ground;
int totalTime;
int numCycles;
int numLoads;

const int timeToSetup = 3;
const int timeToDupe = 1;
const long int targetValue = 2147484000;
const int startingValue = 9;

// Takes 3 seconds
void setup()
{
    totalTime += 3;
    inventory += ground;
    ground = inventory;
    inventory = 0;
}

// Takes 1 second
void dupe()
{
    totalTime += 1;
    inventory += ground;
}

int main()
{
    std::cout << "Dupes |      Final |  Time | Items/sec | Loops | Loads" << std::endl;

    for(int numDupes = 1; numDupes < 100; numDupes++)
    {
        inventory = 0;
        ground = startingValue;
        totalTime = 0;
        numCycles = 0;
        numLoads = 0;

        // Number of dupes between setups
        while(inventory < targetValue)
        {
            numCycles++;
            setup();
            numLoads++;
            if(ground > targetValue)
            {
                inventory = ground;
                ground = 0;
                break;
            }

            for(int i = 0; i < numDupes; i++)
            {
                dupe();
                numLoads++;
                if(inventory > targetValue)
                {
                    break;
                }
            }
        }

        std::cout << std::setw(5) << std::setfill(' ') << numDupes << " | ";
        std::cout << std::setw(10) << std::setfill(' ') << inventory << " | ";
        std::cout << std::setw(5) << std::setfill(' ') << totalTime << " | ";
        std::cout << std::setw(9) << std::setfill(' ') << inventory / totalTime << " | "; 
        std::cout << std::setw(5) << std::setfill(' ') << numCycles << " | ";
        std::cout << std::setw(5) << std::setfill(' ') << numLoads << std::endl;
    }

    return 0;
}
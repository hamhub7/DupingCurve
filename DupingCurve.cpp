#include <iostream>
#include <iomanip>
#include <string>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

long int inventory;
long int ground;
int totalTime;
int numCycles;
int numLoads;

int timeToSetup = 3;
int timeToDupe = 1;
long long int targetValue = 2147484000;
int startingValue = 9;

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
    std::cout << "How long do you take, on average, to do a setup? (Pick items up off floor, drop inventory, QS/QL)" << std::endl;
    std::cin >> timeToSetup;
    std::cout << "How long do you take, on average, to do a dupe? (Pick items up off floor, QS/QL)" << std::endl;
    std::cin >> timeToDupe;
    std::cout << "What is the target number of items you want to have at the end of the dupe sequence?" << std::endl;
    std::cin >> targetValue;
    std::cout << "How many items are you starting with on the ground at the beginning?" << std::endl;
    std::cin >> startingValue;


    std::cout << "Dupes b/w Setup |      Final |  Time | Items/sec | Loops | Loads" << std::endl;

    const int numLoops = 100;
    std::vector<double> x(numLoops), y(numLoops);
    for(int numDupes = 1; numDupes < numLoops; numDupes++)
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

        x.at(numDupes) = numDupes;
        y.at(numDupes) = totalTime;

        std::cout << std::setw(15) << std::setfill(' ') << numDupes << " | ";
        std::cout << std::setw(10) << std::setfill(' ') << inventory << " | ";
        std::cout << std::setw(5) << std::setfill(' ') << totalTime << " | ";
        std::cout << std::setw(9) << std::setfill(' ') << inventory / totalTime << " | "; 
        std::cout << std::setw(5) << std::setfill(' ') << numCycles << " | ";
        std::cout << std::setw(5) << std::setfill(' ') << numLoads << std::endl;
    }

    plt::figure_size(1200, 700);
    plt::plot(x, y);
    plt::xlim(1, numLoops - 1);
    plt::title("Time vs Number of Dupes");
    plt::save("graph.png"); 

    return 0;
}
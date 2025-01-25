/**
 * @file life_game.cpp
 *
 * @description
 * This program simulates the Conway's Game of Life.
 * It reads a initial game configuration from a input file and
 * keeps updating it, if the user so whishes.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03, updated 2024-05-31
 *
 * @remark On 2015-09-19 changed the way stability is verified.
 * In the previous version we just looked back one configuration and compare it
 * with the current configuration.
 * Now, the stability may span more than one configuration. Because of that we
 * need to keep track of all configurations and check whether the current
 * configuration has already been generated.
 * If this is the case, the game has reached stability and must stop.
 */

#include "life.h"
#include <cstdlib>  // EXIT_SUCCESS
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) 
{
    life::LifeCfg jgoo;
    std::string input;
    std::string ini;

    if(argc == 1){ std::cout << "No .ini file, try -h for more information.\n"; exit(0);}
    std::vector<std::string> fancyargy{};
    for(int i=1; i<argc; ++i)
    {
        fancyargy.push_back(argv[i]);
    }
    for(auto&arg : fancyargy)
    {
        if(arg == "-h" || arg == "-help" || arg == "--help"){jgoo.givehelp(); exit(0);}
        else if(arg.substr(arg.size()-4, 4) == ".ini")
        {
            ini = arg;  
        }
    }
    

    jgoo.readini(ini);
    jgoo.start(jgoo.readfrom);
    std::chrono::milliseconds timespan(1000/jgoo.fps);
    // jgoo.readini(argv[1]);
    // jgoo.start(argv[2]); // NOT SURE YET HOW THIS IS GONNA WORK BUT SOMEHOW FOR SURE
    while (!jgoo.is_over())
    {
        jgoo.print();
        jgoo.update();
        std::this_thread::sleep_for(timespan);
    }



    return EXIT_SUCCESS; 
}


//! This class implements a life board in the Conway's Game of Life.
/*!
 * @file life.h
 *
 * @details Class Life, to simulate the Conway's Game of Life.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 * @update 2019, April 2nd.
 * @version     v1.1
 */

#ifndef _LIFE_H_
#define _LIFE_H_

#include <vector>
using std::vector;
#include <cstdint>

#include "../lib/lodepng.h"
#include "../lib/canvas.hpp"
#include "../lib/common.hpp"

#include <unordered_map>
#include "../lib/hate.h"

#include <cassert>
#include <cstring>  // std::memcpy().
#include <iostream>
#include <set>
#include <sstream>  // std::ostringstream
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

#include "life.h"

namespace life {

/// A life configuration.


class LifeCfg {

   public:
    std::string currentconfig;

    std::vector<std::pair<int, int>> livecoords;
    
    Canvas* nossatela;
    size_t cols=10;
    size_t rows=10;
    int born=3;
    int min=2;
    int max=3;
    int limitedetelas{};
    bool generateimage{};
    bool sphere{}; // name?
    bool extinct{};
    bool limitado{};
    std::string runningopt = "B3/S23";
    std::unordered_map<std::string, int> pastlives;
    int geracaos = 1;
    char livesymbol = '*';

    std::string readfrom;
    Color Background = BLACK;
    Color LiveColor = GREEN;
    // USABLE COLORS
    /*
        { "black", BLACK },
        { "white", WHITE },
        { "dark_green", DARK_GREEN },
        { "red", RED },
        { "green", GREEN },
        { "blue", BLUE },
        { "crimson", CRIMSON },
        { "light_blue", LIGHT_BLUE },
        { "light_grey", LIGHT_GREY },
        { "deep_sky_blue", DEEP_SKY_BLUE },
        { "dodger_blue", DODGER_BLUE },
        { "steel_blue", STEEL_BLUE },
        { "yellow", YELLOW },
        { "light_yellow", LIGHT_YELLOW },
        { "purple", PURPLE }
    */

    int roblox = 10;
    int fps = 2;
    std::string outputfolder{};

    LifeCfg();  // lines, columns
    ~LifeCfg(){ delete nossatela; };
    /* void set_alive(const std::vector<Location2>&);
    void update(void);
    std::string to_string(void) const;
    bool operator==(const LifeCfg&) const;
    LifeCfg& operator=(const LifeCfg& _rhs);
    bool extinct(void) const;
    size_type rows(void) const;
    size_type cols(void) const; */

    std::unordered_map<std::string, std::string> configuracaoses;
    /// @brief Sends a helping message to the user.
    void givehelp()
    {
        const char * helping = R"(
        ****************************************************************
        Welcome to Conway’s game of Life.
        To properly run the game, do this:
        ./gameoflife <.ini>
        Where the .ini is the path to the file containing the desired configurations
        ****************************************************************
        )";
        std::cout << helping << '\n';
    }
    /// @brief Begins the simulation.
    /// @param filename Starting position of the simulation. 
    void start(std::string filename)
    {
        std::ifstream arq{filename};
        if(!arq.is_open())
        {
            std::cerr << "Initial position not found, try checking the path inside the .ini file.\n";
            exit(0);
        }
        else
        {

            std::string linha{};
            std::getline(arq, linha);
            std::vector<std::string> dimensions = hate::split(linha);
            if(dimensions.size() < 2){ std::cerr << "Invalid Input File.\n"; exit(0); }
            try
            {
            cols = stoi(dimensions[1]);
            rows = stoi(dimensions[0]);
            }
            catch(std::invalid_argument){ std::cerr << "Invalid Input File.\n"; exit(0);}
            
            std::getline(arq, linha);
            livesymbol = linha[0];

            int i=0;
            while (std::getline(arq, linha))
            {
                int j=0;
                for(char caractere : linha)
                {
                    if(caractere == livesymbol)
                    {
                        livecoords.push_back({j, i});
                    }
                    j++;
                }
                i++;
            }
            
        }
        nossatela = new Canvas(cols, rows, roblox);
        
        nossatela->clear(Background);
    }

    /// @brief Reads a .ini to set configurations
    /// @param filename Path to .ini
    void readini(std::string filename)
    {
        std::ifstream arq{filename};
        if(!arq.is_open())
        {
            std::cout << "Configuration file not found.\n";
            exit(0);
        }
        else
        {
            std::string linha{};
            while (std::getline(arq, linha))
            {
                std::vector<std::string> coisas = hate::split(linha);
                if(coisas.size() >= 3)
                {
                    if(coisas[1] == "=")
                    {
                        configuracaoses[coisas[0]] = coisas[2];
                    }
                }
            }
            
        }

        for(auto& a : configuracaoses)
        {
            if(a.first == "max_gen")
            {
                try{ limitedetelas = stoi(a.second); if(limitedetelas > 0){ limitado = true;}} 
                catch(std::invalid_argument){std::cout << "Invalid argument for limit, running as default.\n"; };
            }
            if(a.first == "sphere")
            {
                sphere = (hate::strtolower(a.second) == "true"); 
            }
            if(a.first == "born")
            {
                try{ born = stoi(a.second); } 
                catch(std::invalid_argument){std::cout << "Invalid argument for born configuration, running as default.\n"; };
            }
            if(a.first == "min_to_survive")
            {
                try{ min = stoi(a.second); } 
                catch(std::invalid_argument){std::cout << "Invalid argument for minimal surviving configuration, running as default.\n"; };
            }
            if(a.first == "max_to_survive")
            {
                try{ max = stoi(a.second); } 
                catch(std::invalid_argument){std::cout << "Invalid argument for  configuration, running as default.\n"; };
        
            }
            if(a.first == "bkg")
            {
                Background = color_pallet[hate::strtolower(a.second)];
            }
            if(a.first == "alive")
            {
                LiveColor = color_pallet[hate::strtolower(a.second)];
            }
            if(a.first == "generate_image")
            {
                generateimage = (hate::strtolower(a.second) == "true");
            }
            if(a.first == "input_cfg")
            {
                readfrom = a.second;
            }
            if(a.first == "block_size")
            {
                try{ roblox = stoi(a.second); } 
                catch(std::invalid_argument){std::cout << "Invalid argument for blocksize, running as default.\n"; };
            }
            if(a.first == "path")
            {
                outputfolder = a.second;
            }
            if(a.first == "fps")
            {
                try{ fps = stoi(a.second); } 
                catch(std::invalid_argument){std::cout << "Invalid argument for frames per second, running as default.\n"; };

            }
        }
        runningopt = "B" + born;
        runningopt += "/S";
        runningopt += min;
        runningopt += max;
    }
    /// @brief Passes configurations.
    void update()
    {
        if(livecoords.size() == 0)
        {
            std::cout << "THE END OF SIMULATION, EVERY CELL DIED.\n BAD ENDING\n";
            // acabar com tudo
            exit(0);
        }
        std::string config{};
        std::sort(livecoords.begin(), livecoords.end(), [](std::pair<int, int> a, std::pair<int, int> b){if(a.first < b.first || (a.first == b.first && a.second < b.second)){return true;} return false;});
        // ordem lexicográfica de pares ordenados :p
        for(std::pair<int, int> negocio : livecoords)
        {
            config +=  negocio.first + "x";
            config +=  negocio.second + "y";
        }
        // (1,2), (10,11)
        // [ 1x2y10x11y ]
        if(pastlives.find(config) != pastlives.end())
        {
            std::cout << "REACHED STABILITY AFTER " << geracaos << " GENERATIONS. AN EQUAL CONFIGURATION WAS SEEN AT GENERATION " << pastlives[config] << ".\n";
            // pensar em como acabar o programa
            exit(0);
        }
        else
        {
            pastlives[config] = geracaos;
        }
        geracaos++;
        if(limitado && geracaos > limitedetelas)
        {
            std::cout << "THE END OF SIMULATION, GENERATION LIMIT REACHED.\n";
        }

        gettonextconfig();




    }

    /// @return A pair representing the supposed position in the canvas.
    std::pair<int, int> spheric(std::pair<int, int> a) 
    {
        
        return std::make_pair( (a.first + cols)%cols, (a.second + rows)%rows);
    }

    /// @brief counts how many neighbors a coordinate has in the current state.
    /// @param coord the coordinate to be checked.
    /// @return the amount of live neighbors a coordinate has.
    int neighbors(std::pair<int, int> coord)
    {
        int count{};
        for(int i = coord.second-1; i <= coord.second+1; ++i)
            {
                for(int j= coord.first-1; j<=coord.first+1; j++)
                {
                    if(!sphere)
                    {
                        if(i<0 || j<0){ continue; }
                        else if(i>=rows || j>=cols){ continue; }
                    }

                    if((j==coord.first && i==coord.second)){continue;}
                    
                    
                    if(std::find(livecoords.begin(), livecoords.end(), spheric(std::make_pair(j, i))) != livecoords.end())
                    {
                        count++;
                    }
                }
            }
        return count;
    }

    /// @brief checks whether a coordinate is supposed to stay alive in the next configuration.
    /// @param coordinate the coordinate to be checked.
    /// @return returns a boolean representing if a coordinate is supposed to stay alive in the next configuration. 
    bool checkalive(std::pair<int, int> coordinate)
    {
        
        int neigh = neighbors(coordinate);
        if(std::find(livecoords.begin(), livecoords.end(), coordinate) != livecoords.end()) // VIVO
        {
           if(neigh>=min && neigh<=max)
           {
            return true;
           } 
           else
           {
            return false;
           }
        }
        else // MORTO   
        {                                  
            if(neigh == born)
            {
             return true;
            }
            else
            {
             return false;
            }
        }

    }
    /// @brief checks whether the animation is over.
    /// @return a boolean representing if the animation is over.
    bool is_over()
    {
        if(extinct || (limitado&&(geracaos > limitedetelas))){return true;}
        return false;
    }

    /// @brief Updates the livecoords vector.
    void gettonextconfig()
    {
        std::set<std::pair<int, int>> checklist{};

        for(auto& a : livecoords)
        {
            for(int i = a.second-1; i <= a.second+1; ++i)
            {
                for(int j= a.first-1; j<=a.first+1; j++)
                {
                    if(!sphere)
                    {
                        if(i<0 || j<0){ continue; }
                        else if(j>=cols || i>=rows){ continue; }
                    }
                    checklist.insert(spheric({j, i}));
                }
            }
        }
        
        std::set<std::pair<int, int>> checked{};
        
        for(auto& coordinate : checklist)
        {
            if(checkalive(coordinate))
            {
                checked.insert(coordinate);
            }
        }

        livecoords.clear();
        for(std::pair<int, int> par : checked)
        {
            livecoords.push_back(par);
        }

    }
    /// @brief Prints the image
    void print()
    {   
        std::cout << "****************************************************************\nWelcome to Conway’s game of Life.\nRunning a simulation on a grid of size " << rows << " by " << cols << " in which\neach cell can either be occupied by an organism or not.\nThe occupied cells change from generation to generation\naccording to the number of neighboring cells which are alive.\n****************************************************************\n";
        for(int i=0; i<rows; ++i)
        {
            for(int j=0; j<cols; ++j)
            {
                if(std::find(livecoords.begin(), livecoords.end(), std::make_pair(j, i)) != livecoords.end())
                {
                    std::cout << "•";
                    nossatela->pixel(j, i, LiveColor);
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << '\n';
        }   
        if(generateimage)
        {

            std::string archnemesis = outputfolder + "/generation" + std::to_string(geracaos) + ".png";
            // std::cout << nossatela->pixels() << '\n';
            
            encode_png(archnemesis, nossatela->pixels(), nossatela->width(), nossatela->height());
            nossatela->clear(Background);
        }                 

    }
/// @brief Saves a canvas as a PNG
/// @param filename output filename.
/// @param image canvas' pixels.
void encode_png(std::string filename, const unsigned char* image, unsigned width, unsigned height) {
  // Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  // if there's an error, display it
  if (error != 0U) {
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << '\n';
  }
}

};










}  // namespace life

#endif

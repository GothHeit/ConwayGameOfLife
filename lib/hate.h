/*!
 * @file hate.h
 *
 * @details Library file, some useful functions.
 *
 * @author	Heitor Andrade Tavares, <heitorosvaldo@gmail.com>
 * @date	2025
 * @version v8
 */
#ifndef HATE_H
#define HATE_H

#include <vector>
#include <string>

/*
    Hate/Heit
    Heitor's library.
    KAFKA
*/
namespace hate 
{
    std::vector<std::string> split(std::string input, std::string delimiters="; \t");
    std::string strtolower(std::string orig);
}


#endif

#ifndef COMMON_HPP
#define COMMON_HPP

#include <array>
#include <cstring>  // memset, memcpy
#include <iostream>
#include <map>

namespace life {
/// Represents a Color as a RGB entity.
struct Color {
  //=== Alias
  using color_t = unsigned char;  //!< Type of a color channel.
  /// Identifies each color channel.
  enum channel_e : color_t 
  {
    R = 0,  //!< Red channel.
    G = 1,  //!< Green channel.
    B = 2   //!< Blue channel
  };

  //=== Members
  std::array<color_t, 3> channels{ 0, 0, 0 };  //!< Stores each of the color channels, R, G, and B.
  //=== Methods
  /// Creates a color.
  Color(color_t r = 0, color_t g = 0, color_t b = 0) : channels{ r, g, b } { /*empty*/ }
  /// Copy constructor.
  Color(const Color& clone) { channels = clone.channels; }
  /// Assignment operator.
  Color& operator=(const Color& rhs) {
    if (&rhs != this) {
      channels = rhs.channels;
    }
    return *this;
  }
  /// Comparison operator.
  bool operator==(const Color& rhs) {
    // TODO
    return false;  // this a stub, replace it.
  }
  /// Prints out a string representation of a color to an output stream.
  friend std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << "(" << (int)c.channels[0] << "," << (int)c.channels[1] << "," << (int)c.channels[2]
       << ")";
    return os;
  }
};

// A basic color pallete.
static const Color BLACK = Color{ 0, 0, 0 };               //!< Black.
static const Color WHITE = Color{ 255, 255, 255 };         //!< White.
static const Color DARK_GREEN = Color{ 0, 100, 0 };        //!< Dark green.
static const Color GREEN = Color{ 0, 250, 0 };             //!< Green.
static const Color RED = Color{ 255, 0, 0 };               //!< Red.
static const Color BLUE = Color{ 0, 0, 255 };              //!< Blue.
static const Color CRIMSON = Color{ 220, 20, 60 };         //!< Crimson (kind of red).
static const Color LIGHT_BLUE = Color{ 135, 206, 250 };    //!< Light blue.
static const Color LIGHT_GREY = Color{ 210, 210, 210 };    //!< Light blue.
static const Color DEEP_SKY_BLUE = Color{ 0, 191, 255 };   //!< Deep blue.
static const Color DODGER_BLUE = Color{ 30, 144, 255 };    //!< Another bluish color.
static const Color STEEL_BLUE = Color{ 70, 130, 180 };     //!< Yet another bluish color.
static const Color YELLOW = Color{ 255, 255, 0 };          //!< Yellow.
static const Color LIGHT_YELLOW = Color{ 255, 255, 153 };  //!< Light yellow.
static const Color PURPLE = Color{ 128, 0, 128 }; //!< Purple.

static const Color PINK = Color{ 244, 181, 235 }; //!< Pink.

/// A color palette for later use.
static std::map<std::string, Color> color_pallet{ { "black", BLACK },
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
                                                  { "purple", PURPLE },
                                                  { "pink", PINK}
                                                   };

}  // namespace life

#endif  // COMMON_H

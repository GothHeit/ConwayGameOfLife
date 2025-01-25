/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "../src/life.h"





namespace life {

/// @brief Takes coordinates and returns it's offset in the pixels vector;
int Canvas::offset (coord_t x, coord_t y) const{   
    int a{};


    a = ((y*m_block_size)* (m_width * image_depth)) + (x * (m_block_size * image_depth));
    
    return a;
}

/*!
 * Deep copy of the canvas.
 * @param clone The object we are copying from.
 */
Canvas::Canvas(const Canvas& clone) 
{
    this->m_height = clone.m_height;
    this->m_width = clone.m_width;
    this->m_block_size = clone.m_block_size;
    this->m_pixels = clone.m_pixels;
}

/*!
 * @param source The object we are copying information from.
 * @return A reference to the `this` object.
 */
Canvas& Canvas::operator=(const Canvas& source) 
{
    this->m_height = source.m_height;
    this->m_width = source.m_width;
    this->m_block_size = source.m_block_size;
    this->m_pixels = source.m_pixels;
    return *this;
}

// [ 100, 100, 100, 255, 100, 100, 100, 255]

//image_depth = 4;
/// Assigns a black color to the whole image.
void Canvas::clear(const Color &color) 
{
    for(int i=0; i<m_width; ++i)
    {
        for(int j=0; j<m_height; ++j)
        {
            pixel(i, j, color);
        }
    }
}

/*!
 * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
 * @param x The (virtual) X coordinate of the pixel we want to know the color of.
 * @param x The (virtual) Y coordinate of the pixel we want to know the color of.
 * @return The pixel color.
 */
Color Canvas::pixel(coord_t x, coord_t y) const {
    int difference = offset(x,y);
    return {m_pixels[difference], m_pixels[difference+1], m_pixels[difference+2]};
}

/*!
 * Draw a pixel on the virtual image at the requested coordinate.
 *
 * @note Nothing is done if the  pixel coordinate is located outside the canvas.
 * @param x The (virtual) X coordinate of the pixel we want to know the color of.
 * @param x The (virtual) Y coordinate of the pixel we want to know the color of.
 * @param c The color.
 */
void Canvas::pixel(coord_t x, coord_t y, const Color& c)
{
    if( (x >= m_width/m_block_size) || (x<0) || (y >= (m_height/m_block_size)) || (y<0) ) {return;}
    
    for(int i=0; i<m_block_size; ++i)
    {
        for(int j=0; j<m_block_size; ++j)
        {
            Canvas::m_pixels[offset( (x), (y) ) + j*image_depth + i*image_depth*m_width ] = c.channels[c.R];
            Canvas::m_pixels[offset( (x), (y) ) + j*image_depth + i*image_depth*m_width +1] = c.channels[c.G];
            Canvas::m_pixels[offset( (x), (y) ) + j*image_depth + i*image_depth*m_width +2] = c.channels[c.B];
            Canvas::m_pixels[offset( (x), (y) ) + j*image_depth + i*image_depth*m_width +3] = 255;
        }
        
    }
    


    
}



}  // namespace life
//================================[ canvas.cpp ]================================//

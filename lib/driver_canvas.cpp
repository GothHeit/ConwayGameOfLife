#include <fstream>
#include <iostream>
#include <vector>

#include "canvas.hpp"
#include "lodepng.h"

using namespace life;

/// Saves an image as a **ascii** PPM file.
bool save_ppm3(const unsigned char* data,
               size_t w,
               size_t h,
               size_t d,
               const std::string& file_name) {
  std::ofstream ofs_file(file_name, std::ios::out);
  if (not ofs_file.is_open()) 
  {
    return false;
  }

  ofs_file << "P3\n";
  ofs_file << w << " " << h << "\n";
  ofs_file << "255\n";
  // [ 100, 100, 100, 255, 100, 100, 100, 255]
  for(int i=0; i<(w*h*d); ++i)
  {
    if(i%d <= 2)
    {
      ofs_file << int(data[i]) << " ";
    }
      if(((i+1)%d) == 0) { ofs_file << " "; }
      if((i+1) % (d*w) == 0){ ofs_file << "\n";}
  }

  // TODO: Complete a geração do arquivo PPM!!

  ofs_file.close();

  return true;  // stub
}

// Example 1
// Encode from raw pixels to disk with a single function call
// The image argument has width * height RGBA pixels or width * height * 4 bytes
void encode_png(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
  // Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  // if there's an error, display it
  if (error != 0U) {
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << '\n';
  }
}

void paint(life::Canvas &imagem, int x, int y, Color &ChosenColor, int distX=1, int distY=1){
    for(int i=x; i<(x+distX); ++i)
    {
      for(int j=y; j<(y+distY); ++j)
      {
        imagem.pixel(i, j, ChosenColor);
      }  
    }


}


// [ 100, 0, 100, 255, 100]
char* cadapixel(const char* image, int height, int width, int depth, int blocksize)
{
  long unsigned int imagerealsize = width*height*depth;
  char* re = new char[width*height*depth/(blocksize*blocksize)];
  int contador{};
  
  for(int i=0; i<imagerealsize; i += depth)
  {
    re[contador++] = image[i];
    re[contador++] = image[i+1];    
    re[contador++] = image[i+2];
  }

  return re;
}

// a*x^2 + b*x + c = 0
void  imprimirparabola(life::Canvas &image, int a, int b, int c)
{
  int virtualwidth = image.width()/image.bsize();
  int virtualheight = image.height()/image.bsize();


  for(int i=0; i<virtualwidth; ++i)
  {

    float x = (i-(virtualwidth/2))*0.1;
    
    float result = ( x*x*a + x*b + c) + (virtualheight/2);
    
    float vizinho1 = ( (x-0.1)*(x-0.1)*a + (x-0.1)*b + c) + (virtualheight/2);
    float vizinho2 = ( (x+0.1)*(x+0.1)*a + (x+0.1)*b + c) + (virtualheight/2);


    if(result < 0 || result > virtualheight){ continue; }
    
    else
    {
      // if(result < vizinho1)
      // {

      //   for(int j=result; abs(j)!=abs(vizinho1);)
      //   {
      //     if(result<vizinho1){j++;}
      //     else if(result>vizinho1){j--;}
      //     image.pixel(i, j, color_pallet["white"]);
      //   }
      // }
      // if(result < vizinho2)
      // {
      //   for(int j=result; abs(j)!=abs(vizinho2);)
      //   {
      //     if(result<vizinho2){j++;}
      //     else if(result>vizinho2){j--;}
      //     image.pixel(i, j, color_pallet["white"]);
      //   }
      // }
      if(result < vizinho1)
      {
        for(int j = result; j<vizinho1; ++j)
        image.pixel(i, (virtualheight-j), color_pallet["white"]);
      }
      if(result < vizinho2)
      {
        for(int j = result; j<vizinho2; ++j)
        image.pixel(i, (virtualheight-j), color_pallet["white"]);
      }

      image.pixel(i, (virtualheight-result), color_pallet["white"]);
    }
  }
}

void eixos(life::Canvas &image)
{
  int virtualwidth = image.width()/image.bsize();
  int virtualheight = image.height()/image.bsize();

  for(int i=0; i<virtualwidth; ++i)
  {
    image.pixel(i, virtualheight/2, color_pallet["crimson"]);
  }
  for(int i=0; i<virtualheight; ++i)
  {
    image.pixel(virtualwidth/2, i, color_pallet["crimson"]);
  }
}

/*


// Saves image to filename given as argument. Warning, this overwrites the file
// without warning!
int main(int argc, char* argv[]) {
  // NOTE: this sample will overwrite the file or test.png without warning!
  const char* filename = argc > 1 ? argv[1] : "test.png";

  // Test parameters: generate some image
  constexpr size_t width = 500;
  constexpr size_t height = 500;
  constexpr short block_size = 10;

  // Criar uma imagem para desenho.
  life::Canvas image{ width, height, block_size };

  // Preenche os pixels da imagem com um tabuleiro.
  for (auto col{ 0U }; col < width; col++) {
    for (auto row{ 0U }; row < height; row++) {
      if ((row % 2) != 0U) {
        if ((col % 2) == 0U) {
          // another way to define a color.
          image.pixel(col, row, color_pallet["deep_sky_blue"]);
          // image.pixel( x,y , DEEP_SKY_BLUE );
        } else {
          image.pixel(col, row, RED);
        }
      } else if ((col % 2) == 0U) {
        image.pixel(col, row, RED);
      } else {
        image.pixel(col, row, DEEP_SKY_BLUE);
      }
    }
  }
  /// X = Column, Y = Row


  // image.pixel(0, 0, color_pallet["green"]);
  // image.clear(color_pallet["black"]);
  // // image.pixel(9, 0, color_pallet["purple"]); // middle
  // image.pixel(11, 1, color_pallet["purple"]);
  // image.pixel(7, 1, color_pallet["purple"]);
  
  // paint(image, 7, 2, color_pallet["purple"], 5, 4);
  // paint(image, 8, 6, color_pallet["purple"], 3, 1);
  // image.pixel(8, 4, color_pallet["green"]);
  // image.pixel(10, 4, color_pallet["green"]);







  image.clear(color_pallet["black"]);
  eixos(image);
  imprimirparabola(image, 1, 0, 0);

  std::cout << ">>> Gravando imagem '" << filename << "', dimensions: " << width << " x " << height
            << " (bs = " << block_size << "), please wait...\n";

  encode_png(filename, image.pixels(), image.width(), image.height());
  save_ppm3(image.pixels(), image.width(), image.height(), 4, "test.ppm");
  std::cout << "<<< done!\n";
}



*/
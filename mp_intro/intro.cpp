#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
using cs225::PNG;
using cs225::HSLAPixel;

PNG* setupOutput(unsigned w, unsigned h) {
  PNG* image = new PNG(w, h);
  return image;
}

HSLAPixel* myFavoriteColor1() {
    HSLAPixel*p = new HSLAPixel(160, 0.8, 0.5);
    return p;
}

HSLAPixel* myFavoriteColor2() {
    HSLAPixel*p = new HSLAPixel(88, 0.8, 0.5);
    return p;
}

HSLAPixel* myFavoriteColor3() {
    HSLAPixel*p = new HSLAPixel(280, 0.8, 0.5);
    return p;
}

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG* original = new PNG();
  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();

  PNG* output = setupOutput(width, height);

  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {
      HSLAPixel& currOutPixel = output->getPixel(x, y);
      currOutPixel = original->getPixel(width-1 - x, height-1 - y);
    }

  }
  output->writeToFile(outputFile);

  delete original;
  delete output;//what would happen if i change the sequence
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height); //what's the fouction of this one?
  // TODO: Part 3

HSLAPixel* myPixel1 = myFavoriteColor1();
HSLAPixel* myPixel2 = myFavoriteColor2();
HSLAPixel* myPixel3 = myFavoriteColor3();


  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width/3; x++) {
      // HSLAPixel& prev = original->getPixel(x, y);//why I need this one?
      // HSLAPixel& currOutPixel = output->getPixel(x, y);
    HSLAPixel& currOutPixel = png.getPixel(x, y);
      currOutPixel = *myPixel1;
    }
  }

  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = width/3+1; x > width/3 && x < 2*width/3; x++) {
      // HSLAPixel& prev = original->getPixel(x, y);//why I need this one?
      // HSLAPixel& currOutPixel = output->getPixel(x, y);
    HSLAPixel& currOutPixel = png.getPixel(x, y);
      currOutPixel = *myPixel2;
    }
  }

  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 2*width/3+1; x > 2*width/3 && x < width; x++) {
      // HSLAPixel& prev = original->getPixel(x, y);//why I need this one?
      // HSLAPixel& currOutPixel = output->getPixel(x, y);
    HSLAPixel& currOutPixel = png.getPixel(x, y);
      currOutPixel = *myPixel3;
    }
  }
  return png;
}

/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once //only one time

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel{
  public:
    double h; //semicolon
    double s;
    double l;
    double a;
    HSLAPixel();
    HSLAPixel(double hue,double saturation,double luminance);
    HSLAPixel(double hue,double saturation,double luminance,double alpha);
  }; //Do not forget semicolon
}

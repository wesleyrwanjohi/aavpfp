

#ifndef Interpolator_hpp
#define Interpolator_hpp

#include <stdio.h>
#include "ofMain.h"

class Smoother{
public:
    
Smoother(float SmoothingTimeMs,int SampleRate){
        //creates coeff
        a = exp(-TWO_PI / (SmoothingTimeMs * 0.001 * SampleRate));
        b = 1.0 - a;
        z = 0.0;
    }

inline float process(float input){
    //inline function copy's equation because it is used alot
    //one pole filter.
        //inputscale   previous input
    z = (input * b) + (z * a); //second z is the previous z.
    
    return z;
    }
  
private:
    float a,b,z;
    
    
};


struct SmoothValue{
    float targetValue;
    float currentValue;
    Smoother* smoother;
    
};

#endif /* Interpolator_hpp */


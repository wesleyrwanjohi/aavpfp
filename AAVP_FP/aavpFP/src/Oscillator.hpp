

#ifndef Oscillator_hpp
#define Oscillator_hpp

#include <stdio.h>
#include "ofMain.h"


class Oscillator {
public:
    void setup(float _freq, double _phase, float _amp, int _sampleRate);
    float getSample();
   float setFrequency(float _freq);
    float setAmp(float _amp);
    
    
    
private:
    int sampleRate;
    int freq;
    double phase;
    double phaseInc;
    float amplitude;
    float currentSample;
    
};





#endif /* Oscillator_hpp */

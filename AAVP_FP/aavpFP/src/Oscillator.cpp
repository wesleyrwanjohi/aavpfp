

#include "Oscillator.hpp"

void Oscillator::setup(float _freq, double _phase, float _amp, int _sampleRate){
    //setup the osc
    freq = _freq;
    phase = _phase;
    amplitude= _amp;
    sampleRate = _sampleRate;
    phaseInc = (TWO_PI * freq)/sampleRate;
    currentSample = 0;
    
}

float Oscillator:: getSample(){
    //values -1 - 1
    currentSample = sin(phase)*amplitude;
    phase += phaseInc;
    return currentSample;
    
}



float Oscillator :: setFrequency(float _freq){
    //sets the frequency returns a float
    freq = _freq;
    phaseInc = (TWO_PI * freq)/sampleRate;
    return freq;
    
}
float Oscillator::setAmp(float _amp){
    //sets the amplitude returns a float
    amplitude = _amp;
   return amplitude;
    
}


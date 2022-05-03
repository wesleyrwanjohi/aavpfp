
#ifndef envelopegen_hpp
#define envelopegen_hpp

#include <stdio.h>
#include "ofMain.h"


class envelopegen{
public:
 
envelopegen();
    
    void setAttack(float initAttack=5000,float Srate = 44100);
    void setDecay(float initDecay = 10,float Srate = 44100);
    void setSustain(float initSustain = 1.0,float Srate = 44100);
    void setRelease(float initRelease = 200,float Srate = 44100);
    void process();
    float getValue();
    void gGate(int newGate);
    
    
private:
    
    float attack,decay,sustain,release;
    float currentAmp;
    int gate;
    int state;
    float attackInc,decayInc,releaseInc;
    float sampleRate;
    
    enum states {
        //env states.
            OFF,
            ATTACK,
            DECAY,
            SUSTAIN,
            RELEASE
    };
    void calculateInc(int whichState){
        
        switch(whichState){
                
              //determins which state the env is in.
                case ATTACK:
                
                attackInc = 1/(sampleRate * (attack * 0.001));
                          
                break;
                
                case DECAY:
                decayInc = (1 - sustain)/(sampleRate  * (decay * 0.001));
                
                break;
                      
                case RELEASE:
                releaseInc = sustain/(sampleRate  * (release * 0.001));
                break;
                
                
                
        }
        
        
        
        
        
    }
};



#endif /* envelopegen_hpp */


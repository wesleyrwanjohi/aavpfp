//


#include "envelopegen.hpp"

//class that generates a custom envelope
//=======================================================================================

envelopegen::envelopegen(){

}

void envelopegen::setAttack(float initAttack,float Srate){
    
    attack = initAttack;
    sampleRate = Srate;
    //attack
    calculateInc(ATTACK);

    currentAmp = 0;

        
    state = OFF;
    gate = 0;
    
}
void envelopegen::setDecay(float initDecay,float Srate){
    
  
    decay = initDecay;
    
    sampleRate = Srate;
    //decay
    calculateInc(DECAY);
      
         
    currentAmp = 0;

        
    state = OFF;
    gate = 0;
    
}
void envelopegen::setSustain(
             float initSustain,float Srate){
    

    sustain = initSustain;
    sampleRate = Srate;
   currentAmp = 0;

        
    state = OFF;
    gate = 0;
    
}
void envelopegen::setRelease(float initRelease,float Srate){
    
    release = initRelease;
    sampleRate = Srate;
    
    //release
       calculateInc(RELEASE);
         
    currentAmp = 0;

        
    state = OFF;
    gate = 0;
    
}





void envelopegen::process(){
    switch(state){
        case OFF:
            currentAmp = 0;
           
            break;
            
            
        case ATTACK:
            currentAmp += attackInc;
            if(currentAmp >= 1.0){
                currentAmp = 1.0;
                state = DECAY;
            }
            
            break;
        case DECAY:
            currentAmp -= decayInc;
            if(currentAmp <= sustain){
                currentAmp = sustain;
                state = SUSTAIN;
            }
            
            break;
        case SUSTAIN:
            currentAmp = sustain;
            break;
        case RELEASE:
            
            currentAmp -= releaseInc;
            if(currentAmp <= 0.0){
                currentAmp = 0.0;
                state = OFF;
            }
            break;
        default:
            cout<<"this is not working"<<endl;
            
            
    }
    
    
}
 
//=======================================================================================
    
    
        
float envelopegen::getValue(){
            return currentAmp;
    //return current
        }
        
    
    void envelopegen::gGate(int newGate){
        int prevGate = gate;
        gate = newGate;
        //check if env is on or off to trigger.
        if(prevGate == 0 && gate == 1){state = ATTACK;}
        if(prevGate == 1 && gate == 0){state = RELEASE;}
        
    }



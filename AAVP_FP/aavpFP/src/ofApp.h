#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "envelopegen.hpp"
#include "Oscillator.hpp"
#include "Filterr.hpp"
#include "Interpolator.hpp"
#include "ofxMaxim.h"




class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void audioOut(float * output, int bufferSize, int nChannels);
        void exit();
        float mtof(float midiVal);
        void listen();
        void drawSinewave();
        void drawFFTWave();
        void resetCam();

        
   
    
    int sampleRate, bufferSize;

    
    Oscillator osc;
    Oscillator osc2;
    Oscillator lfoTwo;

    envelopegen* env;
    envelopegen* env2;
    
    
    Filterr* lowpass;
    Filterr* lowpass2;
   
    float filterfreq = 4000;
    float filterfreq2 = 7000;

    SmoothValue amplitude;
    SmoothValue amplitude2;
    SmoothValue frequency;
    SmoothValue frequency2;
    SmoothValue frequency3;
    SmoothValue frequency4;
    SmoothValue frequency5;
    
 
    ofxPanel gui;
    ofxIntSlider slider;
    
    
    maxiEnv Envelope;
    maxiEnv FilterEnvelope;
    maxiFilter lowPass;
    
    maxiOsc saw;
    maxiOsc square;
    maxiOsc triangle;
    maxiOsc square2;
    
    
    
    
    
    int trigger;
    int filterEnvelopetrigger;

    ofxFloatSlider attack;
    ofxFloatSlider decay;
    ofxFloatSlider sustain;
    ofxFloatSlider release;
    
    ofxFloatSlider FEattack;
    ofxFloatSlider FEdecay;
    ofxFloatSlider FEsustain;
    ofxFloatSlider FErelease;
    
    ofxFloatSlider cutoff;
    ofxFloatSlider cutoff2;
    ofxFloatSlider freqq;
    ofxFloatSlider res;
    
    ofxFloatSlider lfoamount;
    ofxFloatSlider lfofreq;
    ofxFloatSlider lfofreq2;
    ofxFloatSlider lfoAmp;
    
    enum Notes{
        //Storing the constant note values here, 48 incrementing by 1.
        C = 48,
        CSharp,
        D,
        DSharp,
        E,
        F,
        FSharp,
        G,
        };


    
    ofEasyCam cam;
    ofBoxPrimitive box; //box used as refernce for camera

    float waveform[4096];
    float pauseWaveform[4096];
    int waveIndex;

    //fft elements
    maxiFFT fft;
    double fftSize;

    //plane that draws processed sinewave
    ofPlanePrimitive plane;

    bool pause;

    //variables for color of waves
    vector<ofColor> wColours;
    vector<ofColor> fColours;
    int randColor;


        
};
 


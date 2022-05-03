
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);

    //setting up camera
    box.setPosition(0, 0, 0); //box used as reference for where camera should look
    cam.setPosition(ofVec3f(-400, 100, -500));
    cam.lookAt(box.getPosition());
   
    
    sampleRate = 44100;
    bufferSize = 512;

    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;

    pause = false;

    //initalising fft elements
    fftSize = 4096;
    fft.setup(fftSize, bufferSize, 256);

    //pushing wave colour pairs into vectors
    wColours.push_back(ofColor(31, 218, 255));
    wColours.push_back(ofColor(245, 58, 135));
    wColours.push_back(ofColor(255, 248, 59));
    wColours.push_back(ofColor(217, 79, 255));
    wColours.push_back(ofColor(41, 255, 44));
    wColours.push_back(ofColor(255, 20, 40));
    wColours.push_back(ofColor(186, 255, 10));

    fColours.push_back(ofColor(245, 58, 135));
    fColours.push_back(ofColor(217, 79, 255));
    fColours.push_back(ofColor(255, 20, 40));
    fColours.push_back(ofColor(255, 248, 59));
    fColours.push_back(ofColor(186, 255, 10));
    fColours.push_back(ofColor(41, 255, 44));
    fColours.push_back(ofColor(31, 218, 255));
    
    randColor = 0;
    //gui
    gui.setup();
    gui.add(attack.setup("attack",6000,0,6000));
    gui.add(decay.setup("decay",6000,0,6000));
    gui.add(sustain.setup("sustain",0.5,0.0,1.0));
    gui.add(release.setup("release",6000,0,6000));
    
    


    gui.add(cutoff.setup("cutoff",20000,0,20000));
    gui.add(cutoff2.setup("cutoff2",5000,0,20000));
    gui.add(res.setup("resonance",10.0,1.0,10.0));
    gui.add(freqq.setup("frequency",20000,0,20000));
    
    gui.add(lfoamount.setup("lfoamount",1.0,0.0,1.0));
    gui.add(lfofreq.setup("amplitude modulation",20.0,0.0,20.0));
    gui.add(lfofreq2.setup("lfofreq2",0.0,0.0,20.0));
    gui.add(lfoAmp.setup("lfo Amp",0.5,0.0,1.0));
    
    
    
    
    
   
    
    
    //setup the smoothed values.
    frequency.targetValue = 440;
    frequency2.targetValue = 440;
    frequency3.targetValue = 440;
    frequency4.targetValue = 440;
    frequency5.targetValue = lfofreq;
    frequency.smoother = new Smoother(20,sampleRate);
    frequency2.smoother = new Smoother(20,sampleRate);
    frequency3.smoother = new Smoother(20,sampleRate);
    frequency4.smoother = new Smoother(20,sampleRate);
    frequency5.smoother = new Smoother(20,sampleRate);
    amplitude.targetValue = 0.5;
    amplitude2.targetValue = 0.5;
    amplitude.smoother = new Smoother(20,sampleRate);
    amplitude2.smoother = new Smoother(20,sampleRate);
    
 
    
 
   
  
    
    
    //setup oscs
    osc.setup(frequency.targetValue,0,amplitude.targetValue,sampleRate);
    osc2.setup(frequency2.targetValue,0,amplitude.targetValue,sampleRate);
    lfoTwo.setup(lfofreq2, 0, lfoAmp, sampleRate);
    
    
    
    //setup envelope
   
    env = new envelopegen();
    trigger = 0;
    filterEnvelopetrigger = 0;
    
 
           
          
              
               
           
   
    
    
    //process
    
    amplitude.currentValue = amplitude.smoother -> process(amplitude.targetValue);
    frequency.currentValue = frequency.smoother -> process(frequency.targetValue);
    frequency2.currentValue = frequency2.smoother -> process(frequency2.targetValue);
    frequency3.currentValue = frequency3.smoother -> process(frequency3.targetValue);
    frequency4.currentValue = frequency4.smoother -> process(frequency4.targetValue);
    frequency5.currentValue = frequency5.smoother -> process(frequency5.targetValue);
    
   
   
    
//    for(int i = 0; i <oscNum; i++){
//        osc[i].setup(440 * ( i + 1), 0 ,(float)1 / (i+1),sampleRate);
//
//       }
//
//    for(int i = 0; i <oscNum2; i++){
//         osc2[i].setup(660 * (i + 1), 0 ,(float)1/(i+1),sampleRate);
//        }
//
    
    //Filter init
     lowpass = new Filterr(bq_type_lowpass, cutoff / sampleRate, 0.707, 0);
//    lowpass2 = new Filterr(bq_type_lowpass,cutoff/sampleRate,0.707,0);
     
    
ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
}

void ofApp::listen(){
    
    
}
void ofApp::resetCam() {


    //resets camera
    box.setPosition(0, 0, 0);
    cam.setPosition(ofVec3f(-400, 100, -500));
    cam.lookAt(box.getPosition());



}
//--------------------------------------------------------------
void ofApp::update(){
    //pass the slider values to the adsr
    Envelope.setAttack(attack);
    Envelope.setDecay(decay);
    Envelope.setSustain(sustain);
    Envelope.setRelease(release);

}

//--------------------------------------------------------------
void ofApp::draw(){
    //setting up 3D space
    ofEnableDepthTest();
    cam.begin();


    //box.drawWireframe();

    //drawing waveforms
    drawFFTWave();
    drawSinewave();
    
  
	


    cam.end();
    ofDisableDepthTest(); //disabling depth buffer so gui panel can draw to screen as a 2D image
  
    gui.draw();
	ofDrawBitmapString("Press 'r' to reset camera postition", ofGetWidth() * 12 / 20, ofGetHeight() * 1 / 20);
	ofDrawBitmapString("Press space to pause the sinewave", ofGetWidth() * 12 / 20, ofGetHeight() * 1 / 20 + 20);
	ofDrawBitmapString("Press 'a', 'w', 's', 'e', 'd', 'f', 't' or 'g'", ofGetWidth() * 12 / 20, ofGetHeight() * 1 / 20 + 40);
	ofDrawBitmapString("to trigger different oscillator outputs", ofGetWidth() * 12 / 20, ofGetHeight() * 1 / 20 + 55);
	ofDrawBitmapString("Press 'c' to change wave colours", ofGetWidth() * 12 / 20, ofGetHeight() * 1 / 20 + 75);
}

void ofApp::drawSinewave() {


    ofPushStyle();
    ofPushMatrix();



    //draws sinewave using waveform array values from sound output
    ofSetColor(wColours[randColor]);
    ofFill();
    //ofDrawLine(0, 0, 0, 0, waveform[1] * ofGetHeight() / 2, 1); //first line
    for (int i = 1; i < (ofGetWidth() - 1); ++i) {
        if (pause == false) {
            ofDrawLine(0, waveform[i] * ofGetHeight() / 2, i, 0, waveform[i + 1] * ofGetHeight() / 2, i + 1);
            pauseWaveform[i] = waveform[i];
        }
        else {
            //when paused waveform freezes to its current state
            ofDrawLine(0, pauseWaveform[i] * ofGetHeight() / 2, i, 0, pauseWaveform[i + 1] * ofGetHeight() / 2, i + 1);
        }
    }


    ofPopMatrix();
    ofPopStyle();



}

void ofApp::drawFFTWave() {

    //draws processed fft wave as a plane
    ofPushStyle();
    ofSetColor(fColours[randColor]);
    ofPushMatrix();
    ofTranslate(0, -ofGetHeight() / 3, 0);
    ofScale(ofVec3f(0.25, 0.25, 0.25));
    float xinc = ofGetWidth() / fftSize * 50;
    for (int i = 0; i < fftSize; ++i) {
        float height = fft.magnitudes[i] * 4;
        //ofDrawLine(30 + (i*xinc), ofGetHeight() - height, 0, 30, height, 0);
        plane.setPosition(250 + (i*xinc), ofGetHeight() + height, 0);
        plane.draw();
    }
    ofPopMatrix();
    ofPopStyle();

}







//--------------------------------------------------------------


void ofApp::audioOut(float * output, int bufferSize, int nChannels ) {
   //loop through the buffer
    for(int i = 0; i < bufferSize; i++){
        
        //init the oscs
        float currentSample = 0;
        
        //pass frequency.targetvalue(our smoothed frequency value which is 440 to our osc
        osc.setFrequency(frequency.targetValue);
        osc2.setFrequency(frequency2.targetValue);
        
        
        
        float slidervalue = cutoff;
    
        
        //store our oscillator's as floats
        float osc1 = osc.getSample();
        float oscc2 = osc2.getSample();
        float osc3 = saw.saw(frequency3.targetValue);
        float osc4 = square.rect(frequency4.targetValue);
      
        
        //store our lfo's as floats. Pass the lfofreq slider as the frequency of the oscillator
        float lfofrequency = triangle.triangle(lfofreq);
        float lfofrequency2 = square2.rect(18);
    
        
        
        
    
        
        
        
        // smoothing process

        amplitude.currentValue = amplitude.smoother -> process(amplitude.targetValue);
      
        //smooth the changes in frequency
        frequency.currentValue = frequency.smoother -> process(frequency.targetValue);
        frequency2.currentValue = frequency2.smoother -> process(frequency2.targetValue);
        frequency3.currentValue = frequency3.smoother -> process(frequency3.targetValue);
        frequency4.currentValue = frequency4.smoother -> process(frequency4.targetValue);
        frequency5.currentValue = frequency5.smoother -> process(frequency5.targetValue);

    
        //sum the oscillators
        float mix = osc1 + oscc2 + osc3 + osc4;
       
     //map the oscillator from (amplitude)-1 1 to frequency values which will                                                          change the range on the lfo.
        float LFO = ofMap(lfoTwo.getSample(),-1,1,cutoff,1920);
        
        //store the slider value as float
        float freqcontrol = lfofreq2;
        //set the slider value as the freqnecy of the lfo
        lfoTwo.setFrequency(freqcontrol);
        
        //set the amplitude of the lfo to 'lfoAmp' slider value
        lfoTwo.setAmp(lfoAmp);
        
        
        //set the frequency cutoff of the lowpassfilter to the LFO from above
        float filtercutoff = lowpass->setFc(LFO/sampleRate);
        //set the resonance to the 'res' slider
        lowpass->setQ(res);
        
        
        //apply the filter to the summed audio
        float Filter = lowpass->process(mix);
        
        
     
        

        
       
        //Multiply the amplitude of the summed signal by the lfo for amp modulation
        float lfo = Filter * lfofrequency;
        //store the amp mod value in a new float
        float sampleNew = lfo;
     
        //amp env
        float ampEnv = Envelope.adsr(sampleNew,trigger);

        
        
        
        //sum the the final two oscillators
       
        currentSample = ampEnv;
        
        currentSample *= 0.3;
        output[i*nChannels+0] = currentSample;
        output[i*nChannels+1] = currentSample;
        fft.process(output[i] * 5);

        //gets sound output info and stored in array used to draw waveform
        waveform[waveIndex] = output[i * nChannels];
        if (waveIndex < (ofGetWidth() - 1)) {
            ++waveIndex;
        }
        else {
            waveIndex = 0;
        }
    }
    
    
    
    
    
   
}





void ofApp::keyPressed(int key){
    switch(key){
        case 'a':

           //note on
            frequency.targetValue = mtof(C);
            frequency2.targetValue = mtof(C);
            frequency3.targetValue = mtof(C);
            frequency4.targetValue = mtof(C)+freqq;
            env->gGate(1);

            trigger = 1;
         
            
            break;
        case 'w':
            frequency.targetValue = mtof(CSharp);
            frequency2.targetValue = mtof(CSharp);
            frequency3.targetValue = mtof(CSharp);
            frequency4.targetValue = mtof(CSharp);
            trigger = 1;
          env->gGate(1);
            break;
        case 's':
            frequency.targetValue = mtof(D);
            frequency2.targetValue = mtof(D);
            frequency3.targetValue = mtof(D);
            frequency4.targetValue = mtof(D);
            trigger = 1;
            env->gGate(1);
            break;
        case 'e':
            frequency.targetValue = mtof(DSharp);
            frequency2.targetValue = mtof(DSharp);
            frequency3.targetValue = mtof(DSharp);
            frequency4.targetValue = mtof(DSharp);
            trigger = 1;
           env->gGate(1);
            break;
        case 'd':
            frequency.targetValue = mtof(E);
            frequency2.targetValue = mtof(E);
            frequency3.targetValue = mtof(E);
            frequency4.targetValue = mtof(E);
            trigger = 1;
            env->gGate(1);
            break;
        case 'f':
            frequency.targetValue = mtof(F);
            frequency2.targetValue = mtof(F);
            frequency3.targetValue = mtof(F);
            frequency4.targetValue = mtof(E);
            trigger = 1;
            env->gGate(1);
            break;
        case 't':
            frequency.targetValue = mtof(FSharp);
            frequency2.targetValue = mtof(FSharp);
            frequency3.targetValue = mtof(FSharp);
            frequency4.targetValue = mtof(FSharp);
            trigger = 1;
            env->gGate(1);
            break;
        case 'g':
            frequency.targetValue = mtof(G);
            frequency2.targetValue = mtof(G);
            frequency3.targetValue = mtof(G);
            frequency4.targetValue = mtof(G);
            trigger = 1;
            env->gGate(1);
            break;
            }
    if (key == 'c') {
        randColor = ofRandom(0, 6);
    }
    
    //resets camera position
    if (key == 'r') {
        resetCam();
    }
    //triggering waveform pausing
    if (key == ' ') {
        pause = !pause;
    }

    
         
             
}
    
    
    
    
    

void ofApp::keyReleased(int key){
   switch(key){
           
        case 'a':
           //note off
          env->gGate(0);

           trigger = 0;
           
            break;
        case 'w':
           trigger = 0;
           env->gGate(0);
        
            break;
        case 's':
           trigger = 0;
           env->gGate(0);
          
            break;
        case 'e':
           trigger = 0;
           env->gGate(0);
           
            break;
        case 'd':
           trigger = 0;
           env->gGate(0);
            break;
        case 'f':
           trigger = 0;
           env->gGate(0);
           
            break;
        case 't':
           trigger = 0;
           env->gGate(0);
           
            break;
        case 'g':
           trigger = 0;
           env->gGate(0);
        
            break;
            
            
            
            
            
            
            
    }

   
    
 
    
    
    
}

float ofApp::mtof(float midiVal){
    //takes midi value returns the frequency
    
return 440 * pow(2,(midiVal -69)/12.f);
    
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    

       
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::exit(){
    ofSoundStreamClose();
}


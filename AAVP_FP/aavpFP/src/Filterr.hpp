

#include "ofMain.h"
#ifndef Filterr_hpp
#define Filterr_hpp

enum {
    //filter type
    bq_type_lowpass = 0,
    bq_type_highpass,
    bq_type_bandpass,
    bq_type_notch,
    bq_type_peak,
    bq_type_lowshelf,
    bq_type_highshelf
};

class Filterr{
public:
    Filterr();
    Filterr(int type, double Fc, double Q, double peakGainDB);
    ~Filterr();
    void setType(int type);
    void setQ(double Q);
    float setFc(double Fc);
    void setPeakGain(double peakGainDB);
    void setBiquad(int type, double Fc, double Q, double peakGainDB);
    float process(float in);
    
protected:
    void calcBiquad(void);

    int type;
    double a0, a1, a2, b1, b2;
    double Fc, Q, peakGain;
    double z1, z2;
};

inline float Filterr::process(float in) {
    double out = in * a0 + z1;
    z1 = in * a1 + z2 - b1 * out;
    z2 = in * a2 - b2 * out;
    return out;
}

#endif // Filterr_hpp


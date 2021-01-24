#ifndef EXERCISERESULT_H
#define EXERCISERESULT_H

class ExerciseResult
{
public:
    ExerciseResult(unsigned nCorrect, unsigned nTotal, unsigned duration)
        : _nCorrect(nCorrect)
        , _nTotal(nTotal)
        , _duration(duration) {};
    float getSpeedWPM();
    float getSpeedCPM();
    float getSpeedCPS();
    float getSpeedWPS();
    float getAccuracy();
    float getFormattedAccuracy(); // Get user friendly accuracy (ex: 95.4 instead of 0.953290)
private:
    unsigned _nCorrect;
    unsigned _nTotal;
    unsigned _duration; // in seconds
};

#endif // EXERCISERESULT_H

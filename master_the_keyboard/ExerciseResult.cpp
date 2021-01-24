#include "ExerciseResult.h"
#include <cmath>

static const int CPW = 5;

float ExerciseResult::getSpeedWPM()
{
    return this->getSpeedCPS() * 60.0 / CPW;
}

float ExerciseResult::getSpeedCPM()
{
    return this->getSpeedCPS() * 60.0;
}

float ExerciseResult::getSpeedWPS()
{
    return this->getSpeedCPS() / CPW;
}

float ExerciseResult::getSpeedCPS()
{
    return static_cast<float>(_nCorrect) / static_cast<float>(_duration);
}

float ExerciseResult::getFormattedAccuracy(){
    const int decimalPlaces = 1;
    const float factor = pow(10, decimalPlaces);
    return
        static_cast<float>(static_cast<int>(this->getAccuracy() * 100 * factor))
            / factor;
}

float ExerciseResult::getAccuracy()
{
    return static_cast<float>(_nCorrect) / static_cast<float>(_nTotal);
}

#include "ExerciseResult.h"
#include <cmath>

namespace
{
const int CPW = 5;

float formatFloat (float n, unsigned short decimalPlaces = 1)
{
    const float factor = pow(10, decimalPlaces);
    return static_cast<float>(static_cast<int>(n * factor)) / factor;
}
}

float ExerciseResult::getSpeedWPM()
{
    return formatFloat(this->getSpeedCPS() * 60.0 / CPW, 1);
}

float ExerciseResult::getSpeedCPM()
{
    return formatFloat(this->getSpeedCPS() * 60.0, 1);
}

float ExerciseResult::getSpeedWPS()
{
    return formatFloat(this->getSpeedCPS() / CPW, 1);
}

float ExerciseResult::getSpeedCPS()
{
    return formatFloat(static_cast<float>(_nCorrect) / static_cast<float>(_duration), 1);
}

float ExerciseResult::getFormattedAccuracy(){
    return formatFloat(100 * this->getAccuracy(), 1);
}

float ExerciseResult::getAccuracy()
{
    return static_cast<float>(_nCorrect) / static_cast<float>(_nTotal);
}

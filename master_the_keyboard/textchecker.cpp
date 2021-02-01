#include "textchecker.h"

namespace
{
const int CPW = 5;

float formatFloat (float n, unsigned short decimalPlaces = 1)
{
    const float factor = pow(10, decimalPlaces);
    return roundf(n * factor) / factor;
}
}

QString Metrics::compareText(const QString& reference, const QString& other)
{
    QString result, modifier;

    int domainStart = 0;
    int errors = 0;
    int hits = 0;
    int length = other.length() < reference.length()
                    ? other.length()
                    : reference.length();
    int i = 0;
    while (i < length)
    {
        domainStart = i;
        if (other[i] != reference[i])
        {
            modifier = "<span style=\"color:#FF0C32;text-decoration:line-through;\">";
            do
            {
                if(++i == length) break;
            } while (other[i] != reference[i]);
            errors += i - domainStart;
        }
        else
        {
            modifier = "<span style=\"color:#0CFF32;\">";
            do
            {
                if(++i == length) break;
            } while (other[i] == reference[i]);
            hits += i - domainStart;
        }
        result.append(modifier)
              .append(reference.mid(domainStart, i - domainStart).toHtmlEscaped())
              .append("</span>");
    }
    if (length < reference.length())
    {
        result.append(reference.right(reference.length() - length).toHtmlEscaped());
    }
    this->updateAccuracy(errors, hits);
    return result;
}

int Metrics::getAccuracy()
{
    int errorPercentage =
        _numberOfErrors
                ? formatFloat(static_cast<float>(100*_numberOfErrors)/(_currentNumberOfHits+_numberOfErrors),0)
                : 0;

    int accuracy = 100-errorPercentage;
    return accuracy;
}

int Metrics::getSpeed(){
    using namespace std::chrono;

    TimePoint exerciseEndTime = high_resolution_clock::now();
    unsigned duration = duration_cast<seconds>(exerciseEndTime - _startTime).count();
    float speed =
        duration
            ? formatFloat(
                (static_cast<float>(_currentNumberOfHits) / CPW * 60.0) / static_cast<float>(duration), 0)
            :  0;

    return speed;
}

void Metrics::updateAccuracy(int errors, int hits)
{
    if(errors>_currentNumberOfErrors)
        _numberOfErrors++;

    _currentNumberOfErrors = errors;
    _currentNumberOfHits = hits;
}

void Metrics::resetMetrics()
{
    _numberOfErrors = 0;
    _currentNumberOfHits = 0;
    _currentNumberOfErrors = 0;
}

void Metrics::setStartTime()
{
    _startTime = std::chrono::high_resolution_clock::now();
}

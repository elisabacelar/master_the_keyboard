#ifndef METRICS_H
#define METRICS_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

class Metrics {
    public:
        QString getCorrectness();
        QString getSpeed();
        void updateCorrectness(int errors, int hits);
        QString compareText(const QString& reference, const QString& other);
        void resetMetrics();
        void setStartTime();
    private:
        int _numberOfErrors {0};
        int _currentNumberOfErrors {0};
        int _currentNumberOfHits {0};
        TimePoint _startTime;
};

#endif // METRICS_H

#ifndef TEXTCHECKER_H
#define TEXTCHECKER_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>

class Metrics {
    public:
        QString getCorrectness();
        void updateCorrectness(int errors, int hits);
        void setCurrentText(QString text);
        QString getCurrentText();
        int getCurrentTextLength();
        QString compareText(QString& otherString);
    private:
        int _numberOfErrors;
        int _textLength;
        int _currentNumberOfErrors;
        int _currentNumberOfHits;
        QString _text;
};

#endif // TEXTCHECKER_H

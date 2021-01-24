#ifndef TEXTCHECKER_H
#define TEXTCHECKER_H

#include <QObject>
#include <QString>

std::pair<int, QString> compareText(QString& referenceString,QString& otherString);

#endif // TEXTCHECKER_H

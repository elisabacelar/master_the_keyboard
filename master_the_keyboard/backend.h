#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>
#include <QtSql>
#include <QDebug>
#include "MarkovChain.h"
#include "textchecker.h"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString inputText READ getInputText WRITE setInputText NOTIFY \
               inputTextChanged)
    Q_PROPERTY(QString displayedText READ getDisplayedText WRITE setDisplayedText \
               NOTIFY displayedTextChanged)
    Q_PROPERTY(bool loginWindowVisibility READ isLoginWindowVisible WRITE \
               setLoginWindowVisibility NOTIFY loginWindowVisibilityChanged)
    Q_PROPERTY(QString userNameInput READ getUserName WRITE setUserName NOTIFY \
               userNameChanged)
    Q_PROPERTY(QString correctness READ getCorrectness WRITE setCorrectness NOTIFY \
               correctnessChanged)
    Q_PROPERTY(QString speed READ getSpeed WRITE setSpeed NOTIFY \
               speedChanged)

    public:
        explicit BackEnd(QObject* parent = nullptr);

        QString getSampleText();
        QString getInputText();
        void setInputText(const QString &userName);
        void handleInputChange();
        QString getDisplayedText();
        void setDisplayedText(const QString &userName);
        void setSampleText(int words);
        void setupDb(QString dbname);
        Q_INVOKABLE void resetText();
        bool isLoginWindowVisible();
        void setLoginWindowVisibility(bool visibility);
        void handleNewSession();
        void handleNewUser();
        QString getUserName();
        void setUserName(const QString &userName);
        QString getCorrectness();
        void setCorrectness(const QString &correctness);
        QString getSpeed();
        void setSpeed(const QString &speed);
        QSqlDatabase db;
    signals:
        void inputTextChanged();
        void displayedTextChanged();
        void loginWindowVisibilityChanged();
        void userNameChanged();
        void correctnessChanged();
        void speedChanged();
    private:
        MarkovChain _mChain;
        QString _inputText;
        QString _sampleText;
        QString _displayedText;
        bool _loginWindowVisibility;
        QString _userNameInput;
        QString _correctness;
        QString _speed;
        Metrics _textVerification;
        TimePoint _exerciseStartTime;
        bool _isExerciseOngoing {false};
};

#endif // BACKEND_H

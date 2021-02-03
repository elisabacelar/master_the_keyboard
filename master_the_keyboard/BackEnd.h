#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "MarkovChain.h"
#include "Metrics.h"

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
    Q_PROPERTY(int accuracy READ getAccuracy WRITE setAccuracy NOTIFY \
               accuracyChanged)
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed NOTIFY \
               speedChanged)
    Q_PROPERTY(QVariantList accuracyHistory READ getAccuracyHistory WRITE setAccuracyHistory \
               NOTIFY accuracyHistoryChanged)
    Q_PROPERTY(QVariantList speedHistory READ getSpeedHistory WRITE setSpeedHistory NOTIFY \
               speedHistoryChanged)

    public:
        explicit BackEnd(QObject* parent = nullptr);

        QString getSampleText();
        QString getInputText();
        void setInputText(const QString &userName);
        void handleInputChange();
        QString getDisplayedText();
        void setDisplayedText(const QString &userName);
        void setSampleText(int words);
        Q_INVOKABLE void resetText();
        Q_INVOKABLE QString getUserName();
        Q_INVOKABLE void setUserName(const QString &userName);
        int getAccuracy();
        void setAccuracy(const int accuracy);
        int getSpeed();
        void setSpeed(const int speed);
        QVariantList getAccuracyHistory();
        void setAccuracyHistory(const QVariantList accuracyHistory);
        QVariantList getSpeedHistory();
        void setSpeedHistory(const QVariantList speedHistory);

        bool isLoginWindowVisible();
        void setLoginWindowVisibility(bool visibility);
        void databaseInit(QString dbName);
        void createNewTable();
        void handleNewSession();
        void handleNewUser();
        Q_INVOKABLE QString signInUser(const QString &userName);
        Q_INVOKABLE QString registerUser(const QString &userName);
        Q_INVOKABLE void saveMetrics();
        void saveSpeed();
        void saveAccuracy();
        Q_INVOKABLE void getDataHistory();
        Q_INVOKABLE void clearUserData();
        Q_INVOKABLE void deleteAccount();
    signals:
        void inputTextChanged();
        void displayedTextChanged();
        void loginWindowVisibilityChanged();
        void userNameChanged();
        void accuracyChanged();
        void speedChanged();
        void accuracyHistoryChanged();
        void speedHistoryChanged();
    private:
        MarkovChain _mChain;
        QString _inputText;
        QString _sampleText;
        QString _displayedText;
        bool _loginWindowVisibility;
        QString _userNameInput {};
        QSqlDatabase _db;
        int _accuracy {0};
        int _speed {0};
        Metrics _textVerification;
        TimePoint _exerciseStartTime;
        bool _isExerciseOngoing {false};
        QVariantList _speedHistory;
        QVariantList _accuracyHistory;
};

#endif

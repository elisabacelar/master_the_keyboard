#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>
#include <QtSql>
#include <QDebug>
#include "MarkovChain.h"

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString inputText READ getInputText WRITE setInputText NOTIFY \
               inputTextChanged)
    Q_PROPERTY(QString displayedText READ getDisplayedText WRITE setDisplayedText \
               NOTIFY displayedTextChanged)


    public:
        explicit BackEnd(QObject* parent = nullptr);

        QString getSampleText();
        QString getInputText();
        Q_INVOKABLE void setInputText(const QString &userName);
        void handleInputChange();
        QString getDisplayedText();
        void setDisplayedText(const QString &userName);
        Q_INVOKABLE void setSampleText(int words);
        void setupDb(QString dbname);
        QSqlDatabase db;
        Q_INVOKABLE bool signInUser(QString user, QString pass);
        Q_INVOKABLE bool registerUser(QString user, QString pass);
        void insertSpeed(QString speed);
    signals:
        void inputTextChanged();
        void displayedTextChanged();
    private:
        MarkovChain _mChain;
        QString _inputText;
        QString _sampleText;
        QString _displayedText;
        QString _currentUser;
};

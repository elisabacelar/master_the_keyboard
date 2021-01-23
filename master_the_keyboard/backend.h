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
    signals:
        void inputTextChanged();
        void displayedTextChanged();
    private:
        MarkovChain _mChain;
        QString _inputText;
        QString _sampleText;
        QString _displayedText;
};

#endif // BACKEND_H

//#include <QDeclarativeItem>
//#include <QMainWindow>
//#include <QQuickItem>
//#include <QSharedDataPointer>
//#include <QWidget>

//class BackEnd : public QObject {
//    Q_OBJECT

//    public:
//        explicit BackEnd(QObject *parent = nullptr);

//        QString userName();
//        void setUserName(const QString &userName);

//    signals:
//        void userNameChanged();

//    private:
//        QString m_userName;
//};



//class BackEndData;


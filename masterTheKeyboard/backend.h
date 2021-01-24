#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>
#include "textchecker.h"

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
    Q_PROPERTY(QString passwordInput READ getPassword WRITE setPassword NOTIFY \
               passwordChanged)
    Q_PROPERTY(QString correctness READ getCorrectness WRITE setCorrectness NOTIFY \
               correctnessChanged)


    public:
        explicit BackEnd(QObject* parent = nullptr);

        QString getInputText();
        void setInputText(const QString &inputText);
        void handleInputChange();
        QString getDisplayedText();
        void setDisplayedText(const QString &text);
        QString getReferenceText();
        void setReferenceText(const QString &text);
        bool isLoginWindowVisible();
        void setLoginWindowVisibility(bool visibility);
        void handleNewSession();
        void handleNewUser();
        QString getUserName();
        void setUserName(const QString &userName);
        QString getPassword();
        void setPassword(const QString &password);
        QString getCorrectness();
        void setCorrectness(const QString &correctness);


    signals:
        void inputTextChanged();
        void displayedTextChanged();
        void loginWindowVisibilityChanged();
        void userNameChanged();
        void passwordChanged();
        void correctnessChanged();

    private:
        QString _inputText;
        QString _displayedText;
        bool _loginWindowVisibility;
        QString _userNameInput;
        QString _passwordInput;
        QString _correctness;
        Metrics _textVerification;
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


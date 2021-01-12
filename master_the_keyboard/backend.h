#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString inputText READ getInputText WRITE setInputText NOTIFY inputTextChanged)


    public:
        explicit BackEnd(QObject* parent = nullptr);

        QString getInputText();
        void setInputText(const QString &userName);

    signals:
        void inputTextChanged();

    private:
        QString _inputText;
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


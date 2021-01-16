#include "backend.h"
#include "textchecker.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{}

QString BackEnd::getInputText()
{
    return _inputText;
}

void BackEnd::setInputText(const QString &inputText)
{
    if (inputText == _inputText)
        return;

    _inputText = inputText;
    emit inputTextChanged();
    this->handleInputChange();
}

QString BackEnd::getDisplayedText()
{
    return _displayedText;
}

void BackEnd::setDisplayedText(const QString &displayedText)
{
    if (displayedText == _displayedText)
        return;

    _displayedText = displayedText;
    emit displayedTextChanged();
}

void BackEnd::handleInputChange() {
    QString text = "Long text to be written by the user of this application (master the keyboard).";
    this->setDisplayedText(compareText(text,_inputText));
}

//#include "backend.h"

//class BackEndData : public QSharedData
//{
//public:

//};

//BackEnd::BackEnd(QObject *parent) : QObject(parent), data(new BackEndData)
//{

//}

//BackEnd::BackEnd(const BackEnd &rhs) : data(rhs.data)
//{

//}

//BackEnd &BackEnd::operator=(const BackEnd &rhs)
//{
//    if (this != &rhs)
//        data.operator=(rhs.data);
//    return *this;
//}

//BackEnd::~BackEnd()
//{

//}

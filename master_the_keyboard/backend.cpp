#include "backend.h"
#include "textchecker.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    MarkovChain mChain;
    _mChain = mChain;
}

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

QString BackEnd::getSampleText()
{
    return _displayedText;
}

void BackEnd::setSampleText(int words)
{
    QString sampleText = _mChain.generateText(words);

    _sampleText = sampleText;
    this->setDisplayedText(sampleText);
}

void BackEnd::handleInputChange() {
    //QString text = "Long text to be written by the user of this application (master the keyboard).";
    this->setDisplayedText(compareText(_sampleText,_inputText));
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

#include "backend.h"

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

void BackEnd::handleInputChange() {
    this->setDisplayedText(_textVerification.compareText(_inputText));
    this->setCorrectness(_textVerification.getCorrectness());
}

QString BackEnd::getDisplayedText()
{
    return _displayedText;
}

void BackEnd::setDisplayedText(const QString &text)
{
    if (text == _displayedText)
        return;

    _displayedText = text;
    emit displayedTextChanged();
}

QString BackEnd::getReferenceText()
{
    return _textVerification.getCurrentText();
}

void BackEnd::setReferenceText(const QString &text)
{
    if (text == _textVerification.getCurrentText())
        return;

    _textVerification.setCurrentText(text);
    this->setDisplayedText(text);
    emit displayedTextChanged();
}

bool BackEnd::isLoginWindowVisible()
{
    return _loginWindowVisibility;
}

void BackEnd::setLoginWindowVisibility(bool visibility)
{
    if (visibility == _loginWindowVisibility)
        return;

    if(visibility)
        this->handleNewUser();
    else
        this->handleNewSession();

    _loginWindowVisibility = visibility;
    emit loginWindowVisibilityChanged();
}

void BackEnd::handleNewSession()
{
    QString newText = "Username: ";
    newText.append(this->getUserName());
    newText.append("\nPassword: ");
    newText.append(this->getPassword());
    this->setDisplayedText(newText);
}

void BackEnd::handleNewUser()
{}

QString BackEnd::getUserName()
{
    return _userNameInput;
}

void BackEnd::setUserName(const QString &userName)
{
    if (userName == _userNameInput)
        return;

    _userNameInput = userName;
    emit userNameChanged();
}

QString BackEnd::getPassword()
{
    return _passwordInput;
}

void BackEnd::setPassword(const QString &password)
{
    if (password == _passwordInput)
        return;

    _passwordInput = password;
    emit passwordChanged();
}

QString BackEnd::getCorrectness()
{
    return _correctness;
}

void BackEnd::setCorrectness(const QString &correctness)
{
    if (correctness == _correctness)
        return;

    _correctness = correctness;
    emit correctnessChanged();
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

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

    // first call of this function after resetText
    if (!_isExerciseOngoing)
    {
        _isExerciseOngoing = true;
        _textVerification.setStartTime();

        qDebug()<< "Started exercise.";
    }
    _inputText = inputText;
    emit inputTextChanged();
    this->handleInputChange();
}

void BackEnd::handleInputChange()
{
    this->setDisplayedText(_textVerification.compareText(_sampleText,_inputText));
    this->setCorrectness(_textVerification.getCorrectness());
    this->setSpeed(_textVerification.getSpeed());
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

    // Pass through compareText to escape HTML characters
    QString result = _textVerification.compareText(sampleText,QString());
    this->setDisplayedText(result);
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
    qDebug()<<"Started new session, username: " << this->getUserName();
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


void BackEnd::setupDb(QString dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if(!db.open())
    {
        qDebug()<<"Failed to open database";
        return;
    }

    qDebug()<<"Database open";
    foreach (QString table, db.tables())
    {
        if(table == "dbUsers")
        {
            qDebug()<<"Table dbUsers found";
            return;
        }
    }
    qDebug()<<"Table dbUsers not found, creating...";
    QSqlQuery query(db);
    query.exec("CREATE TABLE dbUsers (id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(16), password VARCHAR(16), time DOUBLE)");
}

void BackEnd::resetText()
{
    _textVerification.resetMetrics();
    setInputText(QString());
    _isExerciseOngoing = false; // this will be set to true after next call of setInputText
    setSampleText(20);
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

QString BackEnd::getSpeed()
{
    return _speed;
}

void BackEnd::setSpeed(const QString &speed)
{
    if (speed == _speed)
        return;

    _speed = speed;
    emit speedChanged();
}

#include "BackEnd.h"
#include "Metrics.h"

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

void BackEnd::databaseInit(QString dbName)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(dbName);

    if(!_db.open())
    {
        qWarning() << "Failed to open database - ERROR: " << _db.lastError().text();
        return;
    }

    foreach (QString table, _db.tables())
    {
        if(table == "users")
        {
            return;
        }
    }

    QSqlQuery query("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT)");
    if(!query.isActive())
    {
        qWarning() << "Creating user table - ERROR: " << query.lastError().text();
    }
}

QString BackEnd::signInUser(const QString &userName)
{
    QSqlQuery query(_db);
    if(!query.exec("select * from users where username='"+userName+"'"))
    {
        qWarning() << "Accessing database - ERROR: " << query.lastError().text();
        return "Failed to sign in";
    }

    if(query.next())
    {
        setUserName(userName);
        qDebug()<<"user logged";
        return "User logged";
    }

    qDebug()<<"User not found";
    return "User not found, please check your name or create a new one";
}

QString BackEnd::registerUser(const QString &userName)
{
    QSqlQuery query(_db);
    if(!query.exec("select * from users where username='"+userName+"'"))
    {
        qWarning() << "Accessing database - ERROR: " << query.lastError().text();
        return "Failed to create account";
    }

    if(query.next())
    {
        qDebug()<<"User: '"+userName+"' already registered.";
        return "User already registered, please SIGN IN";
    }
    else
    {
        query.prepare("INSERT INTO users (username) VALUES ('"+userName+"')");
        if(!query.exec())
        {
            qWarning() << "Registering user - ERROR: " << query.lastError().text();
            return "Failed to create account";
        }
        setUserName(userName);
        qDebug()<<"User: '"+userName+"' successfully registered";
        return "User successfully registered";
    }
}

void BackEnd::createNewTable()
{
    QSqlQuery query("CREATE TABLE '"+_userNameInput+"' (id INTEGER PRIMARY KEY, speed TEXT, accuracy TEXT, TEXT DEFAULT CURRENT_TIMESTAMP)");
    if(!query.isActive())
    {
        qWarning() << "Creating user data table - ERROR: " << query.lastError().text();
    }
}

void BackEnd::saveMetrics()
{
    bool isNewUser = true;
    foreach (QString table, _db.tables())
    {
        if(table == _userNameInput)
        {
            isNewUser = false;
        }
    }

    if(isNewUser)
    {
        createNewTable();
    }

    QSqlQuery query(_db);
    if(!query.exec("INSERT INTO '"+_userNameInput+"' (speed, accuracy) VALUES ('"+_speed+"', '"+_correctness+"')"))
    {
        qWarning() << "Saving metrics - ERROR: " << query.lastError().text();
    }
}

void BackEnd::saveSpeed()
{
    QSqlQuery query(_db);
    if(!query.exec("INSERT INTO '"+_userNameInput+"' (speed) VALUES ('"+_speed+"')"))
    {
        qWarning() << "Saving speed - ERROR: " << query.lastError().text();
    }
}

void BackEnd::saveAccuracy()
{
    QSqlQuery query(_db);
    if(!query.exec("INSERT INTO '"+_userNameInput+"' (accuracy) VALUES ('"+_correctness+"')"))
    {
        qWarning() << "Saving accuracy - ERROR: " << query.lastError().text();
    }
}

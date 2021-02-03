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
    this->setAccuracy(_textVerification.getAccuracy());
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

int BackEnd::getAccuracy()
{
    return _accuracy;
}

void BackEnd::setAccuracy(const int accuracy)
{
    if (accuracy == _accuracy)
        return;

    _accuracy = accuracy;
    emit accuracyChanged();
}

int BackEnd::getSpeed()
{
    return _speed;
}

void BackEnd::setSpeed(const int speed)
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
        createNewTable();
        qDebug()<<"User: '"+userName+"' successfully registered";
        return "User successfully registered";
    }
}

void BackEnd::createNewTable()
{
    QSqlQuery query("CREATE TABLE '"+_userNameInput+"' (id INTEGER PRIMARY KEY, speed INTEGER, accuracy INTEGER, timestamp DATE DEFAULT (datetime('now','localtime')))");
    if(!query.isActive())
    {
        qWarning() << "Creating user data table - ERROR: " << query.lastError().text();
    }
}

void BackEnd::saveMetrics()
{
    QSqlQuery query(_db);
    if(!query.exec("INSERT INTO '"+_userNameInput+"' (speed, accuracy) VALUES ('"+QString("%1").arg(_speed)+"', '"+QString("%1").arg(_accuracy)+"')"))
    {
        qWarning() << "Saving metrics - ERROR: " << query.lastError().text();
    }
}

void BackEnd::getDataHistory()
{
    QSqlQuery query(_db);
    if(!query.exec("select * from '"+_userNameInput+"'"))
    {
        qWarning() << "Reading database - ERROR: " << query.lastError().text();
        return;
    }

    query.last();
    QVariantList accuracyHistory;
    QVariantList speedHistory;


    int it = 0;
    while(it<30)
    {
        accuracyHistory.append(query.value("accuracy"));
        speedHistory.append(query.value("speed"));
        ++it;
        if(!query.previous())
            break;
    }

    this->setAccuracyHistory(accuracyHistory);
    this->setSpeedHistory(speedHistory);
}

void BackEnd::clearUserData()
{
    QSqlQuery query(_db);
    if(!query.exec("DELETE from '"+_userNameInput+"'"))
    {
        qWarning() << "Delete user data - ERROR: " << query.lastError().text();
    }
}

void BackEnd::deleteAccount()
{
    QSqlQuery query(_db);
    if(!query.exec("DELETE from users where username='"+_userNameInput+"'"))
    {
        qWarning() << "Delete account - ERROR: " << query.lastError().text();
    }
    if(!query.exec("DROP TABLE IF EXISTS '"+_userNameInput+"'"))
    {
        qWarning() << "Delete User Table - ERROR: " << query.lastError().text();
    }
}

QVariantList BackEnd::getAccuracyHistory()
{
    return _accuracyHistory;
}

void BackEnd::setAccuracyHistory(const QVariantList accuracyHistory)
{
    if (accuracyHistory == _accuracyHistory)
        return;
    _accuracyHistory.clear();
    int listLength = accuracyHistory.length();
    for(int it=0;it<listLength;++it) {
        _accuracyHistory.append(accuracyHistory[it]);
    }
    emit accuracyHistoryChanged();
}

QVariantList BackEnd::getSpeedHistory()
{
    return _speedHistory;
}

void BackEnd::setSpeedHistory(const QVariantList speedHistory)
{
    if (speedHistory == _speedHistory)
        return;
    _speedHistory.clear();
    int listLength = speedHistory.length();
    for(int it=0;it<listLength;++it) {
        _speedHistory.append(speedHistory[it]);
    }
        emit speedHistoryChanged();
}


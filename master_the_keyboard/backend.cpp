#include "backend.h"
#include "textchecker.h"
#include "ExerciseResult.h"

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
        _exerciseStartTime = std::chrono::high_resolution_clock::now();

        qDebug()<< "Started exercise.";
    }
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

    // Pass through compareText to escape HTML characters
    std::pair<int, QString> result = compareText(sampleText,QString());
    this->setDisplayedText(result.second);
}

void BackEnd::handleInputChange() {
    //QString text = "Long text to be written by the user of this application (master the keyboard).";

    std::pair<int, QString> result = compareText(_sampleText,_inputText);
    this->setDisplayedText(result.second);

    // reset text automatically if the user typed everything
    if (_sampleText.length() == _inputText.length())
    {
        this->generateResult(result.first, _sampleText.length());
        this->resetText();
    }
}

void BackEnd::generateResult(int nCorrect, int nTotal)
{
    using namespace std::chrono;

    TimePoint exerciseEndTime = high_resolution_clock::now();
    unsigned duration = duration_cast<seconds>(exerciseEndTime - _exerciseStartTime).count();
    ExerciseResult R (nCorrect, nTotal, duration);

    qDebug() << "Finished exercise, results:";
    qDebug() << "\tTime [s]: " << duration << ", Character count: " << nCorrect << "";
    qDebug() << "\tSpeed [WPM]: " << R.getSpeedWPM() << " WPM, Accuracy: " << R.getFormattedAccuracy() << " %\n";
}

void BackEnd::resetText()
{
    setInputText(QString());
    _isExerciseOngoing = false; // this will be set to true after next call of setInputText
    setSampleText(20);
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
    query.exec("CREATE TABLE dbUsers (id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username VARCHAR(16), password VARCHAR(16), time DOUBLE)");
}

bool BackEnd::signInUser(QString user, QString pass)
{
    QSqlQuery query(db);
    if(!query.exec("select * from dbUsers where username='"+user+"'"))
    {
        qDebug()<<"Error accessing database";
        return false;
    }

    if(query.next())
    {
        if(pass == query.value(2))
        {
            _currentUser = user;
            qDebug()<<"user logged";
            return true;
        }
        else
        {
            qDebug()<<"Incorrect password";
            return false;
        }
    }

    qDebug()<<"User not found";
    return false;
}
bool BackEnd::registerUser(QString user, QString pass)
{
    QSqlQuery query(db);
    if(!query.exec("select * from dbUsers where username='"+user+"'"))
    {
        qDebug()<<"Error accessing database";
        return false;
    }

    if(query.next())
    {
        qDebug()<<"User already registered.";
        return false;
    }
    else
    {
        query.prepare("insert into dbUsers (username,password) values ('"+user+"','"+pass+"')");
        if(!query.exec())
        {
            qDebug()<<"Error registering user";
            return false;
        }
        _currentUser = user;
        qDebug()<<"User successfully registered";
        return true;
    }
}

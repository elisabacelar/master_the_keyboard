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

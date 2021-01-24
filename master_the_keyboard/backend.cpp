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
    this->setDisplayedText(sampleText);
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

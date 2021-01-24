#include "textchecker.h"

QString Metrics::compareText(QString& otherString)
{
    int stringLength = otherString.length() < _textLength ? otherString.length() : _textLength;
    QString stringBeginning, stringMiddle, stringEnd, stringResult, stringModifier;
    stringResult = "";
    stringEnd = _text;
    int stringRemovedLength = 0;
    int domainStart;
    int errors = 0;
    int hits = 0;
    int it = 0;
    while(it<stringLength)
    {
        domainStart = it;
        if(otherString[it]!=_text[it])
        {
            stringModifier = "<span style=\"color:#FF0000;text-decoration:line-through;\">";
            do
            {
                ++it;
                if(it==stringLength)
                    break;
            } while(otherString[it]!=_text[it]);
            errors += it - domainStart;
        }
        else
        {
            stringModifier = "<span style=\"color:#00FF00;\">";
            do
            {
                ++it;
                if(it==stringLength)
                    break;
            }
            while(otherString[it]==_text[it]);
            hits += it - domainStart;
        }
        stringBeginning = stringEnd.left(it-stringRemovedLength);
        stringMiddle = stringBeginning.right(stringBeginning.length()-(domainStart-stringRemovedLength));
        stringBeginning= stringBeginning.left(domainStart-stringRemovedLength);
        stringRemovedLength += stringBeginning.length() + stringMiddle.length();
        stringEnd = _text.right(_textLength-it);
        stringResult.append(stringBeginning);
        stringResult.append(stringModifier);
        stringResult.append(stringMiddle);
        stringResult.append("</span>");
    }
    this->updateCorrectness(errors,hits);
    stringResult.append(stringEnd);
    return stringResult;
}

QString Metrics::getCorrectness()
{
    QString correctness = "";
    QString correctnessText = "";
    int errorPercentage = int (std::round((100*_numberOfErrors)/(_currentNumberOfHits+\
                          _numberOfErrors)));

    if(errorPercentage<5)
        correctnessText.append("<span style=\"color:#CC00CC;\">");
    else if(errorPercentage<10)
        correctnessText.append("<span style=\"color:#0000FF;\">");
    else if(errorPercentage<20)
        correctnessText.append("<span style=\"color:#00FF00;\">");
    else if(errorPercentage<30)
        correctnessText.append("<span style=\"color:#FFFF00;\">");
    else if(errorPercentage<50)
        correctnessText.append("<span style=\"color:#FF6600;\">");
    else
        correctnessText.append("<span style=\"color:#FF0000;\">");

    correctness = QString("%1").arg(100-errorPercentage);

    correctnessText.append(correctness);
    correctnessText.append("%");
    correctnessText.append("</span>");

    return correctnessText;
}

void Metrics::updateCorrectness(int errors, int hits)
{
    if(errors>_currentNumberOfErrors)
        _numberOfErrors++;

    _currentNumberOfErrors = errors;
    _currentNumberOfHits = hits;
}

void Metrics::setCurrentText(QString text)
{
    if (text == _text)
        return;

    _text = text;
    _textLength = _text.length();
    _numberOfErrors = 0;
    _currentNumberOfHits = 0;
    _currentNumberOfErrors = 0;
}

QString Metrics::getCurrentText()
{
    return _text;
}


int Metrics::getCurrentTextLength()
{
    return _textLength;
}

#include "textchecker.h"

QString compareText(QString& referenceString,QString& otherString)
{
    int stringLength = otherString.length() < referenceString.length() ? otherString.length() : referenceString.length();
    QString stringBeginning, stringMiddle, stringEnd, stringResult, stringModifier;
    stringResult = "";
    stringEnd = referenceString;
    int stringRemovedLength = 0;
    int domainStart;
    int it = 0;
    while(it<stringLength)
    {
        domainStart = it;
        if(otherString[it]!=referenceString[it])
        {
            stringModifier = "<span style=\"color:#FF0C32;text-decoration:line-through;\">";
            do
            {
                if(it==stringLength)
                    break;
                ++it;
            } while(otherString[it]!=referenceString[it]);
        }
        else
        {
            stringModifier = "<span style=\"color:#0CFF32;\">";
            do
            {
                if(it==stringLength)
                    break;
                ++it;
            }
            while(otherString[it]==referenceString[it]);
        }
        stringBeginning = stringEnd.left(it-stringRemovedLength);
        stringMiddle = stringBeginning.right(stringBeginning.length()-(domainStart-stringRemovedLength));
        stringBeginning= stringBeginning.left(domainStart-stringRemovedLength);
        stringRemovedLength += stringBeginning.length() + stringMiddle.length();
        stringEnd = referenceString.right(referenceString.length()-it);
        stringResult.append(stringBeginning);
        stringResult.append(stringModifier);
        stringResult.append(stringMiddle);
        stringResult.append("</span>");
    }
    stringResult.append(stringEnd);
    return stringResult;
}

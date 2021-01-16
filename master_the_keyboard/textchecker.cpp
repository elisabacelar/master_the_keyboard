#include "textchecker.h"

QString compareText(QString referenceString,QString otherString)
{
    int stringLength = otherString.length() < referenceString.length() ? otherString.length() : referenceString.length();
    QString stringBeginning, stringMiddle, stringEnd, stringResult;
    stringResult = "";
    stringEnd = referenceString;
    int stringRemovedLength = 0;
    int errorStart;
    int it = 0;
    while(it<stringLength) {
        if(otherString[it]!=referenceString[it]) {
            errorStart = it++;
            while(otherString[it]!=referenceString[it]) {
                if(it==stringLength)
                    break;
                ++it;
            }
            stringBeginning = stringEnd.left(it-stringRemovedLength);
            stringMiddle = stringBeginning.right(stringBeginning.length()-(errorStart-stringRemovedLength));
            stringBeginning= stringBeginning.left(errorStart-stringRemovedLength);
            stringRemovedLength += stringBeginning.length() + stringMiddle.length();
            stringEnd = referenceString.right(referenceString.length()-it);
            stringResult.append(stringBeginning);
            stringResult.append("<span style=\"color:#FF0c32;text-decoration:line-through;\">");
            stringResult.append(stringMiddle);
            stringResult.append("</span>");
        }
        ++it;
    }
    stringResult.append(stringEnd);
    return stringResult;
}

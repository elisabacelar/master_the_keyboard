#include "textchecker.h"

std::pair<int, QString> compareText(QString& reference, QString& other)
{
    QString result, modifier;

    int length = other.length() < reference.length() ? other.length() : reference.length();
    int domainStart;
    int it = 0;
    int countCorrect = 0;

    while(it<length)
    {
        domainStart = it;
        if(other[it]!=reference[it])
        {
            modifier = "<span style=\"color:#FF0C32;text-decoration:line-through;\">";
            do
            {
                if(it==length)
                    break;
                ++it;
            } while(other[it]!=reference[it]);
        }
        else
        {
            modifier = "<span style=\"color:#0CFF32;\">";
            do
            {
                if(it==length)
                    break;
                ++it;
                ++countCorrect;
            }
            while(other[it]==reference[it]);
        }

        QString portion = reference.mid(domainStart, it - domainStart);
        result.append(modifier).append(portion).append("</span>");
    }

    if (length < reference.length()){
        result.append(reference.right(reference.length() - length));
    }
    return std::make_pair(countCorrect, result);
}

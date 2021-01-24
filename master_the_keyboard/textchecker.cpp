#include "textchecker.h"

std::pair<int, QString> compareText(const QString& reference, const QString& other)
{
    QString result, modifier;

    int domainStart = 0;
    int countCorrect = 0;
    int length = other.length() < reference.length()
                    ? other.length()
                    : reference.length();
    int i = 0;
    while (i < length)
    {
        domainStart = i;
        if (other[i] != reference[i])
        {
            modifier = "<span style=\"color:#FF0C32;text-decoration:line-through;\">";
            do
            {
                if(++i == length) break;
            } while (other[i] != reference[i]);
        }
        else
        {
            modifier = "<span style=\"color:#0CFF32;\">";
            do
            {
                ++countCorrect;
                if(++i == length) break;
            } while (other[i] == reference[i]);
        }
        result.append(modifier)
              .append(reference.mid(domainStart, i - domainStart).toHtmlEscaped())
              .append("</span>");
    }
    if (length < reference.length())
    {
        result.append(reference.right(reference.length() - length).toHtmlEscaped());
    }
    return std::make_pair(countCorrect, result);
}

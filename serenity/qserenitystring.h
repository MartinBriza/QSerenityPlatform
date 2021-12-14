#ifndef QSERENITYSTRING_H
#define QSERENITYSTRING_H

#define AK_DONT_REPLACE_STD

#include <QtCore/private/qstringconverter_p.h>
#include <forward_list>
#include <AK/StdLibExtraDetails.h>
#include <AK/String.h>
#include <QString>

class QSerenityString
{
public:
    static AK::String fromQString(const QString& str);
    static QString toQString(const AK::String& v);
};

#endif  // QSERENITYSTRING_H

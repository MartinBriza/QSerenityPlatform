#ifndef QSERENITYSTRING_H
#define QSERENITYSTRING_H

#include <AK/String.h>
#include <QString>

class QSerenityString
{
public:
    static AK::String fromQString(const QString &str);
    static QString toQString(const AK::String &v);
};

#endif // QSERENITYSTRING_H

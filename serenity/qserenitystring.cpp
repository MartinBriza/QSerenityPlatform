#include "qserenitystring.h"

#include <AK/StdLibExtraDetails.h>

AK::String QSerenityString::fromQString(const QString &str) {
    return AK::String(str.toStdString().c_str());
}

QString QSerenityString::toQString(const AK::String &v) {
    return QString(v.characters());
}

#ifndef VALUE_H
#define VALUE_H

#include <QString>

QString vget(QString key);
QString vget_ensure(QString key, QString value);
void vset(QString key, QString value);

#endif // VALUE_H

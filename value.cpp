#include "value.h"

#include <stdio.h>
#include <QDir>
#include <QStandardPaths>

FILE *vf_open(QString key, const char *mode)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    return fopen(QDir(path).filePath(key).toUtf8().constData(), mode);
}

QString vget(QString key)
{
    FILE *f = vf_open(key, "r");
    if(f == NULL)
        return QString();

    char v[0x4000];
    fscanf(f, "%s\n", v);
    QString final = QString::fromUtf8(v);

    fclose(f);
    return final;
}

QString vget_ensure(QString key, QString value)
{
    QString v = vget(key);
    if(v.length() == 0)
    {
        vset(key, value);
        return value;
    }

    return v;
}

void vset(QString key, QString value)
{
    FILE *f = vf_open(key, "w");
    if(f == NULL)
        return;

    fprintf(f, "%s\n", value.toUtf8().constData());
    fclose(f);
}

#ifndef HISTORY_H
#define HISTORY_H

#include <QString>
#include <QFile>
#include <QTextStream>

class History
{
public:
    static void add(const QString &item);
    static QStringList get();
};

#endif // HISTORY_H

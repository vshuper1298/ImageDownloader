#include "history.h"
#include <QDebug>

void History::add(const QString &item)
{
    QFile *historyFile = new QFile("History.txt");
    if (!historyFile->open(QIODevice::Append | QIODevice::Text)){
        qDebug() << "Problem opening file when writing.\n";
        return;
    }

    QTextStream stream(historyFile);
    stream << item << "\n";

    historyFile->close();
    delete historyFile;
}

QStringList History::get()
{
    QFile *historyFile = new QFile("History.txt");
    QStringList historyList;
    if (!historyFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        historyList << "Problem opening file when writing.\n";
        delete historyFile;
        return historyList;
    }
    else{
        QTextStream stream(historyFile);
        while (!stream.atEnd())
            historyList << stream.readLine();

        historyFile->close();
        delete historyFile;
        return historyList;
    }
}

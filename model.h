#ifndef MODEL_H
#define MODEL_H

#include "download.h"
#include <QQueue>
#include <QVector>
#include <QThreadPool>

class Model : public QObject
{
    Q_OBJECT

public:
    Model(QObject *parent = 0);
    ~Model();
    void downloadAppend(Image *image);
    void downloadStart();
    void imageAppend(Image *image);
    Image* imageAt(int index);
    void clearSearchResults();
    void setDownloadPath(const QString &path);
    QString getDownloadPath() const;
    QStringList history() const;
    void addHistoryItem(const QString &item);
    QVector<int*> getDownloadProgresses();

private:
    QQueue<Image*> downloadQueue;
    QVector<Image*> images;
    QVector<int*> downloadProgresses;
    QFile *folderInfo;
    QString downloadPath;
    QThreadPool *pool;
};

#endif // MODEL_H

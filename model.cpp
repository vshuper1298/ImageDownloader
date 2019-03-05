#include "model.h"
#include "history.h"
#include <QDebug>

Model::Model(QObject *parent): QObject(parent)
{
    pool = new QThreadPool(this);
    folderInfo = new QFile("Folderinfo.txt");
    if (folderInfo->size() == 0)
        downloadPath = nullptr;
    else{
        if (!folderInfo->open(QIODevice::ReadOnly))
            qDebug() << "Problem opening file when reading.\n";
        else
            downloadPath = folderInfo->readAll().data();
        folderInfo->close();
    }
}

Model::~Model()
{
    delete folderInfo;
}

void Model::downloadAppend(Image *image)
{
    downloadQueue.enqueue(image);
}

void Model::downloadStart()
{
    downloadProgresses.clear();
    for (Image *image : downloadQueue){
        image = downloadQueue.dequeue();
        Download *download = new Download(image, downloadPath);
        downloadProgresses.append(download->getProgressIndicator());
        pool->start(download);
    }
}

void Model::setDownloadPath(const QString &path)
{
    if (!folderInfo->open(QIODevice::WriteOnly)){
        qDebug() << "Problem opening file when writing.\n";
        return;
    }
    downloadPath = path;
    folderInfo->write(path.toUtf8());
    folderInfo->close();
}

QString Model::getDownloadPath() const
{
    return downloadPath;
}

void Model::imageAppend(Image *image)
{
    images.append(image);
}

Image* Model::imageAt(int index)
{
    return images.at(index);
}

void Model::clearSearchResults()
{
    for (Image *image : images)
        delete image;
    images.clear();
}

QStringList Model::history() const
{
    return History::get();
}

void Model::addHistoryItem(const QString &item)
{
    History::add(item);
}

QVector<int*> Model::getDownloadProgresses()
{
    return downloadProgresses;
}

#include "download.h"
#include "constants.h"
#include <QDebug>
#include <QFileInfo>
#include <QThread>

Download::Download(Image *image, QString folder)
{
    picture = image;
    QUrl url(picture->url());
    size = picture->size();
    progress = 0;
    downloadPath = folder + "/";
    QString fileName = saveFileName(url);
    if (!downloadPath.isEmpty())
        fileName = downloadPath + fileName;
    file = new QFile(fileName);
    finished = false;
}

Download::~Download()
{
    delete file;
}

void Download::run()
{
    if (!file->open(QIODevice::WriteOnly)) {
        qDebug() << QString("Problem opening save file %1 for download: %3\n")
                    .arg(file->fileName()).arg(file->errorString());
        return;
    }

    if (size == 0){
        qDebug() << "File is empty.";
        file->close();
        return;
    }

    QByteArray pictureData = picture->data();
    int pos = 0;
    int percent = size / 100;

    if (percent == 0)
        progress = 100;
    else
        while (!finished){
            QByteArray buffer = pictureData.mid(pos, bufferSize);
            file->write(buffer);
            pos += buffer.size();
            progress = pos / percent;
            if (pos == size)
                finished = true;
        }
    QThread::msleep(10);
    qDebug() << "finished";
    file->close();
}

QString Download::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString name = QFileInfo(path).fileName();

    if (name.isEmpty())
        name = "download";

    if (QFile::exists(downloadPath + name)) {
        int i = 0;
        name += '.';
        while (QFile::exists(downloadPath + name + QString::number(i)))
            ++i;
        name += QString::number(i);
    }

    return name;
}

int *Download::getProgressIndicator()
{
    return &progress;
}

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QRunnable>
#include <QFile>
#include "image.h"

class Download : public QRunnable
{
public:
    Download(Image *image, QString folder);
    ~Download();
    void run() override;
    int* getProgressIndicator();
    QString saveFileName(const QUrl &url);

private:
    QFile *file;
    Image *picture;
    QString downloadPath;
    int size;
    int progress;
    bool finished;
};

#endif // DOWNLOAD_H

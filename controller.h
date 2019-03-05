#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QNetworkAccessManager>
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(Model *m, QObject *parent = 0);
    ~Controller();
    bool isSearchReply(QNetworkReply *reply) const;
    QString &getPictureName(const QString &link);
    void loadImage(const QString &link);
    void loadNextImage();
    void sendSearchRequest(const QString &query, int startIndex);
    void downloadImages(QVector<bool> selectedImages, int page);
    void setSearchQuery(const QString &q);

signals:
    void imagesLoadFinished();

public slots:
    void replyFinished(QNetworkReply *reply);
    void parseData(const QString &data);
    void search(const QString &query);

private:
    int imagesLoaded;
    int searchReplyFinished;
    QString query;
    Model *model;
    QNetworkAccessManager *manager;
    QMap<QString, QString> resultTitles;
    QQueue<QString> loadigQueue;
};

#endif // CONTROLLER_H

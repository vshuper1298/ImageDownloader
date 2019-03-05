#include "constants.h"
#include "controller.h"
#include "image.h"
#include <QNetworkReply>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Controller::Controller(Model *m, QObject *parent) : QObject(parent), model(m)
{
    manager = new QNetworkAccessManager();
    QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
    QString location = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(location);
    manager->setCache(diskCache);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    imagesLoaded = 0;
    searchReplyFinished = 0;
}

Controller::~Controller()
{
    delete manager;
}

void Controller::search(const QString &query)
{
    model->clearSearchResults();
    resultTitles.clear();
    imagesLoaded = 0;
    searchReplyFinished = 0;
    model->addHistoryItem(query);

    for (int i(0); i < maxRequestCount; i++)
        sendSearchRequest(query, startSearchIndex + resultsPerRequest * 0);
}

void Controller::replyFinished(QNetworkReply *reply)
{

    if (isSearchReply(reply)){
        QString strReply = (QString)reply->readAll();
        parseData(strReply);
        reply->deleteLater();
        ++searchReplyFinished;
        if (searchReplyFinished == maxRequestCount)
            for (int i(0); i < maxRequestCount; i++)
                loadNextImage();
    }
    else{
        QUrl imageUrl = reply->request().url();
        QString imageName;
        try{
            imageName = getPictureName(imageUrl.toString());
        }
        catch (const QString &s)
        {
            qDebug() << s;
            imageName = s;
        }
        QByteArray imageData = reply->readAll();
        Image *image = new Image(imageName, imageUrl, imageData);
        model->imageAppend(image);
        reply->deleteLater();
        ++imagesLoaded;
        if(imagesLoaded == imagesViewCount)
            emit imagesLoadFinished();
        loadNextImage();
    }
}

void Controller::parseData(const QString &data)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["items"].toArray();

    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();
        QString link = obj["link"].toString();
        QString title = obj["title"].toString();
        resultTitles.insert(link, title);
        loadigQueue.enqueue(link);
    }
}

bool Controller::isSearchReply(QNetworkReply *reply) const
{
    QString url = reply->url().toString();
    return (url.startsWith(customSearchUrl)) ? true : false;
}

void Controller::loadImage(const QString &link)
{
    QUrl url(link);
    QNetworkRequest request(url);
    QNetworkReply *searchReply = manager->get(request);

    if (searchReply->error()) {
        qDebug() << "Loading image failed: " + searchReply->errorString() + "\n";
    }
    else {
        qDebug() << "Loading image succeeded.\n";
    }
}

QString &Controller::getPictureName(const QString &link)
{
    QMap<QString, QString>::iterator i = resultTitles.find(link);
    if (i == resultTitles.end()) {
        qDebug() << "Picture name wasn't found!";
        throw link;
    }
    return i.value();
}

void Controller::loadNextImage()
{
    if (!loadigQueue.isEmpty())
        loadImage(loadigQueue.dequeue());
}

void Controller::downloadImages(QVector<bool> selectedImages, int page)
{
    int startIndex = page * imagesViewCount;
    for (int i = 0; i < selectedImages.size(); i++)
        if (selectedImages.at(i)) {
            int index = i + startIndex;
            Image * image = model->imageAt(index);
            model->downloadAppend(image);
        }
    model->downloadStart();
}

void Controller::sendSearchRequest(const QString &query, int startIndex)
{
    QUrl url(searchQuery.arg(query).arg(startIndex));
    QNetworkRequest request(url);
    QNetworkReply *searchReply = manager->get(request);

    if (searchReply->error()) {
        qDebug() << "Search failed: " + searchReply->errorString() + "\n";
    }
    else {
        qDebug() << "Search succeeded.\n";
    }
}


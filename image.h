#ifndef IMAGE_H
#define IMAGE_H

#include <QByteArray>
#include <QUrl>

class Image
{
public:
    Image(const QString &name, const QUrl &link, const QByteArray &data);
    Image() = default;
    Image(const Image &other) = default;
    Image &operator=(const Image &other) = default;
    ~Image();
    QString name() const;
    void setName(const QString &name);
    QUrl url() const;
    void setUrl(const QUrl &link);
    QByteArray data() const;
    int size() const;

private:
    QString title;
    QUrl imageUrl;
    QByteArray imageData;
};

#endif // IMAGE_H

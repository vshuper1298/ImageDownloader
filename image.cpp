#include "image.h"

Image::Image(const QString &name, const QUrl &link, const QByteArray &data)
{
    title = name;
    imageUrl = link;
    imageData = data;
}

Image::~Image()
{

}

QString Image::name() const
{
    return title;
}

void Image::setName(const QString &name)
{
    title = name;
}

QUrl Image::url() const
{
    return imageUrl;
}

void Image::setUrl(const QUrl &link)
{
    imageUrl = link;
}

QByteArray Image::data() const
{
    return imageData;
}

int Image::size() const
{
    return imageData.size();
}

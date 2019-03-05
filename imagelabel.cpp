#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent)
{
    selected = false;
}

ImageLabel::~ImageLabel()
{

}

void ImageLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if(!isSelected()) {
            select();
            setForegroundRole(QPalette::Highlight);
            emit leftClicked();
        }
    }
    else if (event->button() == Qt::RightButton) {
        if(isSelected()) {
            removeSelection();
            setForegroundRole(QPalette::WindowText);
            emit rightClicked();
        }
    }
}

bool ImageLabel::isSelected()
{
    return selected;
}
void ImageLabel::select()
{
    selected = true;
}
void ImageLabel::removeSelection()
{
    selected = false;
}

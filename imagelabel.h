#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);
    bool isSelected();
    void select();
    void removeSelection();
    ~ImageLabel();
signals:
    void rightClicked();
    void leftClicked();
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    bool selected;
};
#endif // IMAGELABEL_H

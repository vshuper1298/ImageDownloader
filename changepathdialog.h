#ifndef CHANGEPATHDIALOG_H
#define CHANGEPATHDIALOG_H

#include <QDialog>
#include "model.h"

namespace Ui {
class ChangePathDialog;
}

class ChangePathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePathDialog(Model *m, QWidget *parent = 0);
    ~ChangePathDialog();

public slots:
    void okClicked();
    void selectFolderClicked();

private:
    Ui::ChangePathDialog *ui;
    Model *model;
};

#endif // CHANGEPATHDIALOG_H

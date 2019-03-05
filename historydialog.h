#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QStringList historyList, QWidget *parent = 0);
    ~HistoryDialog();

private:
    Ui::HistoryDialog *ui;
};

#endif // HISTORYDIALOG_H

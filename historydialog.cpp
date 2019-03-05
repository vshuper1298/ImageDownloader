#include "historydialog.h"
#include "ui_historydialog.h"

HistoryDialog::HistoryDialog(QStringList historyList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);

    ui->listWidget->addItems(historyList);
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

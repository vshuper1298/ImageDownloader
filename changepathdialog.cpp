#include "changepathdialog.h"
#include "ui_changepathdialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>

ChangePathDialog::ChangePathDialog(Model *m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePathDialog)
{
    ui->setupUi(this);
    model = m;
    ui->lineEdit->setText(model->getDownloadPath());
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(okClicked()));
    connect(ui->buttonSelectFolder, SIGNAL(clicked(bool)), this, SLOT(selectFolderClicked()));
}

ChangePathDialog::~ChangePathDialog()
{
    delete ui;
}

void ChangePathDialog::okClicked()
{
    QFileInfo folder(ui->lineEdit->text());
    if(folder.exists()){
        if(folder.isDir())
            model->setDownloadPath(ui->lineEdit->text());
    }
    else
       QMessageBox::warning(this, "Error", "Folder doesn't exists");
}

void ChangePathDialog::selectFolderClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Folder choosing", QStandardPaths::displayName(QStandardPaths::DocumentsLocation));
    ui->lineEdit->setText(path);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include "changepathdialog.h"
#include "historydialog.h"
#include <QPicture>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new Model();
    controller = new Controller(model);
    pageNumber = 0;
    selectedCount = 0;

    timer = new QTimer(this);
    timer->setInterval(1);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDownloadProgress()));
    timer->start();

    imagesSelected.fill(false, imagesViewCount);

    imageNames.append(ui->labelImageName);
    imageNames.append(ui->labelImageName2);
    imageNames.append(ui->labelImageName3);
    imageNames.append(ui->labelImageName4);
    imageNames.append(ui->labelImageName5);
    imageNames.append(ui->labelImageName6);
    imageNames.append(ui->labelImageName7);
    imageNames.append(ui->labelImageName8);
    imageNames.append(ui->labelImageName9);

    imageThumbnails.append(ui->imageLabel);
    imageThumbnails.append(ui->imageLabel2);
    imageThumbnails.append(ui->imageLabel3);
    imageThumbnails.append(ui->imageLabel4);
    imageThumbnails.append(ui->imageLabel5);
    imageThumbnails.append(ui->imageLabel6);
    imageThumbnails.append(ui->imageLabel7);
    imageThumbnails.append(ui->imageLabel8);
    imageThumbnails.append(ui->imageLabel9);

    for (ImageLabel *img : imageThumbnails){
        connect (img, SIGNAL(leftClicked()), this, SLOT(imageSelected()));
        connect (img, SIGNAL(rightClicked()), this, SLOT(removeSelection()));
    }

    ui->buttonDownload->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete controller;
}

void MainWindow::on_buttonSearch_clicked()
{
    pageNumber = 0;
    connect (controller, SIGNAL(imagesLoadFinished()), this, SLOT(loadImages())); 
    controller->search(ui->lineEdit->text());
}

void MainWindow::on_buttonDownload_clicked()
{
    for (QProgressBar *p : progresses)
        delete p;
    progresses.clear();

    for (int i = 0; i < selectedCount; i++) {
        QProgressBar *bar = new QProgressBar(this);
        bar->setValue(0);
        progresses.append(bar);
        ui->statusBar->addWidget(bar);
    }
    controller->downloadImages(imagesSelected, pageNumber);
}

void MainWindow::on_buttonPrev_clicked()
{
    if (pageNumber != 0) {
        --pageNumber;
        int startIndex = pageNumber * imagesViewCount;
        loadImages(startIndex);
    }
}

void MainWindow::on_buttoNext_clicked()
{
    ++pageNumber;
    int startIndex = pageNumber * imagesViewCount;
    loadImages(startIndex);
}

void MainWindow::on_actionHistory_triggered()
{
    HistoryDialog dialog(model->history());
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_actionChange_download_folder_triggered()
{
    ChangePathDialog dialog(model);
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::loadImages(int from)
{
    for (int i = 0; i < imagesViewCount; i++){
        QByteArray data = model->imageAt(i + from)->data();
        QPixmap pix;
        pix.loadFromData(data);
        if(!pix.isNull()){
            int width = imageThumbnails[i]->width();
            int height = imageThumbnails[i]->height();
            imageThumbnails[i]->setPixmap(pix.scaled(width, height));
        }
    }
}

void MainWindow::updateDownloadProgress()
{
    for(int i = 0; i < progresses.size(); i++){
        int val = *model->getDownloadProgresses().at(i);
        progresses[i]->setValue(val);
    }
}

void MainWindow::imageSelected()
{
    int index = imageThumbnails.indexOf((ImageLabel*)sender());
    imagesSelected[index] = true;
    ++selectedCount;
    if (selectedCount == 1)
        ui->buttonDownload->setVisible(true);
}
void MainWindow::removeSelection()
{
    int index = imageThumbnails.indexOf((ImageLabel*)sender());
    imagesSelected[index] = false;
    --selectedCount;
    if (selectedCount == 0)
        ui->buttonDownload->setVisible(false);
}

void MainWindow::loadImages()
{
    loadImages(0);
}

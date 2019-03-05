#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>
#include <QProgressBar>
#include "controller.h"
#include "imagelabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadImages(int from);

private slots:
    void on_buttonSearch_clicked();
    void on_buttonDownload_clicked();
    void on_buttonPrev_clicked();
    void on_buttoNext_clicked();
    void on_actionHistory_triggered();
    void on_actionChange_download_folder_triggered();
    void updateDownloadProgress();
    void loadImages();
    void imageSelected();
    void removeSelection();

private:
    Ui::MainWindow *ui;
    Model *model;
    Controller *controller;
    QVector<QLabel*> imageNames;
    QVector<ImageLabel*> imageThumbnails;
    QVector<bool> imagesSelected;
    int selectedCount;
    QVector<QProgressBar*> progresses;
    QTimer *timer;
    int pageNumber;
};

#endif // MAINWINDOW_H

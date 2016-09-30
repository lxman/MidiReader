#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "ba32tobe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbOpen_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this, "Choose a midi file.", QDir::homePath());
    if(fName == "") return;
    currFile = new QFile(fName);
    if(currFile->open(QFile::ReadOnly)) {
        QByteArray *ba = new QByteArray(currFile->size(), '0');
        *ba = currFile->readAll();
        hdChunk = new HeaderChunk(ba->left(14));
        if(hdChunk->isValid()) {
            int ptr = 14;
            while(ptr < ba->length()) {
                QByteArray nextHdr = ba->mid(ptr, 8);
                ptr += 8;
                if(nextHdr.left(4) == "MTrk") {
                    int data_len = BA32toBE(nextHdr.right(4)).translated();
                    trkList.append(new TrkChunk(ba->mid(ptr, data_len)));
                    ptr += data_len;
                    qDebug() << ptr << " " << ba->length();
                }
            }
        }
        ba->clear();
        currFile->close();
    }
}

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
		currFile->close();
		hdChunk = new HeaderChunk(ba->left(14));
		if(hdChunk->isValid()) {
			*ba = ba->right(ba->length() - 14);
			while(ba->length() > 0) {
				QByteArray nextHdr = ba->left(8);
				if(nextHdr.left(4) == "MTrk") {
					*ba = ba->right(ba->length() - 8);
					int data_len = BA32toBE(nextHdr.right(4)).translated();
					trkList.append(new TrkChunk(ba->left(data_len)));
					*ba = ba->right(ba->length() - data_len);
					qDebug() << ba->length();
				}
			}
		}
	}
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QList>
#include "headerchunk.h"
#include "trkchunk.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pbOpen_clicked();

private:
	Ui::MainWindow *ui;
	QFile *currFile;
	HeaderChunk *hdChunk;
	QList<TrkChunk *> trkList;
};

#endif // MAINWINDOW_H

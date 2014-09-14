#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QImage>

#include "classicnoise.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void timerUpdate();

private:
	Ui::MainWindow *ui;

	ClassicNoise noise;
	QImage *image;
	QTimer *timer;
};

#endif // MAINWINDOW_H

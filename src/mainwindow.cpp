#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, timer(0)
	, image(0)
{
	ui->setupUi(this);

	image = new QImage(QSize(512, 512), QImage::Format_RGB32);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	timer->start(100);
}

MainWindow::~MainWindow()
{
	timer->stop();
	delete timer;
	delete ui;
}

void MainWindow::timerUpdate()
{
	noise.Generate(image);
	// ui->label->setPixmap(QPixmap::fromImage(*image));
}

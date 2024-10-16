#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPushButton>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(createDucks()));
    timer->start(800);
    ui->shootedDuckCounter->setText(QString::number(shootedDucks));
    ui->missedDuckCounter->setText(QString::number(missedDucks));
}

void MainWindow::createDucks() {
    QPushButton *duck = new QPushButton(ui->frame);
    int maxX = ui->frame->width() - duck->width();
    int randomX = rand() % (maxX + 1);
    duck->setGeometry(randomX, -20, 50, 50);
    duck->show();

    QImage resim(":/res/ordek.png");
    QSize duckSize = duck->size();
    QPixmap pixmap = QPixmap::fromImage(resim);
    QPixmap pixmap2 = pixmap.scaled(duckSize);

    duck->setIconSize(duckSize);
    duck->setIcon(pixmap2);

    QTimer *moveTimer = new QTimer(duck);
    connect(moveTimer, &QTimer::timeout, [=]() {
        int newY = duck->y() + 10;
        duck->move(duck->x(), newY);
        if (newY > ui->frame->height()) {
            moveTimer->stop();
            moveTimer->deleteLater();
            missedDucks++;
            ui->missedDuckCounter->setText(QString::number(missedDucks));
            duck->deleteLater();
        }
    });
    moveTimer->start(50);

    connect(duck, &QPushButton::clicked, [=]() {
        shootDucks(duck);
    });
}

void MainWindow::shootDucks(QPushButton *duck) {
    QImage resim(":/res/vurulma.png");
    QSize duckSize = duck->size();
    QPixmap pixmap = QPixmap::fromImage(resim);
    QPixmap pixmap2 = pixmap.scaled(duckSize);

    duck->setIconSize(duckSize);
    duck->setIcon(pixmap2);

    QTimer *deleteTimer = new QTimer(duck);
    connect(deleteTimer, &QTimer::timeout, [=]() {
        deleteTimer->stop();
        deleteTimer->deleteLater();
        shootedDucks++;
        ui->shootedDuckCounter->setText(QString::number(shootedDucks));
        duck->deleteLater();
    });

    deleteTimer->start(200);
}


MainWindow::~MainWindow()
{
    delete ui;
}


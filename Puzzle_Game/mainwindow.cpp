#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "etiket.h"
#include <QMessageBox>

void ShuffleArray(int arr[], int size);

int imgArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

void MainWindow::ShuffleArray(int dizi[], int boyut) {
    srand(time(NULL));
    for (int i = boyut - 1; i > 0; i--) {
        int rastgeleIndis = rand() % (i + 1);
        std::swap(dizi[i], dizi[rastgeleIndis]);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->setText("Hamle Sayısı :");
    ui->label_3->setText(QString::number(hamleSayisi));
    ShuffleArray(imgArray, sizeof(imgArray) / sizeof(imgArray[0]));
    QImage tamResim(":/res/puzzle.jpg");
    QSize labelSize = ui->label->size();
    QPixmap pixmapTam = QPixmap::fromImage(tamResim);
    QPixmap pixmapTam2 = pixmapTam.scaled(labelSize);
    ui->label->setPixmap(pixmapTam2);

    for (int i = 0; i < sizeof(imgArray) / sizeof(imgArray[0]); ++i) {
        etiket *pushButton = new etiket(this);
        pushButton->setGeometry((i % 5) * 80, (i / 5) * 80, 80, 80);

        QImage butonResim(":/res/" + QString::number(imgArray[i]) + ".png");
        QPixmap butonPixmap = QPixmap::fromImage(butonResim);
        butonPixmap.scaled(pushButton->width(), pushButton->height());
        pushButton->setPixmap(butonPixmap);
        etiketler.append(pushButton);
    }
}

bool MainWindow::kontrolEtiketDuzeni()
{
    int siradakiResim = 0;

    for (int i = 0; i < sizeof(imgArray) / sizeof(imgArray[0]); ++i) {
        etiket *etiket = etiketler.at(i);

        QString resimAdi = ":/res/" + QString::number(siradakiResim) + ".png";
        if (etiket->pixmap()->toImage() != QImage(resimAdi)) {
            return false;
        }

        siradakiResim++;
    }

    return true;
}

int MainWindow::getHamleSayisi() const {
    return hamleSayisi;
}

void MainWindow::arttirHamleSayisi() {
    hamleSayisi++;
    ui->label_3->setText(QString::number(hamleSayisi));
}

MainWindow::~MainWindow()
{
    delete ui;
}



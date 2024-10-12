#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

bool closeCardKey = true;
bool closingTimerKey = false;
QTimer *closingTimer;
QPushButton* pushButton1;
QPushButton* pushButton2;
int imgArray[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
int unsuccessfulMoves;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ButtonCustomiser();
    closingTimer = new QTimer(this);
    ui->labelUnSuccess->setText("Başarısız Hamle Sayısı: ") ;
    ui->labelUnsuccessfulMoves->setText(QString::number(unsuccessfulMoves));
    ShuffleArray(imgArray,sizeof(imgArray)/4);
}

void MainWindow::ButtonCustomiser(){
    QImage resim(":/res/kapak.png");
    QSize buttonSize = ui->pushButton->size();
    QPixmap pixmap = QPixmap::fromImage(resim);
    QPixmap pixmap2 = pixmap.scaled(buttonSize);

    ui->pushButton->setIconSize(buttonSize);
    ui->pushButton->setIcon(pixmap2);

    ui->pushButton_2->setIconSize(buttonSize);
    ui->pushButton_2->setIcon(pixmap2);

    ui->pushButton_3->setIconSize(buttonSize);
    ui->pushButton_3->setIcon(pixmap2);

    ui->pushButton_4->setIconSize(buttonSize);
    ui->pushButton_4->setIcon(pixmap2);

    ui->pushButton_5->setIconSize(buttonSize);
    ui->pushButton_5->setIcon(pixmap2);

    ui->pushButton_6->setIconSize(buttonSize);
    ui->pushButton_6->setIcon(pixmap2);

    ui->pushButton_7->setIconSize(buttonSize);
    ui->pushButton_7->setIcon(pixmap2);

    ui->pushButton_8->setIconSize(buttonSize);
    ui->pushButton_8->setIcon(pixmap2);

    ui->pushButton_9->setIconSize(buttonSize);
    ui->pushButton_9->setIcon(pixmap2);

    ui->pushButton_10->setIconSize(buttonSize);
    ui->pushButton_10->setIcon(pixmap2);
}

void MainWindow::OpenCard(QPushButton* pushButton, int imgNumber) {
    QImage resim(":/res/" + QString::number(imgNumber) + ".png");
    QSize buttonSize = pushButton->size();
    QPixmap pixmap = QPixmap::fromImage(resim);
    QPixmap pixmap2 = pixmap.scaled(buttonSize);

    pushButton->setIconSize(buttonSize);
    pushButton->setIcon(pixmap2);

    if (closeCardKey) {
        pushButton1 = pushButton;
        pushButton1->setProperty("imgNumber", imgNumber);
        closeCardKey = false;
    } else {
        pushButton2 = pushButton;
        pushButton2->setProperty("imgNumber", imgNumber);
        closeCardKey = true;
        CloseCard();
    }
}

void MainWindow::CloseCard() {

    if(closingTimerKey){
        closingTimerKey = false;
        closingTimer->stop();
        if (pushButton1 && pushButton2) {
            int imgNumber1 = pushButton1->property("imgNumber").toInt();
            int imgNumber2 = pushButton2->property("imgNumber").toInt();

            if (imgNumber1 == imgNumber2) {
                pushButton1 = nullptr;
                pushButton2 = nullptr;
            } else {
                unsuccessfulMoves++;
                ui->labelUnsuccessfulMoves->setText(QString::number(unsuccessfulMoves));
                QImage resim(":/res/kapak.png");
                QSize buttonSize = pushButton1->size();
                QPixmap pixmap = QPixmap::fromImage(resim);
                QPixmap pixmap2 = pixmap.scaled(buttonSize);

                pushButton1->setIconSize(buttonSize);
                pushButton1->setIcon(pixmap2);

                pushButton2->setIconSize(buttonSize);
                pushButton2->setIcon(pixmap2);

                pushButton1 = nullptr;
                pushButton2 = nullptr;
            }
        }
    }
    else{
        connect(closingTimer,SIGNAL(timeout()),this,SLOT(CloseCard()));
        closingTimer->start(650);
        closingTimerKey = true;
    }

}

void MainWindow::ShuffleArray(int dizi[], int boyut) {
    srand(time(NULL));
    for (int i = boyut - 1; i > 0; i--) {
        int rastgeleIndis = rand() % (i + 1);
        std::swap(dizi[i], dizi[rastgeleIndis]);
    }
}

void MainWindow::on_pushButton_clicked()
{
    OpenCard(ui->pushButton,imgArray[0]);
}

void MainWindow::on_pushButton_2_clicked()
{
    OpenCard(ui->pushButton_2,imgArray[1]);
}

void MainWindow::on_pushButton_3_clicked()
{
    OpenCard(ui->pushButton_3,imgArray[2]);
}

void MainWindow::on_pushButton_4_clicked()
{
    OpenCard(ui->pushButton_4,imgArray[3]);
}

void MainWindow::on_pushButton_5_clicked()
{
    OpenCard(ui->pushButton_5,imgArray[4]);
}

void MainWindow::on_pushButton_6_clicked()
{
    OpenCard(ui->pushButton_6,imgArray[5]);
}

void MainWindow::on_pushButton_7_clicked()
{
    OpenCard(ui->pushButton_7,imgArray[6]);
}

void MainWindow::on_pushButton_8_clicked()
{
    OpenCard(ui->pushButton_8,imgArray[7]);
}

void MainWindow::on_pushButton_9_clicked()
{
    OpenCard(ui->pushButton_9,imgArray[8]);
}


void MainWindow::on_pushButton_10_clicked()
{
    OpenCard(ui->pushButton_10,imgArray[9]);
}


MainWindow::~MainWindow()
{
    delete ui;
}

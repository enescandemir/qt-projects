#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "etiket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool kontrolEtiketDuzeni();
    int getHamleSayisi() const;
    void arttirHamleSayisi();
    ~MainWindow();

private:
    void ShuffleArray(int dizi[], int boyut);
    QList<etiket*> etiketler;
    Ui::MainWindow *ui;
    int hamleSayisi = 0;
};

#endif // MAINWINDOW_H

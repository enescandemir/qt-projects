#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QFrame *frame;
    int shootedDucks = 0;
    int missedDucks = 0;
    ~MainWindow();

public slots:
    void createDucks();
    void shootDucks(QPushButton *duck);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

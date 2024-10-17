#include "etiket.h"
#include "mainwindow.h"
#include <QMimeData>
#include <QDrag>
#include <QMessageBox>
#include <QDebug>

etiket::etiket(QWidget *parent) : QLabel(parent)
{
    setFrameShape(QFrame::Box);
    setScaledContents(true);
    setAcceptDrops(true);
}

void etiket::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void etiket::dropEvent(QDropEvent *event)
{
    etiket *gelen = qobject_cast<etiket*>(event->source());
    if (gelen && gelen != this) {
        int mesafeKriteri = width();

        QPoint gelenPos = gelen->pos();
        QPoint thisPos = pos();

        int deltaX = qAbs(gelenPos.x() - thisPos.x());
        int deltaY = qAbs(gelenPos.y() - thisPos.y());

        if ((deltaX <= mesafeKriteri && deltaY == 0) ||
            (deltaY <= mesafeKriteri && deltaX == 0) ||
            (deltaX == deltaY && deltaX <= mesafeKriteri))
        {
            QImage birakilan(pixmap()->toImage());
            setPixmap(QPixmap::fromImage(gelen->pixmap()->toImage()));
            gelen->setPixmap(QPixmap::fromImage(birakilan));


            MainWindow *mainWindow = qobject_cast<MainWindow*>(topLevelWidget());
            if (mainWindow && mainWindow->kontrolEtiketDuzeni()) {
                QMessageBox::information(topLevelWidget(), "Oyun Kazanıldı", "Tebrikler! Oyunu kazandınız.");
            }
            mainWindow->arttirHamleSayisi();
        }
    }
}

void etiket::mouseMoveEvent(QMouseEvent *event)
{
    QMimeData *mdata = new QMimeData();
    mdata->setImageData(pixmap()->toImage());
    QDrag *suruklenen = new QDrag(this);
    suruklenen->setMimeData(mdata);
    suruklenen->setPixmap(mdata->imageData().value<QPixmap>());
    suruklenen->exec(Qt::MoveAction);
}

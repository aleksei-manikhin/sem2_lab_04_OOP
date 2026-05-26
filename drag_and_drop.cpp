#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDropEvent>
#include <QEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QStyle>
#include <QUrl>
#include <QWidget>

bool MainWindow::eventFilter(QObject* watched, QEvent* event) {
    int isHandled = 0;

    if (event != nullptr) {
        isHandled = handleTouchpadEvent(watched, event);

        if (!isHandled && (isDropWidget(watched) || watched == ui->centralwidget))
            isHandled = handleDragDropEvent(watched, event);
    }

    return isHandled;
}

int MainWindow::isDropWidget(const QObject* watched) const {
    return watched == ui->contentStackedWidget
           || watched == ui->emptyPage
           || watched == ui->graphPage
           || watched == ui->graphicsView
           || watched == ui->graphicsView->viewport()
           || watched == ui->emptyPageText
           || watched == ui->icon_4;
}

int MainWindow::handleDragDropEvent(const QObject* watched, QEvent* event) {
    int isHandled = 0;
    int isGraphArea = isDropWidget(watched);

    if (event != nullptr) {
        if (event->type() == QEvent::DragEnter || event->type() == QEvent::DragMove) {
            if (isGraphArea && (isHandled = acceptDropEvent((QDropEvent*)event, 0)))
                setDropHintVisible(1);
            else {
                setDropHintVisible(0);
                ((QDropEvent*)event)->ignore();
                isHandled = 1;
            }
        } else if (event->type() == QEvent::Drop) {
            if (isGraphArea && (isHandled = acceptDropEvent((QDropEvent*)event, 1)))
                setDropHintVisible(0);
            else {
                ((QDropEvent*)event)->ignore();
                isHandled = 1;
            }
        } else if (event->type() == QEvent::DragLeave) {
            setDropHintVisible(0);
            isHandled = 1;
        }
    }
    return isHandled;
}

int MainWindow::acceptDropEvent(QDropEvent* dropEvent, int shouldSelectFile) {
    int isHandled = 0;

    if (dropEvent != nullptr) {
        QString filePath = droppedFilePath(dropEvent->mimeData());
        if (!filePath.isEmpty()) {
            if (shouldSelectFile)
                selectFile(filePath);
            dropEvent->acceptProposedAction();
            isHandled = 1;
        }
    }
    return isHandled;
}

void MainWindow::setDropHintVisible(int isVisible) {
    ui->emptyPage->setProperty("dropActive", isVisible != 0);
    ui->emptyPage->style()->unpolish(ui->emptyPage);
    ui->emptyPage->style()->polish(ui->emptyPage);
    ui->emptyPage->update();

    if (hasLoadedData()) {
        QWidget* page = isVisible ? ui->emptyPage : ui->graphPage;
        if (ui->contentStackedWidget->currentWidget() != page)
            ui->contentStackedWidget->setCurrentWidget(page);
    }
}

QString MainWindow::droppedFilePath(const QMimeData* mimeData) const {
    QString filePath;

    if (mimeData != nullptr && mimeData->hasUrls()) {
        const QList<QUrl> urls = mimeData->urls();
        for (const QUrl& url : urls) {
            if (url.isLocalFile()) {
                QString droppedPath = url.toLocalFile();
                QFileInfo fileInfo(droppedPath);
                if (fileInfo.exists() && fileInfo.isFile()) {
                    filePath = droppedPath;
                    break;
                }
            }
        }
    }
    return filePath;
}

void MainWindow::setupDragAndDrop() {
    ui->centralwidget->setAcceptDrops(true);
    ui->graphicsView->viewport()->setAcceptDrops(true);

    ui->centralwidget->installEventFilter(this);
    ui->contentStackedWidget->installEventFilter(this);
    ui->emptyPage->installEventFilter(this);
    ui->graphPage->installEventFilter(this);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->emptyPageText->installEventFilter(this);
    ui->icon_4->installEventFilter(this);
}

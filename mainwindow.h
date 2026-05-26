#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "facade.h"
#include "fileReader.h"
#include "qtSceneDrawer.h"

#include <QMainWindow>
#include <QString>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QDropEvent;
class QEvent;
class QMimeData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    Ui::MainWindow *ui;
    FileReader fileReader;
    std::unique_ptr<QtSceneDrawer> sceneDrawer;
    std::unique_ptr<Facade> facade;
    QString currentFilePath;
    bool isChangingValues = false;

    void SetupFacade();
    void SetupConnections();
    void setupDragAndDrop();
    void OnChooseFileClicked();
    void OnResetButtonClicked();
    void OnParametersChanged();
    void selectFile(const QString& filePath);
    int isDropWidget(const QObject* watched) const;
    int handleDragDropEvent(const QObject* watched, QEvent* event);
    int acceptDropEvent(QDropEvent* dropEvent, int shouldSelectFile);
    void setDropHintVisible(int isVisible);
    QString droppedFilePath(const QMimeData* mimeData) const;
    int hasLoadedData() const;
    bool UpdateScene();
    bool LoadScene();
    bool ScaleScene();
    bool RotateScene();
    bool MoveScene();
    bool HandleFacadeResult(const FacadeOperationResult& result);
    std::string GetCurrentFilePath() const;
};
#endif // MAINWINDOW_H

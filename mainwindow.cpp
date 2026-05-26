#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetupFacade();
    SetupConnections();

    ui->contentStackedWidget->setCurrentWidget(ui->emptyPage);
    ui->statusbar->showMessage(tr("Выберите CSV-файл"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupFacade() {
    sceneDrawer = std::make_unique<QtSceneDrawer>(*ui->graphicsView);
    facade = std::make_unique<Facade>(fileReader, *sceneDrawer);
}

void MainWindow::SetupConnections() {
    connect(ui->icon_2, &QToolButton::clicked, this, &MainWindow::OnChooseFileClicked);
    connect(ui->icon_4, &QToolButton::clicked, this, &MainWindow::OnChooseFileClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::OnResetButtonClicked);

    connect(ui->doubleSpinBox_2, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
    connect(ui->doubleSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
    connect(ui->doubleSpinBox_3, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
    connect(ui->doubleSpinBox_4, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);

    connect(ui->doubleSpinBox_5, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
    connect(ui->doubleSpinBox_6, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
    connect(ui->doubleSpinBox_7, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);

    connect(ui->doubleSpinBox_8, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
    connect(ui->doubleSpinBox_9, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
    connect(ui->doubleSpinBox_10, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);

    connect(ui->doubleSpinBox_14, &QDoubleSpinBox::valueChanged, this, &MainWindow::OnParametersChanged);
}

void MainWindow::OnChooseFileClicked() {
    QDir filesDirectory(QCoreApplication::applicationDirPath());
    filesDirectory.cd("../../..");
    filesDirectory.cd("files_for_selecting");

    const QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Выберите CSV-файл"),
        filesDirectory.absolutePath(),
        tr("CSV files (*.csv);;All files (*.*)"));

    if (filePath.isEmpty()) {
        return;
    }

    currentFilePath = filePath;

    if (UpdateScene()) {
        ui->filePathLineEdit->setText(filePath);
    }
}

void MainWindow::OnResetButtonClicked() {
    isChangingValues = true;

    ui->doubleSpinBox_2->setValue(0.0);
    ui->doubleSpinBox->setValue(5.0);
    ui->doubleSpinBox_3->setValue(1.0);
    ui->doubleSpinBox_4->setValue(1.0);

    ui->doubleSpinBox_5->setValue(0.0);
    ui->doubleSpinBox_6->setValue(0.0);
    ui->doubleSpinBox_7->setValue(0.0);

    ui->doubleSpinBox_8->setValue(0.0);
    ui->doubleSpinBox_9->setValue(0.0);
    ui->doubleSpinBox_10->setValue(0.0);

    ui->doubleSpinBox_14->setValue(1.0);

    isChangingValues = false;
    UpdateScene();
}

void MainWindow::OnParametersChanged() {
    if (!isChangingValues) {
        UpdateScene();
    }
}

bool MainWindow::UpdateScene() {
    if (currentFilePath.isEmpty()) {
        ui->contentStackedWidget->setCurrentWidget(ui->emptyPage);
        return false;
    }

    ui->contentStackedWidget->setCurrentWidget(ui->graphPage);

    return LoadScene() && ScaleScene() && RotateScene() && MoveScene();
}

bool MainWindow::LoadScene() {
    return HandleFacadeResult(facade->LoadScene(
        GetCurrentFilePath(),
        static_cast<float>(ui->doubleSpinBox_2->value()),
        static_cast<float>(ui->doubleSpinBox->value()),
        static_cast<float>(ui->doubleSpinBox_3->value()),
        static_cast<float>(ui->doubleSpinBox_4->value())));
}

bool MainWindow::ScaleScene() {
    const float scale = static_cast<float>(ui->doubleSpinBox_14->value());
    return HandleFacadeResult(facade->ScaleScene(scale, scale, scale));
}

bool MainWindow::RotateScene() {
    return HandleFacadeResult(facade->RotateScene(
        static_cast<float>(ui->doubleSpinBox_8->value()),
        static_cast<float>(ui->doubleSpinBox_9->value()),
        static_cast<float>(ui->doubleSpinBox_10->value())));
}

bool MainWindow::MoveScene() {
    return HandleFacadeResult(facade->MoveScene(
        static_cast<float>(ui->doubleSpinBox_5->value()),
        static_cast<float>(ui->doubleSpinBox_6->value()),
        static_cast<float>(ui->doubleSpinBox_7->value())));
}

std::string MainWindow::GetCurrentFilePath() const {
    const QByteArray encodedPath = QFile::encodeName(QDir::toNativeSeparators(currentFilePath));
    return std::string(encodedPath.constData());
}

bool MainWindow::HandleFacadeResult(const FacadeOperationResult& result) {
    if (!result.IsSuccess()) {
        ui->statusbar->showMessage(QString::fromStdString(result.GetErrorMessage()));
        return false;
    }

    return true;
}

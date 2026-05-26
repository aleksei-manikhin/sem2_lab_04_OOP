#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QNativeGestureEvent>
#include <QPoint>
#include <QtGlobal>
#include <QWheelEvent>

static constexpr double TouchpadMoveByPixel = 0.12;
static constexpr double TouchpadMoveByAngle = 1.6 / 120.0;
static constexpr double WheelZoomByPixel = 1.0 / 500.0;
static constexpr double WheelZoomByAngle = 1.0 / 900.0;

static double deltaToSceneMove(int delta, int isPixelDelta) {
    return delta * (isPixelDelta ? TouchpadMoveByPixel : TouchpadMoveByAngle);
}

static double deltaToZoomFactor(int delta, int isPixelDelta) {
    return qBound(0.75, 1.0 + delta * (isPixelDelta ? WheelZoomByPixel : WheelZoomByAngle), 1.35);
}

static QPoint touchpadDelta(QWheelEvent* wheelEvent, int& isPixelDelta) {
    QPoint delta = wheelEvent->pixelDelta();
    isPixelDelta = 1;

    if (delta.isNull()) {
        delta = wheelEvent->angleDelta();
        isPixelDelta = 0;
    }

    return delta;
}

static int zScrollDelta(const QPoint& delta) {
    return delta.y() != 0 ? delta.y() : delta.x();
}

void MainWindow::setSpinBoxValueWithoutUpdate(QDoubleSpinBox* spinBox, double value) {
    isChangingValues = true;
    spinBox->setValue(value);
    isChangingValues = false;
}

int MainWindow::isTouchpadWidget(const QObject* watched) const {
    return watched == ui->graphicsView
           || watched == ui->graphicsView->viewport();
}

int MainWindow::handleTouchpadEvent(const QObject* watched, QEvent* event) {
    if (event == nullptr)
        return 0;

    updateZKeyState(event);

    if (!isTouchpadWidget(watched))
        return 0;

    if (event->type() == QEvent::Wheel)
        return handleTouchpadWheel(static_cast<QWheelEvent*>(event));

    if (event->type() == QEvent::NativeGesture)
        return handleTouchpadNativeGesture(static_cast<QNativeGestureEvent*>(event));

    return 0;
}

void MainWindow::updateZKeyState(QEvent* event) {
    if (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease)
        return;

    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

    if (keyEvent->key() == Qt::Key_Z && !keyEvent->isAutoRepeat())
        isZPressed = event->type() == QEvent::KeyPress;
}

int MainWindow::handleTouchpadWheel(QWheelEvent* wheelEvent) {
    int isPixelDelta = 1;
    const QPoint delta = touchpadDelta(wheelEvent, isPixelDelta);

    if (delta.isNull())
        return 0;

    if (wheelEvent->modifiers() & Qt::ControlModifier)
        zoomTouchpadScene(deltaToZoomFactor(delta.y(), isPixelDelta));
    else
        moveTouchpadScene(delta, isPixelDelta);

    wheelEvent->accept();
    return 1;
}

int MainWindow::handleTouchpadNativeGesture(QNativeGestureEvent* gestureEvent) {
    if (gestureEvent->gestureType() != Qt::ZoomNativeGesture)
        return 0;

    const double scaleDelta = gestureEvent->value();
    if (qFuzzyIsNull(scaleDelta))
        return 0;

    zoomTouchpadScene(qBound(0.2, 1.0 + scaleDelta, 5.0));
    gestureEvent->accept();

    return 1;
}

void MainWindow::zoomTouchpadScene(double scaleFactor) {
    if (qFuzzyCompare(scaleFactor, 1.0))
        return;

    setSpinBoxValueWithoutUpdate(ui->doubleSpinBox_14,
                                 ui->doubleSpinBox_14->value() * scaleFactor);
    UpdateScene();
}

void MainWindow::moveTouchpadScene(const QPoint& delta, int isPixelDelta) {
    if (isZPressed)
        moveTouchpadSceneByZ(delta, isPixelDelta);
    else
        moveTouchpadSceneByXY(delta, isPixelDelta);
}

void MainWindow::moveTouchpadSceneByXY(const QPoint& delta, int isPixelDelta) {
    const double oldX = ui->doubleSpinBox_5->value();
    const double oldY = ui->doubleSpinBox_6->value();
    const double dx = deltaToSceneMove(delta.x(), isPixelDelta);
    const double dy = deltaToSceneMove(delta.y(), isPixelDelta);

    setSpinBoxValueWithoutUpdate(ui->doubleSpinBox_5, oldX + dx);
    setSpinBoxValueWithoutUpdate(ui->doubleSpinBox_6, oldY + dy);
    applyTouchpadMove(ui->doubleSpinBox_5->value() - oldX,
                      ui->doubleSpinBox_6->value() - oldY,
                      0.0);
}

void MainWindow::moveTouchpadSceneByZ(const QPoint& delta, int isPixelDelta) {
    const double oldZ = ui->doubleSpinBox_7->value();
    const double dz = deltaToSceneMove(zScrollDelta(delta), isPixelDelta);

    setSpinBoxValueWithoutUpdate(ui->doubleSpinBox_7, oldZ + dz);
    applyTouchpadMove(0.0, 0.0, ui->doubleSpinBox_7->value() - oldZ);
}

void MainWindow::applyTouchpadMove(double dx, double dy, double dz) {
    if (qFuzzyIsNull(dx) && qFuzzyIsNull(dy) && qFuzzyIsNull(dz))
        return;

    HandleFacadeResult(facade->MoveScene(dx, dy, dz));
}

void MainWindow::setupTouchpad() {
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->viewport()->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->viewport()->unsetCursor();

    ui->doubleSpinBox_5->setRange(-9999.0, 9999.0);
    ui->doubleSpinBox_6->setRange(-9999.0, 9999.0);
    ui->doubleSpinBox_7->setRange(-9999.0, 9999.0);

    if (QCoreApplication::instance() != nullptr)
        QCoreApplication::instance()->installEventFilter(this);
}

#include "qtSceneDrawer.h"

#include <QBrush>
#include <QPen>

QtSceneDrawer::QtSceneDrawer(QGraphicsView& graphicsView)
    : graphicsView(graphicsView) {
    this->graphicsView.setScene(&graphicsScene);
}

void QtSceneDrawer::DrawScene(const Scene& scene) {
    graphicsScene.clear();

    for (const Figure& figure : scene.GetFigures()) {
        DrawFigure(figure);
    }

    graphicsScene.setSceneRect(graphicsScene.itemsBoundingRect());
    //размер сцены равен области, где реально есть нарисованные объекты
    graphicsView.fitInView(graphicsScene.sceneRect(), Qt::KeepAspectRatio);
    //подогнать всю графическую сцену под размер QGraphicsView
}

QPointF QtSceneDrawer::ProjectPoint(const Point3D& point) const {
    const double screenX = (point.X - point.Y) * Scale;
    const double screenY = ((point.X + point.Y) * 0.5 - point.Z) * Scale;

    return QPointF(screenX, screenY);
}

void QtSceneDrawer::DrawFigure(const Figure& figure) {
    const QPen pen(QColor(45, 79, 130), 1.5);

    for (const Edge& edge : figure.GetEdges()) {
        DrawEdge(edge, pen);
    }
}

void QtSceneDrawer::DrawEdge(const Edge& edge, const QPen& pen) {
    const QPointF begin = ProjectPoint(edge.GetBegin().GetPosition());
    const QPointF end = ProjectPoint(edge.GetEnd().GetPosition());

    graphicsScene.addLine(begin.x(), begin.y(), end.x(), end.y(), pen);
}

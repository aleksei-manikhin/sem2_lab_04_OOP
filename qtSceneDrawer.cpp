#include "qtSceneDrawer.h"

#include <QFont>
#include <QGraphicsTextItem>
#include <QPen>
#include <QRectF>

#include <cstddef>
#include <vector>

QtSceneDrawer::QtSceneDrawer(QGraphicsView& graphicsView)
    : graphicsView(graphicsView) {
    this->graphicsView.setScene(&graphicsScene);
}

void QtSceneDrawer::DrawScene(const Scene& scene, bool fitScene) {
    graphicsScene.clear();

    const std::vector<Figure>& figures = scene.GetFigures();
    const QPen figurePen = CreatePen(QColor(37, 76, 134), 2.2);

    if (!figures.empty()) {
        DrawAxes(figures.front());
    }

    for (std::size_t index = 1; index < figures.size(); index++) {
        DrawFigure(figures[index], figurePen);
    }

    if (fitScene) {
        const QRectF sceneRect = graphicsScene.itemsBoundingRect().adjusted(-25.0, -25.0, 25.0, 25.0);
        graphicsScene.setSceneRect(sceneRect);
        graphicsView.fitInView(sceneRect, Qt::KeepAspectRatio);
    }
}

QPointF QtSceneDrawer::ProjectPoint(const Point3D& point) const {
    const double screenX = (point.GetX() - point.GetY()) * Scale;
    const double screenY = ((point.GetX() + point.GetY()) * 0.5 - point.GetZ()) * Scale;

    return QPointF(screenX, screenY);
}

QPen QtSceneDrawer::CreatePen(const QColor& color, double width) const {
    QPen pen(color, width);
    pen.setCosmetic(true);

    return pen;
}

void QtSceneDrawer::DrawAxes(const Figure& axes) {
    const std::vector<Edge>& edges = axes.GetEdges();

    if (edges.size() < 3) {
        DrawFigure(axes, CreatePen(QColor(50, 75, 105), 2.6));
        return;
    }

    DrawAxis(edges[0], CreatePen(QColor(220, 63, 63), 3.0), "X");
    DrawAxis(edges[1], CreatePen(QColor(50, 160, 85), 3.0), "Y");
    DrawAxis(edges[2], CreatePen(QColor(50, 105, 210), 3.0), "Z");
}

void QtSceneDrawer::DrawAxis(const Edge& axis, const QPen& pen, const QString& label) {
    DrawEdge(axis, pen);

    const QPointF labelPosition = ProjectPoint(axis.GetEnd().GetPosition());
    QGraphicsTextItem* text = graphicsScene.addText(label, QFont("Segoe UI", 10, QFont::Bold));
    text->setDefaultTextColor(pen.color());
    text->setPos(labelPosition.x() + 6.0, labelPosition.y() - 18.0);
}

void QtSceneDrawer::DrawFigure(const Figure& figure, const QPen& pen) {
    for (const Edge& edge : figure.GetEdges()) {
        DrawEdge(edge, pen);
    }
}

void QtSceneDrawer::DrawEdge(const Edge& edge, const QPen& pen) {
    const QPointF begin = ProjectPoint(edge.GetBegin().GetPosition());
    const QPointF end = ProjectPoint(edge.GetEnd().GetPosition());

    graphicsScene.addLine(begin.x(), begin.y(), end.x(), end.y(), pen);
}

#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H

#include "point3D.h"
#include "sceneDrawerBase.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QPointF>

class QtSceneDrawer : public SceneDrawerBase {
private:
    static constexpr double Scale = 35.0;

    QGraphicsView& graphicsView;
    QGraphicsScene graphicsScene;

    QPointF ProjectPoint(const Point3D& point) const;
    QPen CreatePen(const QColor& color, double width) const;
    void DrawAxes(const Figure& axes);
    void DrawAxis(const Edge& axis, const QPen& pen, const QString& label);
    void DrawFigure(const Figure& figure, const QPen& pen);
    void DrawEdge(const Edge& edge, const QPen& pen);

public:
    explicit QtSceneDrawer(QGraphicsView& graphicsView);

    void DrawScene(const Scene& scene, bool fitScene) override;
};

#endif // QTSCENEDRAWER_H

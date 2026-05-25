#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H

#include "point3D.h"
#include "sceneDrawerBase.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>

class QtSceneDrawer : public SceneDrawerBase {
private:
    static constexpr double Scale = 35.0;

    QGraphicsView& graphicsView;
    QGraphicsScene graphicsScene;

    QPointF ProjectPoint(const Point3D& point) const;
    void DrawFigure(const Figure& figure);
    void DrawEdge(const Edge& edge, const QPen& pen);

public:
    explicit QtSceneDrawer(QGraphicsView& graphicsView);

    void DrawScene(const Scene& scene) override;
};

#endif // QTSCENEDRAWER_H

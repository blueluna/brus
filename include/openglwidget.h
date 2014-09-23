#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>

#include <stdint.h>

#include "TBox.h"

class OpenGLWidget
	: public QGLWidget
{
	Q_OBJECT

protected:
    QPoint				lastPos;

    int					textureMax;
    int					vertexMax;
    int					indexMax;

    TPoint      		*vertices;
    uint32_t			vertexCount;
    uint32_t			vertexAllocated;

    bool				useShanders;
    QGLShaderProgram	*shaderProgram;
    int					shaderMatrix;
    int					shaderVertices;
    int					shaderColor;

    TBox                bounds;
    TBox        		viewBox;

    TPoint              *polygon;
    uint32_t			polygonVertexCount;

public:
	explicit OpenGLWidget(QWidget *parent = 0);
	~OpenGLWidget();

	uint32_t		GetVertexCount() const { return vertexCount; }

	void			Zoom(const int32_t shapeIndex);

protected:
	virtual void	initializeGL();
	virtual void	resizeGL(int width, int height);
	virtual void	paintGL();
	virtual void	mousePressEvent(QMouseEvent *event);
	virtual void	mouseMoveEvent(QMouseEvent *event);
	virtual void	wheelEvent(QWheelEvent *event);

	void			UpdateViewBoxFromBounds();
	void			UpdateViewMatrix();

    TPoint          translateCoordinate(const int x, const int y) const;
    TPoint          translateCoordinate(const QPoint &p) const;

signals:
	
public slots:
	
};

#endif // OPENGLWIDGET_H

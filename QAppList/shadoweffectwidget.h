#ifndef SHADOWEFFECTWIDGET_H
#define SHADOWEFFECTWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QPixmap>
#include <qmath.h>

#include "qt_windows.h"

/*
 * This class is derived from QDialog, which in turn derived from QWidget.
 * That means we can inherit more features from parent widget other than 
 * subclassed from QWidget.
 */
class ShadowEffectWidget : public QDialog
{
	Q_OBJECT

public:
	explicit ShadowEffectWidget(QWidget *parent = NULL);
	~ShadowEffectWidget(){}
	enum { SHADOW_WIDTH = 5};
protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	ShadowEffectWidget(const ShadowEffectWidget& obj);
	ShadowEffectWidget& operator=(const ShadowEffectWidget& obj);

private:
	bool isPressed;
	QPoint movePoint;

};

#endif // SHADOWEFFECTWIDGET_H

#include "shadoweffectwidget.h"

ShadowEffectWidget::ShadowEffectWidget(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	isPressed = false;
}
/*
 * When the widgets need to be repainted, Qt framework will call
 * this function automatically to update the invalid regions on the widgets
 * Users can force repaint by calling update() or repaint() directly.
 */
void ShadowEffectWidget::paintEvent(QPaintEvent* event)
{
	// providing a container for painting operations, enabling graphical shapes 
	// to be constructed and reused.
	QPainterPath path;  
	path.setFillRule(Qt::WindingFill);
	path.addRect(10, 10, this->width()-20, this->height()-20);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);  //antialiasing hint
	painter.fillPath(path, QBrush(Qt::white));

	QColor color(0, 0, 0, 50);
	for(int i=0; i<10; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
		color.setAlpha(150 - qSqrt(i)*50);
		painter.setPen(color);
		painter.drawPath(path);
	}
}

void ShadowEffectWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (isPressed)
	{
		QPoint point = event->globalPos();
		move(point-movePoint);
	}

}

void ShadowEffectWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		isPressed = true;
	}
	movePoint = event->globalPos()-pos();
}

void ShadowEffectWidget::mouseReleaseEvent(QMouseEvent *event)
{
	isPressed = false;
}

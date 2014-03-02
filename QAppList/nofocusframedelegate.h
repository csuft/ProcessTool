#ifndef NOFOCUSFRAMEDELEGATE_H
#define NOFOCUSFRAMEDELEGATE_H

#include <QStyledItemDelegate>
/*
 * This class is derived from QStyledItemDelegate and is used to control how to paint view items.
 * We reimplement the virtual function paint() to remove the dot-line frame when one item has focus.
 */
class NoFocusFrameDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit NoFocusFrameDelegate(QObject *parent = NULL);
	~NoFocusFrameDelegate(){}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
	NoFocusFrameDelegate& operator=(const NoFocusFrameDelegate& obj);
	NoFocusFrameDelegate(const NoFocusFrameDelegate& obj);
	
};

#endif // NOFOCUSFRAMEDELEGATE_H

#ifndef NOFOCUSFRAMEDELEGATE_H
#define NOFOCUSFRAMEDELEGATE_H

#include <QStyledItemDelegate>

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

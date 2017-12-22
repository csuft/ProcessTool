#include "applicationview.h"

ApplicationView::ApplicationView(QWidget *parent)
	: QTableView(parent)
{
	initialActions();
}

ApplicationView::~ApplicationView()
{

}
/*
 * Reimplemented the virtual function QWidget::contextMenuEvent() since we want to
 * create a context menu when the cursor hovered on the widget.
 */
void ApplicationView::contextMenuEvent(QContextMenuEvent* e)
{
	m_popmenu->clear();
	QPoint p = e->pos();
	QModelIndex index = this->indexAt(p);
	if (index.isValid())
	{
		m_popmenu->addAction(m_refresh);
		m_popmenu->addSeparator();
		m_popmenu->addAction(m_export);
		m_popmenu->addAction(m_detail);
		m_popmenu->exec(QCursor::pos());
		e->accept();  // stop the propagation of the context menu event.
	}
}

void ApplicationView::initialActions()
{
	m_popmenu = new QMenu(this);
	m_refresh = new QAction(QStringLiteral("Refresh"), this);
	m_export = new QAction(QStringLiteral("Export..."), this);
	m_detail = new QAction(QStringLiteral("Details..."), this);
}
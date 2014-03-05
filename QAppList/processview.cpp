#include "processview.h"

ProcessView::ProcessView(QWidget *parent)
	: QTableView(parent)
{
	initialActions();

	connect(m_refresh, SIGNAL(triggered()), this, SLOT(onRefreshActionTriggered()));
	connect(m_modules, SIGNAL(triggered()), this, SLOT(onModulesActionTriggered()));
	connect(m_threads, SIGNAL(triggered()), this, SLOT(onThreadsActionTriggered()));
	connect(m_location, SIGNAL(triggered()), this, SLOT(onLocationActionTriggered()));
}

ProcessView::~ProcessView()
{

}
/*
 * Reimplemented the virtual function QWidget::contextMenuEvent() since we want to
 * create a context menu when the cursor hovered on the widget.
 */
void ProcessView::contextMenuEvent(QContextMenuEvent* e)
{
	m_popmenu->clear();

	QPoint pt = e->pos();
	// retrieve the model index responding to the cursor position.
	QModelIndex index = this->indexAt(pt); 
	if (index.isValid())
	{
		m_popmenu->addAction(m_refresh);
		m_popmenu->addSeparator();
		m_popmenu->addAction(m_threads);
		m_popmenu->addAction(m_modules);
		m_popmenu->addAction(m_location);

		 // show the context menu
		m_popmenu->exec(QCursor::pos()); 
		e->accept();  // stop the propagation of the QContextMenuEvent.
	}

}

void ProcessView::initialActions()
{
	m_popmenu = new QMenu(this);
	m_refresh = new QAction(QStringLiteral("Refresh"), this);
	m_modules = new QAction(QStringLiteral("Modules..."), this);
	m_threads = new QAction(QStringLiteral("Theads..."), this);
	m_location = new QAction(QStringLiteral("Open path..."), this);
}

void ProcessView::onRefreshActionTriggered()
{
	// do nothing
	QMessageBox::information(this, "TEST", "TEST", QMessageBox::Ok);
}
void ProcessView::onThreadsActionTriggered()
{
	QMessageBox::information(this, "TEST", "TEST", QMessageBox::Ok);

}
void ProcessView::onModulesActionTriggered()
{
	// Alternative way: currentIndex().row()
	QModelIndexList indexList = this->selectionModel()->selectedRows();
	unsigned int pid = model()->data(model()->index(indexList.first().row(), 1)).toUInt();
	if (pid >= 0)
	{
		ModulesTableView mtv(pid);
		mtv.exec();
	}
}
void ProcessView::onLocationActionTriggered()
{
	QMessageBox::information(this, "TEST", "TEST", QMessageBox::Ok);

}
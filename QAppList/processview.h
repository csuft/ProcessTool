#ifndef PROCESSVIEW_H
#define PROCESSVIEW_H

#include <QTableView>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QModelIndex>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "modulestableview.h"

class ProcessView : public QTableView
{
	Q_OBJECT

public:
	explicit ProcessView(QWidget *parent = NULL);
	~ProcessView();

protected:
	void contextMenuEvent(QContextMenuEvent* e);

private slots:
	void onRefreshActionTriggered();
	void onThreadsActionTriggered();
	void onModulesActionTriggered();
	void onLocationActionTriggered();

private:
	ProcessView& operator=(const ProcessView& obj);
	ProcessView(const ProcessView& obj);

	void initialActions();
private:
	QMenu* m_popmenu;
	QAction* m_refresh;
	QAction* m_threads;
	QAction* m_modules;
	QAction* m_location;
};

#endif // PROCESSVIEW_H

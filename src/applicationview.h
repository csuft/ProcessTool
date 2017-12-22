#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

#include <QTableView>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>

class ApplicationView : public QTableView
{
	Q_OBJECT

public:
	explicit ApplicationView(QWidget *parent = NULL);
	~ApplicationView();

protected:
	void contextMenuEvent(QContextMenuEvent* e);

private:
	ApplicationView& operator=(const ApplicationView& obj);
	ApplicationView(const ApplicationView& obj);

	void initialActions();
private:
	QMenu* m_popmenu;
	QAction* m_refresh;
	QAction* m_export;
	QAction* m_detail;
};

#endif // APPLICATIONVIEW_H

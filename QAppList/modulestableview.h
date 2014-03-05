#ifndef MODULESTABLEVIEW_H
#define MODULESTABLEVIEW_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QFrame>
#include <QHeaderView>
#include <QAbstractItemView>
#include "custommodel.h"
#include "custompushbutton.h"
#include "shadoweffectwidget.h"
#include "titlebar.h"
#include "RetrieveHelper.h"
#include "nofocusframedelegate.h"

class ModulesTableView : public ShadowEffectWidget
{
	Q_OBJECT

public:
	explicit ModulesTableView(unsigned long pid, QWidget *parent = NULL);
	~ModulesTableView();

private:
	void createHeaders();
	void initialViewBehavior();
	void fillTableView();

protected:
	void paintEvent(QPaintEvent* event);

private slots:
	void onBtnClicked();

private:
	QTableView* m_view;
	CustomModel* m_model;
	QPushButton* m_OkBtn;
	CustomPushButton* m_closeBtn;
	QVBoxLayout* m_mainLayout;
	QHBoxLayout* m_topLayout;
	QHBoxLayout* m_bottomLayout;
	unsigned long m_pid;
	QLabel* m_title;
	QLabel* m_modCounts;
};

#endif // MODULESTABLEVIEW_H

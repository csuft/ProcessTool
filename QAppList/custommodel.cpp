#include "custommodel.h"

QVariant CustomModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::TextAlignmentRole)
	{
		return Qt::AlignCenter;
	}
	return QStandardItemModel::data(index, role);
}

CustomModel::~CustomModel()
{

}

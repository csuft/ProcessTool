#include "custommodel.h"

QVariant CustomModel::data(const QModelIndex& index, int role) const
{
	// align all cells center except the first column
	if (role == Qt::TextAlignmentRole && index.column() != 0)
	{
		return Qt::AlignCenter;
	}
	return QStandardItemModel::data(index, role);
}

CustomModel::~CustomModel()
{

}

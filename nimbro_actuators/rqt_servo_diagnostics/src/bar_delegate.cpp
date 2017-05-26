// Renders the load/torque field
// Author: Max Schwarz <max.schwarz@uni-bonn.de>

#include "bar_delegate.h"

#include <QPainter>

namespace rqt_servo_diagnostics
{

BarDelegate::BarDelegate(QObject* parent)
 : QStyledItemDelegate(parent)
 , m_min(0.0)
 , m_max(100.0)
{
}

BarDelegate::~BarDelegate()
{
}

void BarDelegate::setRange(double min, double max)
{
	m_min = min;
	m_max = max;
}

void BarDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	double alpha = std::min(1.0, std::max(0.0, (index.data(Qt::DisplayRole).toDouble() - m_min) / (m_max - m_min)));

	QRect rect = option.rect;
	rect.setWidth(alpha * rect.width());

	QColor color(
		alpha * 255,
		(1.0f - alpha) * 255,
		0
// 		(1.0f - alpha) * 255
	);

	painter->fillRect(rect, color);

	QStyledItemDelegate::paint(painter, option, index);
}

}

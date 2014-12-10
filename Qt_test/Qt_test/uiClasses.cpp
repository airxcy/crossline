#include "uiClasses.h"
void frameLabel::mousePressEvent(QMouseEvent * ev)
{
	if (ev->button()==Qt::LeftButton)
		emit leftpressed(ev->x(),ev->y());
	else if(ev->button()==Qt::RightButton)
		emit rightpressed(ev->x(),ev->y());
}
void frameLabel::mouseReleaseEvent(QMouseEvent * ev)
{
	if (ev->button()==Qt::LeftButton)
		emit leftreleased(ev->x(),ev->y());
}
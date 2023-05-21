#include "iabstractchess.h"

IAbstractChess::IAbstractChess(QObject *parent)
    : QObject(parent)
{

}

IAbstractChess::~IAbstractChess()
{

}

QPoint IAbstractChess::pos() const
{
    return m_pos;
}

void IAbstractChess::setPos(const QPoint &pos)
{
    m_pos = pos;
}

IChessCamp IAbstractChess::camp() const
{
    return m_camp;
}

void IAbstractChess::setCamp(const IChessCamp &camp)
{
    m_camp = camp;
}

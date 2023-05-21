#include "ielephant.h"

#include "iglobal.h"

IElephant::IElephant(QObject *parent)
    : IAbstractChess(parent)
{

}

IElephant::~IElephant()
{

}

IChessType IElephant::type()
{
    return IChessType::Elephant;
}

QList<IChessStep*> IElephant::allPossibleSteps()
{
    QList<IChessStep*> stepList;

    QPoint newPos;
    IChessStep* pStep = nullptr;
    //左上
    newPos = this->m_pos + QPoint(-2, -2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    //右上
    newPos = this->m_pos + QPoint(2, -2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    //右下
    newPos = this->m_pos + QPoint(2, 2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    //左下
    newPos = this->m_pos + QPoint(-2, 2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    return stepList;
}

bool IElephant::canMove(const QPoint &newPos)
{
    //新位置与自己位置不能形成田字
    qint32 xDistance = qAbs(this->m_pos.x() - newPos.x());
    qint32 yDistance = qAbs(this->m_pos.y() - newPos.y());
    if (xDistance != 2 || yDistance != 2)
        return false;

    //堵象眼
    QPoint midPos;
    if (this->m_pos.x() < newPos.x())
    {
        midPos = this->m_pos.y() < newPos.y() ? this->m_pos + QPoint(1, 1) : this->m_pos + QPoint(1, -1);
    }
    else //this->m_pos.x() > newPos.x()
    {
        midPos = this->m_pos.y() < newPos.y() ? this->m_pos + QPoint(-1, 1) : this->m_pos + QPoint(-1, -1);
    }
    if (IGlobal::global().findChess(midPos) != nullptr)
        return false;

    //可以移动到该位置
    return true;
}

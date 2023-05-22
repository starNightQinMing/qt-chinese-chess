#include "isoldier.h"

#include "iglobal.h"

ISoldier::ISoldier(QObject *parent)
    : IPiece(parent)
{

}

ISoldier::~ISoldier()
{

}

IPieceType ISoldier::type()
{
    return IPieceType::Soldier;
}

QList<IStep*> ISoldier::allPossibleSteps()
{
    QList<IStep*> stepList;

    QPoint newPos;
    IStep* pStep = nullptr;
    //上
    newPos = this->m_pos + QPoint(0, -1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    //下
    newPos = this->m_pos + QPoint(0, 1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    //左
    newPos = this->m_pos + QPoint(-1, 0);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    //右
    newPos = this->m_pos + QPoint(1, 0);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    return stepList;
}

bool ISoldier::canMove(const QPoint &newPos)
{
    //兵不能后退
    IPiece* pGeneray = IGlobal::global().findPiece(IPieceType::General, m_camp);
    qint32 maxY = this->m_pos.y();
    qint32 minY = pGeneray->pos().y();
    if (pGeneray->pos().y() > this->m_pos.y())
    {
        maxY = pGeneray->pos().y();
        minY = this->m_pos.y();
    }
    if (newPos.y() > minY && newPos.y() < maxY)
        return false;

    //没过河的兵只能前进
    if (IGlobal::global().pieceCampRange(this->m_camp).contains(this->m_pos)
            && this->m_pos.x() != newPos.x())
        return false;

    //新位置与自己位置不是相隔一列或一行
    qint32 xDistance = qAbs(this->m_pos.x() - newPos.x());
    qint32 yDistance = qAbs(this->m_pos.y() - newPos.y());
    if (!((xDistance == 1 && yDistance == 0) || (xDistance == 0 && yDistance == 1)))
        return false;

    //可以移动到该位置
    return true;
}

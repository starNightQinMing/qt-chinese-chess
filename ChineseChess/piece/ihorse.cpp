#include "ihorse.h"

#include "iglobal.h"

IHorse::IHorse(QObject *parent)
    : IPiece(parent)
{

}

IHorse::~IHorse()
{

}

IPieceType IHorse::type()
{
    return IPieceType::Horse;
}

QList<IStep*> IHorse::allPossibleSteps()
{
    QList<IStep*> stepList;

    QPoint newPos;
    IStep* pStep = nullptr;
    //上
    newPos = this->m_pos + QPoint(-1, -2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    newPos = this->m_pos + QPoint(1, -2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    //下
    newPos = this->m_pos + QPoint(-1, 2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    newPos = this->m_pos + QPoint(1, 2);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    //左
    newPos = this->m_pos + QPoint(-2, -1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    newPos = this->m_pos + QPoint(-2, 1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    //右
    newPos = this->m_pos + QPoint(2, -1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    newPos = this->m_pos + QPoint(2, 1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    return stepList;
}

bool IHorse::canMove(const QPoint &newPos)
{
    //新位置与自己位置不能形成田字
    qint32 xDistance = qAbs(this->m_pos.x() - newPos.x());
    qint32 yDistance = qAbs(this->m_pos.y() - newPos.y());
    if ((xDistance != 1 && xDistance != 2) || (yDistance != 1 && yDistance != 2))
        return false;

    //别马脚
    QPoint midPos;
    if (xDistance == 1)
    {
        midPos = this->m_pos.y() > newPos.y() ? this->m_pos + QPoint(0, -1) : this->m_pos + QPoint(0, 1);
    }
    else //xDistance == 2
    {
        midPos = this->m_pos.x() > newPos.x() ? this->m_pos + QPoint(-1, 0) : this->m_pos + QPoint(1, 0);
    }
    if (IGlobal::global().findPiece(midPos))
        return false;

    //可以移动到该位置
    return true;
}


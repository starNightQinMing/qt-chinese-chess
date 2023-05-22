#include "iguard.h"

#include "iglobal.h"

IGuard::IGuard(QObject *parent)
    : IPiece(parent)
{

}

IGuard::~IGuard()
{

}

IPieceType IGuard::type()
{
    return IPieceType::Guard;
}

QList<IStep*> IGuard::allPossibleSteps()
{
    QList<IStep*> stepList;

    QPoint newPos;
    IStep* pStep = nullptr;
    //左上
    newPos = this->m_pos + QPoint(-1, -1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    //右上
    newPos = this->m_pos + QPoint(1, -1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    //右下
    newPos = this->m_pos + QPoint(1, 1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    //左下
    newPos = this->m_pos + QPoint(-1, 1);
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
    {
        stepList.append(pStep);
    }

    return stepList;
}

bool IGuard::canMove(const QPoint &newPos)
{
    //新位置不在九宫格之内
    if (!IGlobal::global().pieceCampJiuGongGeRange(m_camp).contains(newPos))
        return false;

    //新位置与自己位置不能形成口字
    qint32 xDistance = qAbs(this->m_pos.x() - newPos.x());
    qint32 yDistance = qAbs(this->m_pos.y() - newPos.y());
    if (xDistance != 1 || yDistance != 1)
        return false;

    return true;
}

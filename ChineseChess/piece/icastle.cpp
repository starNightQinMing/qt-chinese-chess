#include "icastle.h"

#include "iglobal.h"

ICastle::ICastle(QObject *parent)
    : IPiece(parent)
{

}

ICastle::~ICastle()
{

}

IPieceType ICastle::type()
{
    return IPieceType::Castle;
}

QList<IStep*> ICastle::allPossibleSteps()
{
    QList<IStep*> stepList;

    QPoint newPos;
    IStep* pStep = nullptr;

    //减少判断次数，提高速度
    //上
    newPos = this->m_pos;
    for (qint32 y = this->y() - 1; y >= 0; y--)
    {
        newPos.setY(y);
        pStep = canMoveTo(newPos);
        if (pStep != nullptr)
            stepList.append(pStep);
        else
            break;
    }

    //下
    newPos = this->m_pos;
    for (qint32 y = this->y() + 1; y <= 9; y++)
    {
        newPos.setY(y);
        pStep = canMoveTo(newPos);
        if (pStep != nullptr)
            stepList.append(pStep);
        else
            break;
    }

    //左
    newPos = this->m_pos;
    for (qint32 x = this->x() - 1; x >= 0; x--)
    {
        newPos.setX(x);
        pStep = canMoveTo(newPos);
        if (pStep != nullptr)
            stepList.append(pStep);
        else
            break;
    }

    //右
    newPos = this->m_pos;
    for (qint32 x = this->x() + 1; x <= 8; x++)
    {
        newPos.setX(x);
        pStep = canMoveTo(newPos);
        if (pStep != nullptr)
            stepList.append(pStep);
        else
            break;
    }

    return stepList;
}

bool ICastle::canMove(const QPoint &newPos)
{
    //新位置与自己位置的行和列都不相同
    if (newPos.x() != this->m_pos.x() && newPos.y() != this->m_pos.y())
        return false;

    //中间有棋子
    QPoint midPos;
    if (newPos.x() == this->m_pos.x())
    {
        midPos.setX(this->m_pos.x());
        qint32 minY = this->m_pos.y() < newPos.y() ? this->m_pos.y() : newPos.y();
        qint32 maxY = this->m_pos.y() > newPos.y() ? this->m_pos.y() : newPos.y();
        for (qint32 y = minY + 1; y < maxY; y++)
        {
            midPos.setY(y);
            if (IGlobal::global().findPiece(midPos) != nullptr)
                return false;
        }
    }
    else
    {
        midPos.setY(this->m_pos.y());
        qint32 minX = this->m_pos.x() < newPos.x() ? this->m_pos.x() : newPos.x();
        qint32 maxX = this->m_pos.x() > newPos.x() ? this->m_pos.x() : newPos.x();
        for (qint32 x = minX + 1; x < maxX; x++)
        {
            midPos.setX(x);
            if (IGlobal::global().findPiece(midPos) != nullptr)
                return false;
        }
    }

    //可以移动到该位置
    return true;
}

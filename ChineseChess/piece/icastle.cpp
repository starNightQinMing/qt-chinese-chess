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
    //上下
    newPos = this->m_pos;
    for (qint32 y = 0;y <= 9; y++)
    {
        if (y == this->m_pos.y())
            continue;

        newPos.setY(y);
        pStep = canMoveTo(newPos);
        if (pStep != nullptr)
            stepList.append(pStep);
    }

    //左右
    newPos = this->m_pos;
    for (qint32 x = 0;x <= 8; x++)
    {
        if (x == this->m_pos.x())
            continue;

        newPos.setX(x);
        pStep = canMoveTo(newPos);
        if (pStep != nullptr)
            stepList.append(pStep);
    }

    return stepList;
}

bool ICastle::canMove(const QPoint &newPos)
{
    //新位置与自己位置的行和列都不相同
    if (newPos.x() != this->m_pos.x() && newPos.y() != this->m_pos.y())
        return false;

    //中间有棋子
    qint32 minX = this->m_pos.x();
    qint32 minY = this->m_pos.y();
    qint32 maxX = newPos.x();
    qint32 maxY = newPos.y();
    if (minX > maxX)
    {
        minX = newPos.x();
        maxX = this->m_pos.x();
    }
    if (minY > maxY)
    {
        minY = newPos.y();
        maxY = this->m_pos.y();
    }
    QPoint midPos;
    for (qint32 x = minX + 1; x < maxX; x++)
    {
        midPos.setX(x);
        for (qint32 y = minY + 1; y < maxY; y++)
        {
            midPos.setY(y);
            if (IGlobal::global().findPiece(midPos))
                return false;
        }
    }

    //可以移动到该位置
    return true;
}

#include "igeneral.h"

#include "iglobal.h"

IGeneral::IGeneral(QObject *parent)
    : IPiece(parent)
{

}

IGeneral::~IGeneral()
{

}

IPieceType IGeneral::type()
{
    return IPieceType::General;
}

QList<IStep*> IGeneral::allPossibleSteps()
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

    //将军碰面
    IPieceCamp enemy = IPieceCamp::Red;
    if (this->m_camp == enemy)
        enemy = IPieceCamp::Black;
    IPiece* pEnemyGeneral = IGlobal::global().findPiece(IPieceType::General, enemy);
    newPos = pEnemyGeneral->pos();
    pStep = canMoveTo(newPos);
    if (pStep != nullptr)
        stepList.append(pStep);

    return stepList;
}

bool IGeneral::canMove(const QPoint &newPos)
{
    //将军碰面
    IPieceCamp enemy = IPieceCamp::Red;
    if (this->m_camp == enemy)
        enemy = IPieceCamp::Black;
    IPiece* pEnemyGeneral = IGlobal::global().findPiece(IPieceType::General, enemy);
    if (newPos == pEnemyGeneral->pos() && pEnemyGeneral->pos().x() == this->pos().x())
    {
        qint32 minY = pEnemyGeneral->pos().y();
        qint32 maxY = this->m_pos.y();
        if (minY > maxY)
        {
            minY = this->m_pos.y();
            maxY = pEnemyGeneral->pos().y();
        }

        QPoint midPos = this->m_pos;
        for (qint32 y = minY + 1; y < maxY; y++)
        {
            midPos.setY(y);
            IPiece* pPiece = IGlobal::global().findPiece(midPos);
            if (pPiece != nullptr)
                return false;
        }

        return true;
    }

    //新位置不在九宫格之内
    if (!IGlobal::global().pieceCampJiuGongGeRange(m_camp).contains(newPos))
        return false;

    //新位置与自己位置不是相隔一列或一行
    qint32 xDistance = qAbs(this->m_pos.x() - newPos.x());
    qint32 yDistance = qAbs(this->m_pos.y() - newPos.y());
    if (!((xDistance == 1 && yDistance == 0) || (xDistance == 0 && yDistance == 1)))
        return false;

    return true;
}

#include "iabstractchess.h"

#include "iglobal.h"

IAbstractChess::IAbstractChess(QObject *parent)
    : QObject(parent)
{

}

IAbstractChess::~IAbstractChess()
{

}

QString IAbstractChess::name() const
{
    return m_name;
}

void IAbstractChess::setName(const QString &name)
{
    m_name = name;
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

QSize IAbstractChess::size() const
{
    return m_size;
}

void IAbstractChess::setSize(const QSize &size)
{
    m_size = size;
}

bool IAbstractChess::isDead() const
{
    return m_isDead;
}

void IAbstractChess::setIsDead(bool isDead)
{
    m_isDead = isDead;
}

IChessStep* IAbstractChess::canMoveTo(const QPoint &newPos)
{
    //1，新位置不在棋盘范围之内
    if (!IGlobal::global().bordRange().contains(newPos))
        return nullptr;

    //2，新位置是原来的位置
    if (newPos == this->m_pos)
        return nullptr;

    //3，新位置有己方棋子
    IAbstractChess* pChess = IGlobal::global().findChess(newPos);
    if (pChess != nullptr && pChess->camp() == this->m_camp && !(pChess->m_isDead))
        return nullptr;

    //其他条件由子类去判断
    if (!canMove(newPos))
        return nullptr;

    return this->createStep(newPos);//如果可以移动则反馈步记录
}

void IAbstractChess::moveTo(const QPoint &pos)
{
    m_pos = pos;
}

IChessStep *IAbstractChess::createStep(const QPoint &newPos)
{
    IChessStep* pStep = new IChessStep();
    if (pStep == nullptr)
        return nullptr;

    IAbstractChess* pKillChess = IGlobal::global().findChess(newPos);
    pStep->setOriginalPos(this->m_pos);
    pStep->setNewPos(newPos);
    pStep->setCurrentChess(this);
    pStep->setKillChess(pKillChess);

    return pStep;
}


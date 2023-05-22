#include "ipiece.h"

#include "iglobal.h"

IPiece::IPiece(QObject *parent)
    : QObject(parent)
{

}

IPiece::~IPiece()
{

}

QString IPiece::name() const
{
    return m_name;
}

void IPiece::setName(const QString &name)
{
    m_name = name;
}

QPoint IPiece::pos() const
{
    return m_pos;
}

void IPiece::setPos(const QPoint &pos)
{
    m_pos = pos;
}

IPieceCamp IPiece::camp() const
{
    return m_camp;
}

void IPiece::setCamp(const IPieceCamp &camp)
{
    m_camp = camp;
}

QSize IPiece::size() const
{
    return m_size;
}

void IPiece::setSize(const QSize &size)
{
    m_size = size;
}

bool IPiece::isDead() const
{
    return m_isDead;
}

void IPiece::setIsDead(bool isDead)
{
    m_isDead = isDead;
}

IStep* IPiece::canMoveTo(const QPoint &newPos)
{
    //1，新位置不在棋盘范围之内
    if (!IGlobal::global().bordRange().contains(newPos))
        return nullptr;

    //2，新位置是原来的位置
    if (newPos == this->m_pos)
        return nullptr;

    //3，新位置有己方棋子
    IPiece* pPiece = IGlobal::global().findPiece(newPos);
    if (pPiece != nullptr && pPiece->camp() == this->m_camp && !(pPiece->m_isDead))
        return nullptr;

    //其他条件由子类去判断
    if (!canMove(newPos))
        return nullptr;

    return this->createStep(newPos);//如果可以移动则反馈步记录
}

void IPiece::moveTo(const QPoint &pos)
{
    m_pos = pos;
}

IStep *IPiece::createStep(const QPoint &newPos)
{
    IStep* pStep = new IStep();
    if (pStep == nullptr)
        return nullptr;

    IPiece* pKillPiece = IGlobal::global().findPiece(newPos);
    pStep->setOriginalPos(this->m_pos);
    pStep->setNewPos(newPos);
    pStep->setCurrentPiece(this);
    pStep->setKillPiece(pKillPiece);

    return pStep;
}


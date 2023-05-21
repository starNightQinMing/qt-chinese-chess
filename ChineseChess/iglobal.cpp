#include "iglobal.h"

#include "chess/ichessfactory.h"

IGlobal &IGlobal::global()
{
    static IGlobal global;
    return global;
}

void IGlobal::reset()
{
    //位置回到初始位置即可
    QList<QPoint> posList = m_blackPosList + m_redPosList;
    qint32 count = posList.count();
    for (qint32 index = 0;index < count;index++)
    {
        m_chessList[index]->setIsDead(false);
        m_chessList[index]->setPos(posList[index]);
    }
}

QList<IAbstractChess *> IGlobal::chessList() const
{
    return m_chessList;
}

IAbstractChess *IGlobal::findChess(const IChessType &type, const IChessCamp &camp) const
{
    for (IAbstractChess* pChess : m_chessList)
    {
        if (!pChess->isDead() && pChess->type() == type && pChess->camp() == camp)
            return pChess;
    }

    return nullptr;
}

IAbstractChess *IGlobal::findChess(const QPoint &pos) const
{
    for (IAbstractChess* pChess : m_chessList)
    {
        if (!pChess->isDead() && pChess->pos() == pos)
            return pChess;
    }

    return nullptr;
}

QRect IGlobal::bordRange() const
{
    return QRect(0, 0, 9, 10);
}

QRect IGlobal::chessCampRange(const IChessCamp &camp) const
{
    IAbstractChess* pKing = findChess(IChessType::General, camp);
    if (pKing == nullptr)
        return QRect();

    return (pKing->pos().y() < 4) ? QRect(0, 0, 9, 5) : QRect(0, 5, 9, 5);
}

QRect IGlobal::chessCampJiuGongGeRange(const IChessCamp &camp) const
{
    IAbstractChess* pKing = findChess(IChessType::General, camp);
    if (pKing == nullptr)
        return QRect();

    return (pKing->pos().y() < 4) ? QRect(3, 0, 3, 3) : QRect(3, 7, 3, 3);
}

IGlobal::IGlobal(QObject *parent)
    : QObject(parent)
{
    initChess();
    initPos();
    reset();
}

void IGlobal::initPos()
{
    //黑棋位置
    QList<QPoint> blackPositionList;
    blackPositionList << QPoint(0, 3) << QPoint(2, 3) << QPoint(4, 3) << QPoint(6, 3) << QPoint(8, 3);
    blackPositionList << QPoint(3, 0) << QPoint(5, 0) << QPoint(4, 0) << QPoint(2, 0) << QPoint(6, 0);
    blackPositionList << QPoint(1, 0) << QPoint(7, 0) << QPoint(1, 2) << QPoint(7, 2) << QPoint(0, 0) << QPoint(8, 0);
    m_blackPosList = blackPositionList;

    //红棋位置
    QList<QPoint> redPositionList;
    redPositionList << QPoint(0, 6) << QPoint(2, 6) << QPoint(4, 6) << QPoint(6, 6) << QPoint(8, 6);
    redPositionList << QPoint(3, 9) << QPoint(5, 9) << QPoint(4, 9) << QPoint(2, 0) << QPoint(6, 9);
    redPositionList << QPoint(1, 9) << QPoint(7, 9) << QPoint(1, 7) << QPoint(7, 7) << QPoint(0, 9) << QPoint(8, 9);
    m_redPosList = redPositionList;
}

void IGlobal::initChess()
{
    //类型
    QList<IChessType> typeList;
    typeList << IChessType::Soldier << IChessType::Soldier << IChessType::Soldier
             << IChessType::Soldier << IChessType::Soldier;
    typeList << IChessType::Guard << IChessType::Guard << IChessType::General
             << IChessType::Elephant << IChessType::Elephant;
    typeList << IChessType::Horse << IChessType::Horse << IChessType::Cannon
             << IChessType::Cannon << IChessType::Castle << IChessType::Castle;

    qint32 count = 16;
    //黑棋
    //名称
    QStringList blackNameList;
    blackNameList << "卒" << "卒" << "卒" << "卒" << "卒";
    blackNameList << "士" << "士" << "將" << "象" << "象";
    blackNameList << "馬" << "馬" << "炮" << "炮" << "車" << "車";

    //创建棋子，添加到数组中
    IChessCamp blackCamp = IChessCamp::Black;
    for (qint32 index = 0; index < count; index++)
    {
        IAbstractChess* pChess = IChessFactory::createChess(typeList[index]);
        pChess->setCamp(blackCamp);
        pChess->setName(blackNameList[index]);
        m_chessList.append(pChess);
    }

    //红棋
    //名称
    QStringList redNameList;
    blackNameList << "兵" << "兵" << "兵" << "兵" << "兵";
    blackNameList << "仕" << "仕" << "帥" << "相" << "相";
    blackNameList << "馬" << "馬" << "炮" << "炮" << "車" << "車";

    //创建棋子，添加到数组中
    IChessCamp redCamp = IChessCamp::Red;
    for (qint32 index = 0; index < count; index++)
    {
        IAbstractChess* pChess = IChessFactory::createChess(typeList[index]);
        pChess->setCamp(redCamp);
        pChess->setName(redNameList[index]);
        m_chessList.append(pChess);
    }
}

#include "iglobal.h"

#include "piece/ipiecefactory.h"

#include <QtCore/qdebug.h>

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
        m_pieceList[index]->setIsDead(false);//所有状态都是未死亡
        m_pieceList[index]->setPos(posList[index]);
    }
}

QList<IPiece *> IGlobal::pieceList() const
{
    return m_pieceList;
}

quint8 IGlobal::campBeginIndex(const IPieceCamp &camp) const
{
    qint32 index = 0;
    if (m_pieceList[index]->camp() == camp)
        return index;

    return index + 16;
}

quint8 IGlobal::campEndIndex(const IPieceCamp &camp) const
{
    qint32 index = 15;
    if (m_pieceList[index]->camp() == camp)
        return index;

    return index + 16;
}

IPiece *IGlobal::findPiece(const IPieceType &type, const IPieceCamp &camp) const
{
    for (IPiece* pPiece : m_pieceList)
    {
        if (!pPiece->isDead() && pPiece->type() == type && pPiece->camp() == camp)
            return pPiece;
    }

    return nullptr;
}

IPiece *IGlobal::findPiece(const QPoint &pos) const
{
    for (IPiece* pPiece : m_pieceList)
    {
        if (!pPiece->isDead() && pPiece->pos() == pos)
            return pPiece;
    }

    return nullptr;
}

QRect IGlobal::bordRange() const
{
    return QRect(0, 0, 9, 10);
}

QRect IGlobal::pieceCampRange(const IPieceCamp &camp) const
{
    IPiece* pKing = findPiece(IPieceType::General, camp);
    if (pKing == nullptr)
        return QRect();

    return (pKing->pos().y() < 4) ? QRect(0, 0, 9, 5) : QRect(0, 5, 9, 5);
}

QRect IGlobal::pieceCampJiuGongGeRange(const IPieceCamp &camp) const
{
    IPiece* pKing = findPiece(IPieceType::General, camp);
    if (pKing == nullptr)
        return QRect();

    return (pKing->pos().y() < 4) ? QRect(3, 0, 3, 3) : QRect(3, 7, 3, 3);
}

IGlobal::IGlobal(QObject *parent)
    : QObject(parent)
{
    initPiece();
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
    redPositionList << QPoint(3, 9) << QPoint(5, 9) << QPoint(4, 9) << QPoint(2, 9) << QPoint(6, 9);
    redPositionList << QPoint(1, 9) << QPoint(7, 9) << QPoint(1, 7) << QPoint(7, 7) << QPoint(0, 9) << QPoint(8, 9);
    m_redPosList = redPositionList;
}

void IGlobal::initPiece()
{
    //类型
    QList<IPieceType> typeList;
    typeList << IPieceType::Soldier << IPieceType::Soldier << IPieceType::Soldier
             << IPieceType::Soldier << IPieceType::Soldier;
    typeList << IPieceType::Guard << IPieceType::Guard << IPieceType::General
             << IPieceType::Elephant << IPieceType::Elephant;
    typeList << IPieceType::Horse << IPieceType::Horse << IPieceType::Cannon
             << IPieceType::Cannon << IPieceType::Castle << IPieceType::Castle;

    qint32 count = 16;
    //黑棋
    //名称
    QStringList blackNameList;
    blackNameList << "卒" << "卒" << "卒" << "卒" << "卒";
    blackNameList << "士" << "士" << "將" << "象" << "象";
    blackNameList << "馬" << "馬" << "炮" << "炮" << "車" << "車";

    //创建棋子，添加到数组中
    IPieceCamp blackCamp = IPieceCamp::Black;
    for (qint32 index = 0; index < count; index++)
    {
        IPiece* pPiece = IPieceFactory::createPiece(typeList[index]);
        pPiece->setCamp(blackCamp);
        pPiece->setName(blackNameList[index]);
        m_pieceList.append(pPiece);
    }

    //红棋
    //名称
    QStringList redNameList;
    redNameList << "兵" << "兵" << "兵" << "兵" << "兵";
    redNameList << "仕" << "仕" << "帥" << "相" << "相";
    redNameList << "馬" << "馬" << "炮" << "炮" << "車" << "車";

    //创建棋子，添加到数组中
    IPieceCamp redCamp = IPieceCamp::Red;
    for (qint32 index = 0; index < count; index++)
    {
        IPiece* pPiece = IPieceFactory::createPiece(typeList[index]);
        pPiece->setCamp(redCamp);
        pPiece->setName(redNameList[index]);
        m_pieceList.append(pPiece);
    }
}

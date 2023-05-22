#ifndef IPIECE_H
#define IPIECE_H

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include <QtCore/qsize.h>

#include <QtGui/qpaintdevice.h>
#include <QtGui/qpainter.h>

#include "istep.h"

// 定义棋子类型
enum class IPieceType {
    Empty = 0,  //未知
    General,       //将/帅
    Guard,      //士
    Elephant,   //象
    Horse,      //马
    Castle,        //车
    Cannon,     //炮
    Soldier     //兵/卒
};

//定义棋子阵营
enum class IPieceCamp {
    None = 0,
    Black,
    Red
};

//定义棋子
class IPiece : public QObject
{
    Q_OBJECT
public:
    explicit IPiece(QObject *parent = nullptr);
    virtual ~IPiece();

    QString name() const;
    void setName(const QString &name);

    QPoint pos() const;
    void setPos(const QPoint &pos);

    IPieceCamp camp() const;
    void setCamp(const IPieceCamp &camp);

    QSize size() const;
    void setSize(const QSize &size);

    bool isDead() const;
    void setIsDead(bool isDead);

    IStep* canMoveTo(const QPoint& newPos);//判断是否可以移动到新位置
    void moveTo(const QPoint& pos);

    virtual IPieceType type() = 0;//返回类型由子类实现
    virtual QList<IStep*> allPossibleSteps() = 0;//返回所有可能的步骤

protected:
    IStep* createStep(const QPoint& newPos);

    virtual bool canMove(const QPoint& newPos) = 0;

signals:
    void posChanged();
    void sizeChanged();

protected:
    QString m_name;
    QPoint m_pos;
    QSize m_size;
    IPieceCamp m_camp;
    bool m_isDead;
};

#endif // IPIECE_H

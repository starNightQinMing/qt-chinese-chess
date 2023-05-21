#ifndef IABSTRACTCHESS_H
#define IABSTRACTCHESS_H

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include <QtCore/qsize.h>

#include <QtGui/qpaintdevice.h>
#include <QtGui/qpainter.h>

#include "ichessstep.h"

// 定义棋子类型
enum class IChessType {
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
enum class IChessCamp {
    None = 0,
    Black,
    Red
};

//定义棋子
class IAbstractChess : public QObject
{
    Q_OBJECT
public:
    explicit IAbstractChess(QObject *parent = nullptr);
    virtual ~IAbstractChess();

    QString name() const;
    void setName(const QString &name);

    QPoint pos() const;
    void setPos(const QPoint &pos);

    IChessCamp camp() const;
    void setCamp(const IChessCamp &camp);

    QSize size() const;
    void setSize(const QSize &size);

    bool isDead() const;
    void setIsDead(bool isDead);

    IChessStep* canMoveTo(const QPoint& newPos);//判断是否可以移动到新位置
    void moveTo(const QPoint& pos);

    virtual IChessType type() = 0;//返回类型由子类实现
    virtual QList<IChessStep*> allPossibleSteps() = 0;//返回所有可能的步骤

protected:
    IChessStep* createStep(const QPoint& newPos);

    virtual bool canMove(const QPoint& newPos) = 0;

signals:
    void posChanged();
    void sizeChanged();

protected:
    QString m_name;
    QPoint m_pos;
    QSize m_size;
    IChessCamp m_camp;
    bool m_isDead;
};

#endif // IABSTRACTCHESS_H

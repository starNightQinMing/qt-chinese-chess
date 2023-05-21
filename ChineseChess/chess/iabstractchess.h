#ifndef IABSTRACTCHESS_H
#define IABSTRACTCHESS_H

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include <QtCore/qsize.h>

// 定义棋子类型
enum class IChessType {
    Empty = 0,  //未知
    King,       //将/帅
    Guard,      //士
    Elephant,   //象
    Horse,      //马
    Car,        //车
    Cannon,     //炮
    Soldier     //兵/卒
};

//定义棋子阵营
enum class IChessCamp {
    None = 0,
    Black,
    Red
};

class IAbstractChess;
class IChessStep : QObject
{
public:
    explicit IChessStep(QObject* parent = nullptr);

private:
    IAbstractChess* m_pCurrentChess;
    IAbstractChess* m_pNextChess;
};

//定义棋子
class IAbstractChess : public QObject
{
    Q_OBJECT
public:
    explicit IAbstractChess(QObject *parent = nullptr);
    virtual ~IAbstractChess();

    QPoint pos() const;
    void setPos(const QPoint &pos);

    IChessCamp camp() const;
    void setCamp(const IChessCamp &camp);

    virtual IChessType type() = 0;//返回类型由子类实现
    //virtual QList<IChessStep> allCanMoveStep();

signals:
    void posChanged();
    void sizeChanged();

protected:
    QPoint m_pos;
    IChessCamp m_camp;
};

#endif // IABSTRACTCHESS_H

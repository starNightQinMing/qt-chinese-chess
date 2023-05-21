#ifndef ELEPHANT_H
#define ELEPHANT_H

#include "iabstractchess.h"

class IElephant : public IAbstractChess
{
    Q_OBJECT
public:
    explicit IElephant(QObject *parent = nullptr);
    virtual ~IElephant();

    virtual IChessType type() override;
    virtual QList<IChessStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ELEPHANT_H

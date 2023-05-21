#ifndef IGUARD_H
#define IGUARD_H

#include "iabstractchess.h"

class IGuard : public IAbstractChess
{
    Q_OBJECT
public:
    explicit IGuard(QObject *parent = nullptr);
    virtual ~IGuard();

    virtual IChessType type() override;
    virtual QList<IChessStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // IGUARD_H

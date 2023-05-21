#ifndef ISOLDIER_H
#define ISOLDIER_H

#include "iabstractchess.h"

class ISoldier : public IAbstractChess
{
    Q_OBJECT
public:
    explicit ISoldier(QObject *parent = nullptr);
    virtual ~ISoldier();

    virtual IChessType type() override;
    virtual QList<IChessStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ISOLDIER_H

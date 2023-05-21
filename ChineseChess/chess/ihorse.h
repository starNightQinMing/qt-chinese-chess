#ifndef IHORSE_H
#define IHORSE_H

#include "iabstractchess.h"

class IHorse : public IAbstractChess
{
    Q_OBJECT
public:
    explicit IHorse(QObject *parent = nullptr);
    virtual ~IHorse();

    virtual IChessType type() override;
    virtual QList<IChessStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // IHORSE_H

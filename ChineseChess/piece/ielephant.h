#ifndef ELEPHANT_H
#define ELEPHANT_H

#include "ipiece.h"

class IElephant : public IPiece
{
    Q_OBJECT
public:
    explicit IElephant(QObject *parent = nullptr);
    virtual ~IElephant();

    virtual IPieceType type() override;
    virtual QList<IStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ELEPHANT_H

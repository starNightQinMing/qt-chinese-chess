#ifndef ICAR_H
#define ICAR_H

#include "ipiece.h"

class ICastle : public IPiece
{
    Q_OBJECT
public:
    explicit ICastle(QObject *parent = nullptr);
    virtual ~ICastle();

    virtual IPieceType type() override;
    virtual QList<IStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ICAR_H

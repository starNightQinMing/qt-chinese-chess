#ifndef IPIECEFACTORY_H
#define IPIECEFACTORY_H

#include <QtCore/qobject.h>

#include "icannon.h"
#include "icastle.h"
#include "ielephant.h"
#include "igeneral.h"
#include "iguard.h"
#include "ihorse.h"
#include "isoldier.h"

class IPieceFactory : public QObject
{
    Q_OBJECT
public:
    explicit IPieceFactory(QObject *parent = nullptr);

    static IPiece* createPiece(const IPieceType& type);
    static IPiece* createCannon();
    static IPiece* createCastle();
    static IPiece* createElephant();
    static IPiece* createGeneral();
    static IPiece* createGuard();
    static IPiece* createHorse();
    static IPiece* createSoldier();
};

#endif // IPIECEFACTORY_H

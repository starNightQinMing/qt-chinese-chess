#ifndef ICHESSFACTORY_H
#define ICHESSFACTORY_H

#include <QtCore/qobject.h>

#include "icannon.h"
#include "icastle.h"
#include "ielephant.h"
#include "igeneral.h"
#include "iguard.h"
#include "ihorse.h"
#include "isoldier.h"

class IChessFactory : public QObject
{
    Q_OBJECT
public:
    explicit IChessFactory(QObject *parent = nullptr);

    static IAbstractChess* createChess(const IChessType& type);
    static IAbstractChess* createCannon();
    static IAbstractChess* createCastle();
    static IAbstractChess* createElephant();
    static IAbstractChess* createGeneral();
    static IAbstractChess* createGuard();
    static IAbstractChess* createHorse();
    static IAbstractChess* createSoldier();
};

#endif // ICHESSFACTORY_H

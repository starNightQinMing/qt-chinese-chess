#ifndef ICHESSPLAYER_H
#define ICHESSPLAYER_H

#include <QtCore/qobject.h>

#include "piece/ipiece.h"

class IChessPlayer : public QObject
{
    Q_OBJECT
public:
    explicit IChessPlayer(QObject *parent = nullptr);

signals:
    void moved(IStep* pStep);

protected:
    IPieceCamp m_camp;
    QList<IStep*> m_stepList;

};

#endif // ICHESSPLAYER_H

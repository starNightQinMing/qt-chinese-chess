#ifndef ISEARCHENGINE_H
#define ISEARCHENGINE_H

#include "piece/ipiece.h"

constexpr qint32 MAXIMUM_VALUE = 2520;
constexpr qint32 MINIMUM_VALUE = -2520;
constexpr qint32 DEFAULT_SEARCH_DEPTH = 4;

class ISearchEngine : public QObject
{
    Q_OBJECT
public:
    ISearchEngine(QObject *parent = Q_NULLPTR);
    virtual ~ISearchEngine();

    void setSearchDepth(const qint32& searchDepth);
    qint32 searchDepth() const;

    void setCamp(IPieceCamp camp);
    IPieceCamp camp() const;

    void setBestStep(IStep* pBestIStep);
    IStep* bestStep();

    void setOperatePieceList(QList<IPiece*>& operatePieceieceList);
    QList<IPiece*>& operatePieceList();

    void setStepCount(const quint64& count);
    quint64 stepCount() const;

    void setFirstStep(bool firstStep);
    bool firstStep() const;

    bool fightOver();
    IStep* bestStep(const QList<IPiece*>& pieceList);
    qint32 calScore(IPieceCamp camp);

    void fakeMove(IStep* pIStep);
    void unFakeMove(IStep* pIStep);

    IPieceCamp nextCamp(const IPieceCamp& currentCamp);

    bool checkEnemyGeneral();
    bool checkSelfGeneral();
    bool checkCampGeneral(const IPieceCamp& camp);
    bool checkGeneral(const QPoint& enemyGeneralPos, quint8 beginIndex, quint8 endIndex, bool need = false);
    IStep* escapeCheck(QList<IPiece*>& pieceList);

    void getFirstStep();

protected:
    virtual void search() = 0;

signals:
    void searchEnd();

public slots:
    void startSearch();

protected:
    qint32 m_searchDepth;
    IPieceCamp m_camp;
    IStep* m_pBestStep;
    IStep* m_pCheckGeneralStep;
    QList<IPiece*> m_operatePieceList;
    quint64 m_stepCount;
    bool m_firstStep;
};

#endif //ISEARCHENGINE_H

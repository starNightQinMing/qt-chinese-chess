#ifndef IBOARDWIDGET_H
#define IBOARDWIDGET_H

#include <QtGui/qpainter.h>

#include <QtWidgets/qwidget.h>

class IPiece;
class IStep;

class IBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IBoardWidget(QWidget *parent = nullptr);

    IPiece *currentPiece() const;
    void setCurrentPiece(IPiece *pCurrentPiece);

    IStep *currentStep() const;
    void setCurrentStep(IStep *pCurrentStep);

    bool canUpdate() const;
    void setCanUpdate(const bool& canUpdate);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    void drawGrid(QPainter& painter);
    void drawDiagonal(QPainter& painter);
    void drawAllRightAngle(QPainter& painter);
    void drawRightAngle(QPainter& painter, qint32 rightX, qint32 rightY);
    void drawRiverCourse(QPainter& painter);
    void drawHighlight(QPainter& painter, const QPoint& pos);
    void drawPiece(QPainter& painter);

    virtual void mousePressEvent(QMouseEvent* event) override;

signals:
    void posClicked(const QPoint& pos);

private:
    qint32 m_x;
    qint32 m_y;
    qint32 m_space;
    qint32 m_width;
    qint32 m_height;
    IPiece* m_pCurrentPiece;
    IStep* m_pCurrentStep;
    bool m_canUpdate;
};

#endif // IBOARDWIDGET_H

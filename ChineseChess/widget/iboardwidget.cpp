#include "iboardwidget.h"

#include <QtGui/qevent.h>

#include "iglobal.h"

IBoardWidget::IBoardWidget(QWidget *parent)
    : QWidget(parent)
    , m_pCurrentPiece(nullptr)
    , m_pCurrentStep(nullptr)
    , m_canUpdate(true)
{
    m_x = 60;
    m_y = 60;
    m_space = 80;
    m_width = 8 * m_space;
    m_height = 9 * m_space;
    //this->setMinimumSize(m_width + 10, m_height + 20);
}

IStep *IBoardWidget::currentStep() const
{
    return m_pCurrentStep;
}

void IBoardWidget::setCurrentStep(IStep *pCurrentStep)
{
    m_pCurrentStep = pCurrentStep;
}

bool IBoardWidget::canUpdate() const
{
    return m_canUpdate;
}

void IBoardWidget::setCanUpdate(const bool &canUpdate)
{
    m_canUpdate = canUpdate;
}

IPiece *IBoardWidget::currentPiece() const
{
    return m_pCurrentPiece;
}

void IBoardWidget::setCurrentPiece(IPiece *pCurrentPiece)
{
    m_pCurrentPiece = pCurrentPiece;
}

void IBoardWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawGrid(painter);              //画网格
    drawDiagonal(painter);          //画斜线
    drawAllRightAngle(painter);     //画直角
    drawRiverCourse(painter);       //画河道

    if (m_pCurrentStep != Q_NULLPTR)
    {
        drawHighlight(painter, m_pCurrentStep->originalPos());
        drawHighlight(painter, m_pCurrentStep->newPos());
    }
    else
    {
        if (m_pCurrentPiece != Q_NULLPTR)
            drawHighlight(painter, m_pCurrentPiece->pos());
    }

    drawPiece(painter);
}

void IBoardWidget::drawGrid(QPainter& painter)
{
    QPen pen;
    pen.setWidth(6);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    qint32 baseLength = 50;
    qint32 fillX = m_x - baseLength;
    qint32 fillY = m_y - baseLength;
    qint32 fillWidth = m_width + baseLength * 2;
    qint32 fillHeight = m_height + baseLength * 2;
    painter.fillRect(fillX, fillY, fillWidth, fillHeight, QColor(226, 196, 143));
    //painter.drawRect(fillX, fillY, fillWidth, fillHeight);

    pen.setWidth(4);
    qint32 outLength = 10;
    qint32 outX = m_x - outLength;
    qint32 outY = m_y - outLength;
    qint32 outWidth = m_width + outLength * 2;
    qint32 outHeight = m_height + outLength * 2;
    painter.drawRect(outX, outY, outWidth, outHeight);

    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(m_x, m_y, m_width, m_height);

    //横向
    for (qint32 index = 1; index < 10; index++)
    {
        QPoint startPos(m_x, m_y + m_space * index);
        QPoint endPos(m_x + m_width, m_y + m_space * index);
        painter.drawLine(startPos, endPos);
    }

    //纵向
    qint32 upBaseY = m_y;
    qint32 bottomBaseY = m_y + m_height;
    for (qint32 index = 1; index < 9; index++)
    {
        qint32 x = m_x + index * m_space;

        //上
        QPoint upStartPos(x, upBaseY);
        QPoint upEndPos(x, upBaseY + m_space * 4);
        painter.drawLine(upStartPos, upEndPos);

        //下
        QPoint bottomStartPos(x, bottomBaseY);
        QPoint bottomEndPos(x, bottomBaseY - m_space * 4);
        painter.drawLine(bottomStartPos, bottomEndPos);
    }
}

void IBoardWidget::drawDiagonal(QPainter& painter)
{
    qint32 sx = m_x + m_space * 3;
    qint32 sy = m_y;

    qint32 ex = sx + m_space * 2;
    qint32 ey = m_y + m_space * 2;

    painter.drawLine(sx, sy, ex, ey);

    qint32 sx1 = m_x + m_space * 3;
    qint32 sy1 = m_y + m_space * 2;

    qint32 ex1 = sx1 + m_space * 2;
    qint32 ey1 = m_y;

    painter.drawLine(sx1, sy1, ex1, ey1);

    qint32 sx3 = m_x + m_space * 3;
    qint32 sy3 = m_y + m_height;

    qint32 ex3 = sx3 + m_space * 2;
    qint32 ey3 = sy3 - m_space * 2;

    painter.drawLine(sx3, sy3, ex3, ey3);

    qint32 sx4 = m_x + m_space * 3;
    qint32 sy4 = m_y + m_height - m_space * 2;

    qint32 ex4 = sx4 + m_space * 2;
    qint32 ey4 = sy4 + m_space * 2;

    painter.drawLine(sx4, sy4, ex4, ey4);
}

void IBoardWidget::drawAllRightAngle(QPainter& painter)
{
    qint32 leftCannonX = m_x + 1 * m_space;
    qint32 rightCannonX = m_x + 7 * m_space;

    qint32 blackCannonY = m_y + 2 * m_space;
    drawRightAngle(painter, leftCannonX, blackCannonY);
    drawRightAngle(painter, rightCannonX, blackCannonY);

    qint32 redCannonY = m_y + 7 * m_space;
    drawRightAngle(painter, leftCannonX, redCannonY);
    drawRightAngle(painter, rightCannonX, redCannonY);

    //0 2 4 6 8
    qint32 rightBlackSoldierY = m_x + 3 * m_space;
    qint32 rightRedSoldierY = m_x + 6 * m_space;
    for (qint32 x = 0; x <= 8; x += 2)
    {
        qint32 rightX = m_x + x * m_space;
        drawRightAngle(painter, rightX, rightBlackSoldierY);
        drawRightAngle(painter, rightX, rightRedSoldierY);
    }
}

void IBoardWidget::drawRightAngle(QPainter& painter, qint32 rightX, qint32 rightY)
{
    qint32 offset = 5;
    qint32 length = 15;

    //左上
    qint32 topLeftX = rightX - offset;
    if (topLeftX >= m_x)
    {
        qint32 topLeftY = rightY - offset;
        painter.drawLine(topLeftX, topLeftY, topLeftX - length, topLeftY);
        painter.drawLine(topLeftX, topLeftY, topLeftX, topLeftY - length);
    }

    //右上
    qint32 rightTopX = rightX + offset;
    if (rightTopX <= m_x + m_space * 8)
    {
        qint32 rightTopY = rightY - offset;
        painter.drawLine(rightTopX, rightTopY, rightTopX + length, rightTopY);
        painter.drawLine(rightTopX, rightTopY, rightTopX, rightTopY - length);
    }

    //右下
    qint32 rightBottomX = rightX + offset;
    if (rightBottomX <= m_x + m_space * 8)
    {
        qint32 rightBottomY = rightY + offset;
        painter.drawLine(rightBottomX, rightBottomY, rightBottomX + length, rightBottomY);
        painter.drawLine(rightBottomX, rightBottomY, rightBottomX, rightBottomY + length);
    }

    //左下
    qint32 leftBottomX = rightX - offset;
    if (leftBottomX >= m_x)
    {
        qint32 leftBottomY = rightY + offset;
        painter.drawLine(leftBottomX, leftBottomY, leftBottomX - length, leftBottomY);
        painter.drawLine(leftBottomX, leftBottomY, leftBottomX, leftBottomY + length);
    }
}

void IBoardWidget::drawRiverCourse(QPainter& painter)
{
    painter.setFont(QFont("楷体", 40, 800));
    qint32 wordY = m_x + 4 * m_space;
    qint32 wordX1 = m_x + 1 * m_space;
    qint32 wordX2 = m_x + 2 * m_space;
    qint32 wordX3 = m_x + 5 * m_space;
    qint32 wordX4 = m_x + 6 * m_space;
    qint32 wordWidth = 80;
    qint32 wordHeight = 80;

    QRect wordRect1(wordX1, wordY, wordWidth, wordHeight);
    QRect wordRect2(wordX2, wordY, wordWidth, wordHeight);
    QRect wordRect3(wordX3, wordY, wordWidth, wordHeight);
    QRect wordRect4(wordX4, wordY, wordWidth, wordHeight);
    painter.drawText(wordRect1, "楚", QTextOption(Qt::AlignCenter));
    painter.drawText(wordRect2, "河", QTextOption(Qt::AlignCenter));
    painter.drawText(wordRect3, "汉", QTextOption(Qt::AlignCenter));
    painter.drawText(wordRect4, "界", QTextOption(Qt::AlignCenter));
}

void IBoardWidget::drawHighlight(QPainter& painter, const QPoint& pos)
{
    QPen pen;
    pen.setColor(QColor(115, 251, 253));
    pen.setWidth(2);
    painter.setPen(pen);

    qint32 baseX = m_x + pos.x() * m_space;
    qint32 baseY = m_y + pos.y() * m_space;

    qint32 offset = m_space / 2 - 3;
    qint32 length = 15;

    //左上
    qint32 topLeftX = baseX - offset;
    qint32 topLeftY = baseY - offset;
    painter.drawLine(topLeftX, topLeftY, topLeftX + length, topLeftY);
    painter.drawLine(topLeftX, topLeftY, topLeftX, topLeftY + length);

    //右上
    qint32 topRightX = baseX + offset;
    qint32 topRightY = baseY - offset;
    painter.drawLine(topRightX, topRightY, topRightX - length, topRightY);
    painter.drawLine(topRightX, topRightY, topRightX, topRightY + length);

    //右下
    qint32 bottomRightX = baseX + offset;
    qint32 bottomRightY = baseY + offset;
    painter.drawLine(bottomRightX, bottomRightY, bottomRightX, bottomRightY - length);
    painter.drawLine(bottomRightX, bottomRightY, bottomRightX - length, bottomRightY);

    //左下
    qint32 bottomLeftX = baseX - offset;
    qint32 bottomLeftY = baseY + offset;
    painter.drawLine(bottomLeftX, bottomLeftY, bottomLeftX + length, bottomLeftY);
    painter.drawLine(bottomLeftX, bottomLeftY, bottomLeftX, bottomLeftY - length);
}

void IBoardWidget::drawPiece(QPainter& painter)
{
    QPen borderPen;
    borderPen.setWidth(7);
    borderPen.setColor(QColor(190, 201, 253));

    QPen textPen;
    textPen.setWidth(1);

    QPen inLinePen;
    inLinePen.setWidth(2);

    painter.setBrush(Qt::white);
    painter.setFont(QFont("楷体", 28, 800));
    qint32 width = m_space - 10;//70
    qint32 height = m_space - 10;//70
    const QList<IPiece*> pieceList = IGlobal::global().pieceList();
    for (IPiece* pPiece : pieceList)
    {
        if (pPiece->isDead())
            continue;

        qint32 x = m_x + pPiece->x() * m_space - m_space / 2 + 5;
        qint32 y = m_y + pPiece->y() * m_space - m_space / 2 + 5;

        QRect geometry(x, y, width, height);
        painter.setPen(borderPen);
        painter.drawEllipse(geometry);

        painter.setPen(inLinePen);
        painter.drawEllipse(x + 8, y + 8, width - 16, height - 16);

        QColor textColor = (pPiece->camp() == IPieceCamp::Black) ? Qt::black : Qt::red;
        textPen.setColor(textColor);
        painter.setPen(textPen);
        painter.drawText(geometry, pPiece->name(), QTextOption(Qt::AlignCenter));
    }
}

void IBoardWidget::mousePressEvent(QMouseEvent* event)
{
    qint32 eventX = event->x();
    qint32 eventY = event->y();
    for (qint32 x = 0; x < 9; x++)
    {
        qint32 px = m_x + x * m_space;
        if (qAbs(px - eventX) > 30) continue;

        for (qint32 y = 0; y < 10; y++)
        {
            qint32 py = m_y + y * m_space;
            if (qAbs(py - eventY) < 30)
            {
                emit posClicked(QPoint(x, y));
                return;
            }
        }
    }
}

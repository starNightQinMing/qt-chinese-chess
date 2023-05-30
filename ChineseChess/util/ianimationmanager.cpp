#include "ianimationmanager.h"

IAnimationManager::IAnimationManager(QObject *parent)
    : QObject(parent)
    , m_pWidgetParent(dynamic_cast<QWidget*>(parent))
{
    m_pAnimationLabel = new QLabel(m_pWidgetParent);
    m_pAnimationLabel->setScaledContents(true);
    m_pAnimationLabel->setWindowFlag(Qt::FramelessWindowHint);
    m_pAnimationLabel->setHidden(true);

    m_pOpacityEffect = new QGraphicsOpacityEffect(m_pAnimationLabel);
    m_pOpacityEffect->setOpacity(1.0);
    m_pAnimationLabel->setGraphicsEffect(m_pOpacityEffect);

    m_pPropertyAnimation = new QPropertyAnimation;
    m_pPropertyAnimation->setTargetObject(m_pOpacityEffect);
    m_pPropertyAnimation->setPropertyName("opacity");

    m_pAnimationDisplayTimer = new QTimer(this);

    (void)connect(m_pPropertyAnimation, &QPropertyAnimation::finished
                  , this, &IAnimationManager::on_propertyAnimation_finished);
    (void)connect(m_pAnimationDisplayTimer, &QTimer::timeout
                  , this, &IAnimationManager::on_animationDisplayTimer_timeout);
}

IAnimationManager::~IAnimationManager()
{
}

void IAnimationManager::displayAnimationImage(const QString& image)
{
    QPixmap pixmap(image);
    m_pAnimationLabel->setFixedSize(pixmap.width(), pixmap.height());
    qint32 parentWidth = m_pWidgetParent->width();
    qint32 parentHeight = m_pWidgetParent->height();
    m_pAnimationLabel->move(parentWidth / 2 - pixmap.width() / 2, parentHeight / 2 - pixmap.height() / 2);
    m_pAnimationLabel->setHidden(false);
    m_pAnimationLabel->setStyleSheet(QString("border-image:url(%1);").arg(image));

    m_pPropertyAnimation->setStartValue(0);
    m_pPropertyAnimation->setEndValue(1);
    m_pPropertyAnimation->setDuration(300);
    m_pPropertyAnimation->start();
}

void IAnimationManager::displayAnimationText(const QString& text)
{
    if (m_pWidgetParent == nullptr)
        return;

    QApplication::beep();

    QFontMetrics fontMetrics(m_pAnimationLabel->font());
    qint32 fontWidth = fontMetrics.horizontalAdvance(text) + 70;
    qint32 fontHeight = fontMetrics.height() + 20;
    m_pAnimationLabel->setFixedSize(fontWidth, fontHeight);
    m_pAnimationLabel->setAlignment(Qt::AlignCenter);
    qint32 parentWidth = m_pWidgetParent->width();
    qint32 parentHeight = m_pWidgetParent->height();
    m_pAnimationLabel->move(parentWidth / 2 - fontWidth / 2, parentHeight / 2 - fontHeight / 2);
    m_pAnimationLabel->setHidden(false);
    m_pAnimationLabel->setText(text);
    m_pAnimationLabel->setStyleSheet("border-image:url(:/ChineseChess/images/textBackground2.png);");

    m_pPropertyAnimation->setStartValue(0);
    m_pPropertyAnimation->setEndValue(1);
    m_pPropertyAnimation->setDuration(300);
    m_pPropertyAnimation->start();
}

void IAnimationManager::on_propertyAnimation_finished()
{
    m_pAnimationDisplayTimer->start(1500);
}

void IAnimationManager::on_animationDisplayTimer_timeout()
{
    m_pAnimationLabel->setHidden(true);
    m_pAnimationDisplayTimer->stop();
    m_pAnimationLabel->setText("");
}


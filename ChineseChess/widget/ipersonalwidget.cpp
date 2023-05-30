#include "ipersonalwidget.h"

#include <QtCore/qdatetime.h>

#include <QtWidgets/qlabel.h>

IPersonalWidget::IPersonalWidget(QWidget *parent)
    : QWidget(parent)
    , IPersonalWidgetUi()
{
    setupUi(this);
}

IPersonalWidget::~IPersonalWidget()
{

}

void IPersonalWidget::setImage(const QString& imageUrl)
{
    Q_UNUSED(imageUrl)
}

void IPersonalWidget::setName(const QString& name)
{
    m_pNameLabel->setText(name);
}

void IPersonalWidget::setBureauTime(const QString& time)
{
    m_pBureauTimeLabel->setText(time);
}

void IPersonalWidget::setReflectTime(const QString& time)
{
    m_pReflectionTimeLabel->setText(time);
}

void IPersonalWidget::startTime()
{
    m_pReflectionTimeLabel->setText("02:30");
    m_timer.start(1000);
}

void IPersonalWidget::stopTime()
{
    m_timer.stop();
}

void IPersonalWidget::onTimerTimeout()
{
    QString format = "mm:ss";
    QTime bureauTime = QTime::fromString(m_pBureauTimeLabel->text(), "mm:ss");
    QTime reflectTime = QTime::fromString(m_pReflectionTimeLabel->text(), "mm:ss");

    bureauTime = bureauTime.addSecs(-1);
    reflectTime = reflectTime.addSecs(-1);

    m_pBureauTimeLabel->setText(bureauTime.toString(format));
    m_pReflectionTimeLabel->setText(reflectTime.toString(format));
}

void IPersonalWidget::retime()
{
    m_pBureauTimeLabel->setText("20:00");
    m_pReflectionTimeLabel->setText("02:30");
}

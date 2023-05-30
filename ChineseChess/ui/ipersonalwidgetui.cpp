#include "ipersonalwidgetui.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

IPersonalWidgetUi::IPersonalWidgetUi()
    : IAbstractWidgetUi()
{
    m_pMainLayout = nullptr;
    m_pImageLabel = nullptr;
    m_pNameLayout = nullptr;
    m_pNameIconLabel = nullptr;
    m_pNameLabel = nullptr;
    m_pBureauTimeLayout = nullptr;
    m_pBureauTimeIconLabel = nullptr;
    m_pBureauTimeLabel = nullptr;
    m_pReflectionTimeLayout = nullptr;
    m_pReflectionTimeIconLabel = nullptr;
    m_pReflectionTimeLabel = nullptr;
}

IPersonalWidgetUi::~IPersonalWidgetUi()
{

}

bool IPersonalWidgetUi::instance(QWidget *pWidget)
{
    I_INSTANCE(m_pMainLayout, QVBoxLayout, nullptr);
    I_INSTANCE(m_pImageLabel, QLabel, pWidget);
    I_INSTANCE(m_pNameLayout, QHBoxLayout, nullptr);
    I_INSTANCE(m_pNameIconLabel, QLabel, pWidget);
    I_INSTANCE(m_pNameLabel, QLabel, pWidget);
    I_INSTANCE(m_pBureauTimeLayout, QHBoxLayout, nullptr);
    I_INSTANCE(m_pBureauTimeIconLabel, QLabel, pWidget);
    I_INSTANCE(m_pBureauTimeLabel, QLabel, pWidget);
    I_INSTANCE(m_pReflectionTimeLayout, QHBoxLayout, nullptr);
    I_INSTANCE(m_pReflectionTimeIconLabel, QLabel, pWidget);
    I_INSTANCE(m_pReflectionTimeLabel, QLabel, pWidget);

    return true;
}

bool IPersonalWidgetUi::retranslateUi(QWidget *pWidget)
{
    if (m_pMainLayout == nullptr)
        return false;

    m_pNameIconLabel->setText("将帅：");
    m_pNameLabel->setText("项羽");

    m_pBureauTimeIconLabel->setText("局时：");
    m_pBureauTimeLabel->setText("20:00");

    m_pReflectionTimeIconLabel->setText("思考：");
    m_pReflectionTimeLabel->setText("02:30");

    return true;
}

void IPersonalWidgetUi::layout(QWidget *pWidget)
{
    m_pNameLayout->addWidget(m_pNameIconLabel);
    m_pNameLayout->addWidget(m_pNameLabel);

    m_pBureauTimeLayout->addWidget(m_pBureauTimeIconLabel);
    m_pBureauTimeLayout->addWidget(m_pBureauTimeLabel);

    m_pReflectionTimeLayout->addWidget(m_pReflectionTimeIconLabel);
    m_pReflectionTimeLayout->addWidget(m_pReflectionTimeLabel);

    m_pMainLayout->addWidget(m_pImageLabel);
    m_pMainLayout->addLayout(m_pNameLayout);
    m_pMainLayout->addLayout(m_pBureauTimeLayout);
    m_pMainLayout->addLayout(m_pReflectionTimeLayout);
    pWidget->setLayout(m_pMainLayout);
}

bool IPersonalWidgetUi::connect(QWidget *pWidget)
{
    QMetaObject::Connection connection;
    bool result = true;
    Q_UNUSED(pWidget);
    return result;
}

void IPersonalWidgetUi::objectNameSetting(QWidget *pWidget)
{
    m_pMainLayout->setObjectName("MainLayout");
    m_pImageLabel->setObjectName("ImageLabel");
    m_pNameLayout->setObjectName("NameLayout");
    m_pNameIconLabel->setObjectName("NameIconLabel");
    m_pNameLabel->setObjectName("NameLabel");
    m_pBureauTimeLayout->setObjectName("BureauTimeLayout");
    m_pBureauTimeIconLabel->setObjectName("BureauTimeIconLabel");
    m_pBureauTimeLabel->setObjectName("BureauTimeLabel");
    m_pReflectionTimeLayout->setObjectName("ReflectionTimeLayout");
    m_pReflectionTimeIconLabel->setObjectName("ReflectionTimeIconLabel");
    m_pReflectionTimeLabel->setObjectName("ReflectionTimeLabel");
    pWidget->setObjectName("PersonalWidget");
}

bool IPersonalWidgetUi::decorate(QWidget *pWidget)
{
    //m_pMainLayout = nullptr;

    m_pImageLabel->setScaledContents(true);
    m_pImageLabel->setMaximumSize(120, 120);
    m_pImageLabel->setPixmap(QPixmap(":/ChineseChess/images/general6.png"));

//    m_pNameLayout = nullptr;
//    m_pNameIconLabel = nullptr;
//    m_pNameLabel = nullptr;
//    m_pBureauTimeLayout = nullptr;
//    m_pBureauTimeIconLabel = nullptr;
//    m_pBureauTimeLabel = nullptr;
//    m_pReflectionTimeLayout = nullptr;
//    m_pReflectionTimeIconLabel = nullptr;
//    m_pReflectionTimeLabel = nullptr;

    pWidget->setAttribute(Qt::WA_StyledBackground);

    return true;
}

void IPersonalWidgetUi::release()
{
    I_RELEASE(m_pMainLayout);
    I_RELEASE(m_pImageLabel);
    I_RELEASE(m_pNameLayout);
    I_RELEASE(m_pNameIconLabel);
    I_RELEASE(m_pNameLabel);
    I_RELEASE(m_pBureauTimeLayout);
    I_RELEASE(m_pBureauTimeIconLabel);
    I_RELEASE(m_pBureauTimeLabel);
    I_RELEASE(m_pReflectionTimeLayout);
    I_RELEASE(m_pReflectionTimeIconLabel);
    I_RELEASE(m_pReflectionTimeLabel);
}

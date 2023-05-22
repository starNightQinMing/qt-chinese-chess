#include "ioperationwidgetui.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qpushbutton.h>

IOperationWidgetUi::IOperationWidgetUi()
    : IAbstractWidgetUi()
{
    m_pMainLayout = nullptr;
    m_pLeftVerticalSpacer = nullptr;
    m_pStartButton = nullptr;
    m_pRestartButton = nullptr;
    m_pPromptButton = nullptr;
    m_pAdmitDefeatButton = nullptr;
    m_pDrawButton = nullptr;
    m_pHelpButton = nullptr;
}

IOperationWidgetUi::~IOperationWidgetUi()
{

}

bool IOperationWidgetUi::instance(QWidget *pWidget)
{
    I_INSTANCE(m_pMainLayout, QVBoxLayout, nullptr);

    m_pLeftVerticalSpacer = new QSpacerItem(20, 40);
    if (m_pLeftVerticalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pStartButton, QPushButton, pWidget);
    I_INSTANCE(m_pRestartButton, QPushButton, pWidget);
    I_INSTANCE(m_pPromptButton, QPushButton, pWidget);
    I_INSTANCE(m_pAdmitDefeatButton, QPushButton, pWidget);
    I_INSTANCE(m_pDrawButton, QPushButton, pWidget);
    I_INSTANCE(m_pHelpButton, QPushButton, pWidget);

    return true;
}

bool IOperationWidgetUi::retranslateUi(QWidget *pWidget)
{
    if (m_pMainLayout == nullptr)
        return false;

    m_pStartButton->setText(QObject::tr("开始"));
    m_pRestartButton->setText(QObject::tr("重开"));
    m_pPromptButton->setText(QObject::tr("提示"));
    m_pAdmitDefeatButton->setText(QObject::tr("认输"));
    m_pDrawButton->setText(QObject::tr("求和"));
    m_pHelpButton->setText(QObject::tr("帮助"));
    pWidget->setWindowTitle(QObject::tr("操作"));

    return true;
}

void IOperationWidgetUi::layout(QWidget *pWidget)
{
    m_pMainLayout->addItem(m_pLeftVerticalSpacer);
    m_pMainLayout->addWidget(m_pStartButton);
    m_pMainLayout->addWidget(m_pRestartButton);
    m_pMainLayout->addWidget(m_pPromptButton);
    m_pMainLayout->addWidget(m_pAdmitDefeatButton);
    m_pMainLayout->addWidget(m_pDrawButton);
    m_pMainLayout->addWidget(m_pHelpButton);
    pWidget->setLayout(m_pMainLayout);
}

bool IOperationWidgetUi::connect(QWidget *pWidget)
{
    QMetaObject::Connection connection;
    bool result = true;

    connection = pWidget->connect(m_pStartButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onStartButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pRestartButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onRestartButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pPromptButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onPromptButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pAdmitDefeatButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onAdmitDefeatButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pDrawButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onDrawButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pHelpButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onHelpButtonClicked()));
    result &= bool(connection);

    return result;
}

void IOperationWidgetUi::objectNameSetting(QWidget *pWidget)
{
    m_pMainLayout->setObjectName("MainLayout");
    m_pStartButton->setObjectName("StartButton");
    m_pRestartButton->setObjectName("RestartButton");
    m_pPromptButton->setObjectName("PromptButton");
    m_pAdmitDefeatButton->setObjectName("AdmitDefeatButton");
    m_pDrawButton->setObjectName("DrawButton");
    m_pHelpButton->setObjectName("HelpButton");
    pWidget->setObjectName("OperationWidget");
}

bool IOperationWidgetUi::decorate(QWidget *pWidget)
{
    //m_pMainLayout;

    m_pLeftVerticalSpacer->changeSize(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    //m_pStartButton;
    //m_pRestartButton;
    //m_pPromptButton;
    //m_pAdmitDefeatButton;
    //m_pDrawButton;
    //m_pHelpButton;

    pWidget->setAttribute(Qt::WA_StyledBackground);

    return true;
}

void IOperationWidgetUi::release()
{
    I_RELEASE(m_pMainLayout);
    I_RELEASE(m_pLeftVerticalSpacer);
    I_RELEASE(m_pStartButton);
    I_RELEASE(m_pRestartButton);
    I_RELEASE(m_pPromptButton);
    I_RELEASE(m_pAdmitDefeatButton);
    I_RELEASE(m_pDrawButton);
    I_RELEASE(m_pHelpButton);
}

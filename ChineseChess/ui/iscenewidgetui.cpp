#include "iscenewidgetui.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qpushbutton.h>

#include "widget/iboardwidget.h"
#include "widget/ipersonalwidget.h"

ISceneWidgetUi::ISceneWidgetUi()
    : IAbstractWidgetUi()
{
    m_pMainLayout = nullptr;
    m_pLeftHorizontalSpacer = nullptr;
    m_pRightHorizontalSpacer = nullptr;

    m_pLeftLayout = nullptr;
    m_pBlackPersonalWidget = nullptr;
    m_pLeftTopVerticalSpacer = nullptr;
    m_pStartButton = nullptr;
    m_pRestartButton = nullptr;
    m_pPauseButton = nullptr;
    m_pEndButton = nullptr;
    m_pQuitButton = nullptr;
    m_pLeftCenterVerticalSpacer = nullptr;
    m_pLeftBottomLayout = nullptr;
    m_pAboutButton = nullptr;
    m_pHelpButton = nullptr;

    m_pSceneLayout = nullptr;
    m_pScentTopVerticalSpacer = nullptr;
    m_pBoardWidget = nullptr;
    m_pScentBottomVerticalSpacer = nullptr;

    m_pRightLayout = nullptr;
    m_pRightTopVerticalSpacer = nullptr;
    m_pRepentanceButton = nullptr;
    m_pRequestButton = nullptr;
    m_pAdmitDefeatButton = nullptr;
    m_pPromptButton = nullptr;
    m_pRedPersonalWidget = nullptr;
}

ISceneWidgetUi::~ISceneWidgetUi()
{

}

bool ISceneWidgetUi::instance(QWidget *pWidget)
{
    I_INSTANCE(m_pMainLayout, QHBoxLayout, nullptr);

    m_pLeftHorizontalSpacer = new QSpacerItem(40, 20);
    if (m_pLeftHorizontalSpacer == nullptr)
        return  false;

    m_pRightHorizontalSpacer = new QSpacerItem(40, 20);
    if (m_pRightHorizontalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pLeftLayout, QVBoxLayout, nullptr);
    I_INSTANCE(m_pBlackPersonalWidget, IPersonalWidget, pWidget);

    m_pLeftTopVerticalSpacer = new QSpacerItem(20, 40);
    if (m_pLeftTopVerticalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pStartButton, QPushButton, pWidget);
    I_INSTANCE(m_pRestartButton, QPushButton, pWidget);
    I_INSTANCE(m_pPauseButton, QPushButton, pWidget);
    I_INSTANCE(m_pEndButton, QPushButton, pWidget);
    I_INSTANCE(m_pQuitButton, QPushButton, pWidget);

    m_pLeftCenterVerticalSpacer = new QSpacerItem(20, 40);
    if (m_pLeftCenterVerticalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pLeftBottomLayout, QHBoxLayout, nullptr);
    I_INSTANCE(m_pAboutButton, QPushButton, pWidget);
    I_INSTANCE(m_pHelpButton, QPushButton, pWidget);

    I_INSTANCE(m_pSceneLayout, QVBoxLayout, nullptr);

    m_pScentTopVerticalSpacer = new QSpacerItem(20, 40);
    if (m_pScentTopVerticalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pBoardWidget, IBoardWidget, pWidget);

    m_pScentBottomVerticalSpacer = new QSpacerItem(20, 40);
    if (m_pScentTopVerticalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pRightLayout, QVBoxLayout, nullptr);

    m_pRightTopVerticalSpacer = new QSpacerItem(20, 40);
    if (m_pRightTopVerticalSpacer == nullptr)
        return false;

    I_INSTANCE(m_pRepentanceButton, QPushButton, pWidget);
    I_INSTANCE(m_pRequestButton, QPushButton, pWidget);
    I_INSTANCE(m_pAdmitDefeatButton, QPushButton, pWidget);
    I_INSTANCE(m_pPromptButton, QPushButton, pWidget);
    I_INSTANCE(m_pRedPersonalWidget, IPersonalWidget, pWidget);

    return true;
}

bool ISceneWidgetUi::retranslateUi(QWidget *pWidget)
{
    if (m_pMainLayout == nullptr)
        return false;

    m_pStartButton->setText("开始对战");
    m_pRestartButton->setText("重新对战");
    m_pPauseButton->setText("鸣金收兵");
    m_pEndButton->setText("结束对战");
    m_pQuitButton->setText("退出战场");
    m_pAboutButton->setText("关于");
    m_pHelpButton->setText("帮助");
    m_pRepentanceButton->setText("悔棋");
    m_pRequestButton->setText("求和");
    m_pAdmitDefeatButton->setText("认输");
    m_pPromptButton->setText("提示");
    m_pRedPersonalWidget->setName("刘邦");
    pWidget->setWindowTitle("中国象棋");

    return true;
}

void ISceneWidgetUi::layout(QWidget *pWidget)
{
    m_pLeftLayout->addWidget(m_pBlackPersonalWidget);
    m_pLeftLayout->addItem(m_pLeftTopVerticalSpacer);
    m_pLeftLayout->addWidget(m_pStartButton);
    m_pLeftLayout->addWidget(m_pRestartButton);
    m_pLeftLayout->addWidget(m_pPauseButton);
    m_pLeftLayout->addWidget(m_pEndButton);
    m_pLeftLayout->addWidget(m_pQuitButton);
    m_pLeftLayout->addItem(m_pLeftCenterVerticalSpacer);

    m_pLeftBottomLayout->addWidget(m_pAboutButton);
    m_pLeftBottomLayout->addWidget(m_pHelpButton);

    m_pLeftLayout->addLayout(m_pLeftBottomLayout);

    m_pSceneLayout->addItem(m_pScentTopVerticalSpacer);
    m_pSceneLayout->addWidget(m_pBoardWidget);
    m_pSceneLayout->addItem(m_pScentBottomVerticalSpacer);

    m_pRightLayout->addItem(m_pRightTopVerticalSpacer);
    m_pRightLayout->addWidget(m_pRepentanceButton);
    m_pRightLayout->addWidget(m_pRequestButton);
    m_pRightLayout->addWidget(m_pAdmitDefeatButton);
    m_pRightLayout->addWidget(m_pPromptButton);
    m_pRightLayout->addWidget(m_pRedPersonalWidget);

    m_pMainLayout->addItem(m_pLeftHorizontalSpacer);
    m_pMainLayout->addLayout(m_pLeftLayout);
    m_pMainLayout->addLayout(m_pSceneLayout);
    m_pMainLayout->addLayout(m_pRightLayout);
    m_pMainLayout->addItem(m_pRightHorizontalSpacer);

    pWidget->setLayout(m_pMainLayout);
}

bool ISceneWidgetUi::connect(QWidget *pWidget)
{
    QMetaObject::Connection connection;
    bool result = true;

    connection = pWidget->connect(m_pStartButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onStartButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pRestartButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onRestartButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pPauseButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onPauseButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pEndButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onEndButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pQuitButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onQuitButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pAboutButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onAboutButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pHelpButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onHelpButtonClicked()));
    result &= bool(connection);

    //
    connection = pWidget->connect(m_pBoardWidget, SIGNAL(posClicked(const QPoint&))
                                  , pWidget, SLOT(onBoardWidgetPosClicked(const QPoint&)));
    result &= bool(connection);

    //
    connection = pWidget->connect(m_pRepentanceButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onRepentanceButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pRequestButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onRequestButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pAdmitDefeatButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onAdmitDefeatButtonClicked()));
    result &= bool(connection);

    connection = pWidget->connect(m_pPromptButton, SIGNAL(clicked())
                                  , pWidget, SLOT(onPromptButtonClicked()));
    result &= bool(connection);

    return result;
}

void ISceneWidgetUi::objectNameSetting(QWidget *pWidget)
{
    m_pMainLayout->setObjectName("MainLayout");
    m_pLeftLayout->setObjectName("LeftLayout");
    m_pBlackPersonalWidget->setObjectName("BlackPersonalWidget");
    m_pStartButton->setObjectName("StartButton");
    m_pRestartButton->setObjectName("RestartButton");
    m_pPauseButton->setObjectName("PauseButton");
    m_pEndButton->setObjectName("EndButton");
    m_pQuitButton->setObjectName("QuitButton");
    m_pLeftBottomLayout->setObjectName("LeftBottomLayout");
    m_pAboutButton->setObjectName("AboutButton");
    m_pHelpButton->setObjectName("HelpButton");
    m_pSceneLayout->setObjectName("SceneLayout");
    m_pBoardWidget->setObjectName("BoardWidget");
    m_pRightLayout->setObjectName("RightLayout");
    m_pRepentanceButton->setObjectName("RepentanceButton");
    m_pRequestButton->setObjectName("RequestButton");
    m_pAdmitDefeatButton->setObjectName("AdmitDefeatButton");
    m_pPromptButton->setObjectName("PromptButton");
    m_pRedPersonalWidget->setObjectName("RedPersonalWidget");
    pWidget->setObjectName("SceneWidget");
}

bool ISceneWidgetUi::decorate(QWidget *pWidget)
{
    //m_pMainLayout = nullptr;
    m_pLeftHorizontalSpacer->changeSize(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_pRightHorizontalSpacer->changeSize(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    //m_pLeftLayout = nullptr;
    //m_pBlackPersonalWidget = nullptr;
    m_pLeftTopVerticalSpacer->changeSize(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //m_pStartButton = nullptr;
    //m_pRestartButton = nullptr;
    //m_pPauseButton = nullptr;
    //m_pEndButton = nullptr;
    //m_pQuitButton = nullptr;
    m_pLeftCenterVerticalSpacer->changeSize(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //m_pLeftBottomLayout = nullptr;
    //m_pAboutButton = nullptr;
    //m_pHelpButton = nullptr;

    //m_pSceneLayout = nullptr;
    m_pScentTopVerticalSpacer->changeSize(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pBoardWidget->setFixedSize(760, 840);
    m_pScentBottomVerticalSpacer->changeSize(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    //m_pRightLayout = nullptr;
    m_pRightTopVerticalSpacer->changeSize(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //m_pRepentanceButton = nullptr;
    //m_pRequestButton = nullptr;
    //m_pAdmitDefeatButton = nullptr;
    //m_pPromptButton = nullptr;
    //m_pRedPersonalWidget = nullptr;

    pWidget->setAttribute(Qt::WA_StyledBackground);

    return true;
}

void ISceneWidgetUi::release()
{
    I_RELEASE(m_pMainLayout);
    I_RELEASE(m_pLeftHorizontalSpacer);
    I_RELEASE(m_pRightHorizontalSpacer);

    I_RELEASE(m_pLeftLayout);
    I_RELEASE(m_pBlackPersonalWidget);
    I_RELEASE(m_pLeftTopVerticalSpacer);
    I_RELEASE(m_pStartButton);
    I_RELEASE(m_pRestartButton);
    I_RELEASE(m_pPauseButton);
    I_RELEASE(m_pEndButton);
    I_RELEASE(m_pQuitButton);
    I_RELEASE(m_pLeftCenterVerticalSpacer);
    I_RELEASE(m_pLeftBottomLayout);
    I_RELEASE(m_pAboutButton);
    I_RELEASE(m_pHelpButton);

    I_RELEASE(m_pSceneLayout);
    I_RELEASE(m_pScentTopVerticalSpacer);
    I_RELEASE(m_pBoardWidget);
    I_RELEASE(m_pScentBottomVerticalSpacer);

    I_RELEASE(m_pRightLayout);
    I_RELEASE(m_pRightTopVerticalSpacer);
    I_RELEASE(m_pRepentanceButton);
    I_RELEASE(m_pRequestButton);
    I_RELEASE(m_pAdmitDefeatButton);
    I_RELEASE(m_pPromptButton);
    I_RELEASE(m_pRedPersonalWidget);
}

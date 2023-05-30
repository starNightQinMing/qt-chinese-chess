#ifndef ISCENEWIDGETUI_H
#define ISCENEWIDGETUI_H

#include "iabstractwidgetui.h"

class IBoardWidget;
class IPersonalWidget;
class QPushButton;

class ISceneWidgetUi : public IAbstractWidgetUi
{
public:
    ISceneWidgetUi();
    virtual ~ISceneWidgetUi();

protected:
    virtual bool instance(QWidget* pWidget) override;
    virtual bool retranslateUi(QWidget* pWidget) override;
    virtual void layout(QWidget* pWidget) override;
    virtual bool connect(QWidget* pWidget) override;
    virtual void objectNameSetting(QWidget* pWidget) override;
    virtual bool decorate(QWidget* pWidget) override;
    virtual void release() override;

protected:
    QHBoxLayout* m_pMainLayout;
    QSpacerItem* m_pLeftHorizontalSpacer;
    QSpacerItem* m_pRightHorizontalSpacer;

    QVBoxLayout* m_pLeftLayout;
    IPersonalWidget* m_pBlackPersonalWidget;
    QSpacerItem* m_pLeftTopVerticalSpacer;
    QPushButton* m_pStartButton;
    QPushButton* m_pRestartButton;
    QPushButton* m_pPauseButton;
    QPushButton* m_pEndButton;
    QPushButton* m_pQuitButton;
    QSpacerItem* m_pLeftCenterVerticalSpacer;
    QHBoxLayout* m_pLeftBottomLayout;
    QPushButton* m_pAboutButton;
    QPushButton* m_pHelpButton;

    QVBoxLayout* m_pSceneLayout;
    QSpacerItem* m_pScentTopVerticalSpacer;
    IBoardWidget* m_pBoardWidget;
    QSpacerItem* m_pScentBottomVerticalSpacer;

    QVBoxLayout* m_pRightLayout;
    QSpacerItem* m_pRightTopVerticalSpacer;
    QPushButton* m_pRepentanceButton;
    QPushButton* m_pRequestButton;
    QPushButton* m_pAdmitDefeatButton;
    QPushButton* m_pPromptButton;
    IPersonalWidget* m_pRedPersonalWidget;
};

#endif // ISCENEWIDGETUI_H

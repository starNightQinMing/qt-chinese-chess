#ifndef IMAINWIDGETUI_H
#define IMAINWIDGETUI_H

#include "iabstractwidgetui.h"

class ISceneWidget;

class IMainWidgetUi : public IAbstractWidgetUi
{
public:
    IMainWidgetUi();
    virtual ~IMainWidgetUi();

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
    ISceneWidget* m_pSceneWidget;
};

#endif // IMAINWIDGETUI_H

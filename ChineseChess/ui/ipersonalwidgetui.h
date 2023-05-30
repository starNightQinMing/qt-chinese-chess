#ifndef IPERSONALWIDGETUI_H
#define IPERSONALWIDGETUI_H

#include "iabstractwidgetui.h"

class QLabel;

class IPersonalWidgetUi : public IAbstractWidgetUi
{
public:
    IPersonalWidgetUi();
    virtual ~IPersonalWidgetUi();

protected:
    virtual bool instance(QWidget* pWidget) override;
    virtual bool retranslateUi(QWidget* pWidget) override;
    virtual void layout(QWidget* pWidget) override;
    virtual bool connect(QWidget* pWidget) override;
    virtual void objectNameSetting(QWidget* pWidget) override;
    virtual bool decorate(QWidget* pWidget) override;
    virtual void release() override;

protected:
    QVBoxLayout* m_pMainLayout;
    QLabel* m_pImageLabel;
    QHBoxLayout* m_pNameLayout;
    QLabel* m_pNameIconLabel;
    QLabel* m_pNameLabel;
    QHBoxLayout* m_pBureauTimeLayout;
    QLabel* m_pBureauTimeIconLabel;
    QLabel* m_pBureauTimeLabel;
    QHBoxLayout* m_pReflectionTimeLayout;
    QLabel* m_pReflectionTimeIconLabel;
    QLabel* m_pReflectionTimeLabel;
};

#endif // IPERSONALWIDGETUI_H

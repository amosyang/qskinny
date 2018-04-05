#ifndef SPEEDOMETERSKINLET_H
#define SPEEDOMETERSKINLET_H

#include <QskSkinlet.h>

class Speedometer;

class SpeedometerSkinlet : public QskSkinlet
{
    Q_GADGET

public:

    enum NodeRole
    {
        PanelRole,
        LabelsRole,
        NeedleRole
    };

    Q_INVOKABLE SpeedometerSkinlet( QskSkin* skin = nullptr );
    virtual ~SpeedometerSkinlet() override;

    virtual QRectF subControlRect( const QskSkinnable* skinnable,
        QskAspect::Subcontrol ) const override;

protected:
    virtual QSGNode* updateSubNode( const QskSkinnable* skinnable, quint8 nodeRole, QSGNode* node ) const override;

private:
    QSGNode* updatePanelNode( const Speedometer*, QSGNode* ) const;
    QSGNode* updateLabelsNode( const Speedometer*, QSGNode* ) const;
    QSGNode* updateNeedleNode( const Speedometer*, QSGNode* ) const;
};

#endif // SPEEDOMETERSKINLET_H

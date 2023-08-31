#ifndef ONLINEMAPWIDGET_H
#define ONLINEMAPWIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebChannel>
#include "ui/MapWebChannelHandler.h"
#include "core/PropConditions.h"
#include "ui/WebEnginePage.h"
#include "core/Rig.h"
#include "ui/NewContactWidget.h"
#include "core/KSTChat.h"

namespace Ui {
class OnlineMapWidget;
}

class OnlineMapWidget : public QWebEngineView
{
    Q_OBJECT

public:
    explicit OnlineMapWidget(QWidget* parent = nullptr);
    ~OnlineMapWidget();

    void assignPropConditions(PropConditions *);
    void registerContactWidget(const NewContactWidget*);

signals:
    void chatCallsignPressed(QString);

public slots:
    void setTarget(double lat, double lon);
    void changeTheme(int);
    void auroraDataUpdate();
    void mufDataUpdate();
    void setIBPBand(VFOID, double, double, double);
    void antPositionChanged(int in_azimuth, int in_elevation);
    void rotConnected();
    void rotDisconnected();
    void flyToMyQTH();
    void drawChatUsers(QList<KSTUsersInfo> list);

protected slots:
    void finishLoading(bool);
    void chatCallsignTrigger(QString);

private:

    WebEnginePage *main_page;
    bool isMainPageLoaded;
    QString postponedScripts;
    QWebChannel channel;
    MapWebChannelHandler webChannelHandler;
    PropConditions *prop_cond;
    const NewContactWidget *contact;
    int lastSeenAzimuth, lastSeenElevation;
    bool isRotConnected;

    void runJavaScript(QString &);
};

#endif // ONLINEMAPWIDGET_H

#include "MainWindowsEventHandling.h"
#include "RobotProxy.h"
#include <QQmlContext>
#include "RobotStateHistory.h"

#include <QQuickItem>
#include <QQmlApplicationEngine>

MainWindowsEventHandling::MainWindowsEventHandling(
        RobotProxy &robot, QQmlContext& qmlContext, RobotStateHistory& history)
    : robot(robot), qmlContext(qmlContext), history(history)
{
    QObject::connect(&history, SIGNAL(historyChanged()), this, SLOT(historyChanged()));

}

void MainWindowsEventHandling::accelerateCommand()
{
    robot.accelerate();
}

void MainWindowsEventHandling::stopCommand()
{
    robot.stop();
}

void MainWindowsEventHandling::resetCommand()
{
    robot.reset();
}


void MainWindowsEventHandling::robotTestCommand()
{
    robot.reset();
    robot.selfTest();
}

void MainWindowsEventHandling::historyChanged()
{
    // Ahhoz, hogy frissüljenek a QML oldali adatok, frissíteni kell a változók összekapcsolását.
    qmlContext.setContextProperty(QStringLiteral("historyModel"), QVariant::fromValue(history.stateList));
    qmlContext.setContextProperty(QStringLiteral("currentState"), QVariant::fromValue(history.currentState));

    qmlContext.setContextProperty(QStringLiteral("historyGraphTimestamps"), QVariant::fromValue(history.graphTimestamps));

    //A Qvector nem támogatott QML-ben, ezért átalakítom QList-be

    QList<int> v1,v2;
    if(!history.graphGyro.isEmpty())
    {

        int i;
        for(i=0;i<history.graphGyro.count();i++)
        {
            v1.append(history.graphGyro[i][0]);
            v2.append(history.graphGyro[i][1]);
        }
    }

    qmlContext.setContextProperty(QStringLiteral("historyGraphGyro1"), QVariant::fromValue(v1));
    qmlContext.setContextProperty(QStringLiteral("historyGraphGyro2"), QVariant::fromValue(v2));
    qmlContext.setContextProperty(QStringLiteral("historyGraphVelocity"), QVariant::fromValue(history.graphVelocities));
    qmlContext.setContextProperty(QStringLiteral("historyGraphAcceleration"), QVariant::fromValue(history.graphAcceleration));

    // Jelzünk a QML controloknak, hogy újrarajzolhatják magukat, beállítottuk az új értékeket.
    emit historyContextUpdated();
}

QQuickItem* MainWindowsEventHandling::FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // Node keresése
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // Gyerekekben keresés
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = FindItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // Nem találtuk.
    return nullptr;
}

QQuickItem* MainWindowsEventHandling::FindItemByName(QObject *rootObject, const QString& name)
{
    return FindItemByName(rootObject->children(), name);
}

void MainWindowsEventHandling::ConnectQmlSignals(QObject *rootObject)
{
    QQuickItem *historyGraph = FindItemByName(rootObject,QString("historyGraph"));
    QQuickItem *vectorGraph = FindItemByName(rootObject,QString("vectorGraph"));
    if (historyGraph)
    {
        QObject::connect(this, SIGNAL(historyContextUpdated()), historyGraph, SLOT(requestPaint()));
        QObject::connect(this, SIGNAL(historyContextUpdated()), vectorGraph, SLOT(requestPaint()));
    }
    else
    {
        qDebug() << "HIBA: Nem találom a historyGraph objektumot a QML környezetben.";
    }
}

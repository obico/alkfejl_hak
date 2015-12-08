#include "RobotStateHistory.h"
#include "RobotState.h"

RobotStateHistory::RobotStateHistory()
    : QObject(nullptr), currentState(nullptr)
{
}

void RobotStateHistory::Add(const RobotState& state)
{
    // TODO Add history cleanup function!
    /** @note Unique pointer létrehozása, mellyel a robot jelenlegi állapotára mutatunk. 
    *   Azért használjuk, mert egyszerre fog megszűnni a mutatott objektummal. 
    *   Jelen esetben új robot állapot beérkezése esetén. */
    std::unique_ptr<RobotState> newState = std::make_unique<RobotState>();
    newState->CopyFrom(state);

    stateList.append(newState.get());
    currentState = (RobotState*)newState.get(); // This has to be done before moving ownership
    container.push_back(std::move(newState));

    // Összeállítjuk a grafikon számára az adatszerkezetet.
    // Ezek a listák QList<int> típusú listák, amiket direkt arra hozunk létre, hogy a QML elemek
    //  ezekből olvassák ki az adatokat, mivel erre a fenti container nem alkalmas. (Az std::vector
    //  nem támogatja a Qt metaobject rendszerét.)
    clearScreen();
    /** @note Weak pointer és ahhoz shared pointer felhasználása
    *   Megvizsgálom, hogy van-e egyáltalán hiba a robot működése során. Amennyiben nincs akkor a statisztikákat kirajzoltatom, kiirattatom.
    */

    std::shared_ptr<RobotState> sptr;

    sptr.reset( new RobotState );
    sptr->CopyFrom(state);

    std::weak_ptr<RobotState> weak2 = sptr;
    // weak pointer lefoglalása
    if ( auto tmp = weak2.lock() )
    {
        // robot esetleges hibájának kinyerése, ha "nincs hiba" akkor mindent rajzoljon ki
        if (tmp->error() == "nincs hiba")
        {
            int graphStateNumber = visualize();
            auto it = container.end()-graphStateNumber;
            for(;it!=container.end();++it)
            {

                RobotState *currentState = it->get();
                graphTimestamps.append(currentState->timestamp());
                graphGyro.append(currentState->g());
                graphVelocities.append(currentState->v());
                graphAcceleration.append(currentState->a());

            }
        }
    }
    else
    {
        qDebug() << "weak pointer lejárt, az eredményt nem ábrázoljuk";
    }

    // Jelezzük a history változását.
    historyHasChanged();
}

int RobotStateHistory::historyHasChanged()
{
    emit historyChanged();
    return 1;
}

int RobotStateHistory::clearScreen()
{
    graphTimestamps.clear();
    graphGyro.clear();
    graphVelocities.clear();
    graphAcceleration.clear();
    return 1;
}

int RobotStateHistory::visualize()
{

    return stateList.size() < shownStateNumber ? stateList.size() : shownStateNumber;;
}

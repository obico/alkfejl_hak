#include <QDebug>
#include <QQmlContext>
#include "StvApplication.h"

/* Egyszerű main függvény */

int main(int argc, char *argv[])
{
    StvApplication app(argc, argv);
    return app.exec();
}

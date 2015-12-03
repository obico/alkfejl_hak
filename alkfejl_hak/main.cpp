#include <QDebug>
#include <QQmlContext>
#include "StvApplication.h"

/**
 * @note A qTest megvalósításában gondba ütköztünk.
 * Alapvetően kétféleképpen próbáltuk megvalósítani a tesztelést.
 * Elsőként megváltoztattuk a teljes könyvtárstruktúrát. Létrehoztunk Lib és Test mappákat, hogy oda rakjunk a meghívandó modelleket és függvényeket. Ez a megoldás, azért nem működött, mivel a program túl bonyolult volt.
 * A Lib-be kellett volna átrakni a tesztelendő objektumokat, de mivel a header-k és source-k egymásra hivatkoznak és mutatnak, a main.cpp kivételével mindent át kellett rakni a Lib-be. Miután ez megvolt a Test mappában létrehoztuk a szükséges qTest függvényeket, például QVERIFY, QCOMPARE. Ezzel pedig az volt a probléma, hogy példányosítani kellett ezeknek a paramétereit, vagyis létrehozni egy model objektumot. A modell objektumak pedig meg kell adni a bemenő paramétereit, ahhoz hogy a konstruktor lefusson. De ez problémás volt, mivel az objektumot egymással kommunikálnak, létre kellett hozni ezért gyakorlatilag minden objektumot ami pl. a RobotProxy.h-hoz kellett. Ez nem működött.
 * Nem találtunk olyan egyszerű függvényt, amin a tutorialokon bemutatott megoldás működne.
 * Másodikként, nem változtattunk a könyvtár struktúrán, megpróbáltuk a megírt .cpp-kbe belrakni a a modelleket. Itt is hasonló problémákba ütköztünk mint az első esetben. Nem tudtuk az objektumokat létrehozni, ahhoz hogy teszteljük.
 * Van egy qTest ág a fejlesztésben, amit emiatt nem is mergeltünk bele a masterbe, mivel nem működik a szükséges funkció.
 *
 */

int main(int argc, char *argv[])
{
    StvApplication app(argc, argv);
    return app.exec();
}

#ifndef ALKFEJL_HAKAPPLICATIONTEST_H
#define ALKFEJL_HAKAPPLICATIONTEST_H

#include <QObject>

/**
 * @brief The alkfejl_hakApplicationTest class
 * Át kellett rendezni a projekt hierarchiát, hogy a unit testeknek megfelelő környezetet alakítsunk ki.
 * @see Ide és a alkfejl_hakLib-be kerülnek a unit testekhez szükséges sorok.
 *
 */

/**
 * @see Fontos dokumentáció:Qt Creatorban unit teszt projektet létrehozva kapunk egyből egy kis keretprogramot is, ami elég jól megmutatja, hogyan is kell tesztet készíteni. A unit tesztelés általában azt jelenti, hogy a tesztelendő osztályokat példányosítjuk és mindenféle bemenetekkel bombázzuk, hogy utána ellenőrizzük a reakcióikat. A tesztelendő osztályok általában másik projektből származnak: általában több projektünk van, amiből az egyik a unit tesztek helye, és természetesen látják a többi projekt (pl. library és futtatható alkalmazás külön projektben) osztályait.
 */

class alkfejl_hakApplicationTest : public QObject
{
    Q_OBJECT
public:
    alkfejl_hakApplicationTest(QObject *parent = 0);

signals:

public slots:

private slots:
    //void myTestValuesTest();
};

#endif // ALKFEJL_HAKAPPLICATIONTEST_H

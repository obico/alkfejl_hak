#ifndef ALKFEJL_HAKAPPLICATIONTEST_H
#define ALKFEJL_HAKAPPLICATIONTEST_H

#include <QObject>

/**
 * @brief The alkfejl_hakApplicationTest class
 * Át kellett rendezni a projekt hierarchiát, hogy a unit testeknek megfelelő környezetet alakítsunk ki.
 * @see Ide és a alkfejl_hakLib-be kerülnek a unit testekhez szükséges sorok.
 *
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

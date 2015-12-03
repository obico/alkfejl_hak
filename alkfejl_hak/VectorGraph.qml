import QtQuick 2.0

// A HistoryGraph alapvetően egy Canvas, mivel arra lehet rajzolni.
Canvas {
    // Vannak neki további tulajdonságai, amiket kintről kap
    property var graphTimestamps;
    property var graphVelocities;
    property var graphAccelerations;
    property var graphGyro1;
    property var graphGyro2;

    // A Canvas Paint signalja esetén újra kell rajzolni a grafikont.
    onPaint: {
        // A grafikon rajzolát itt, a QML oldalon, JavaScripben megírva történik.
        // Kell egy "drawing context", amire rajzolni tudunk.
        var context = getContext("2d");

        // Kitöltés fehérre
        context.fillStyle ="rgba(129,177,191,1)"
        context.fillRect(0, 0, width, height);
        //koordináta tengelyek berajzolása
        drawVerticallLine(context, 0, "rgba(100,100,100,1)", 5.0)

        drawHorizontalLine(context, 0, "rgba(100,100,100,1)", 5.0)
        //giroszkóp jelének berajzolása
        drawcircle(context,graphGyro1[graphGyro1.length-1],graphGyro2[graphGyro2.length-1], "rgba(255,0,0,1)", 5.0)
        // Az adatsorok megrajzolása (a graphTimestamps értékét jelenleg nem használjuk).
        //  Ez is külön függvénybe került.
        //drawDataset(context, graphGyro, "rgba(110,220,110,1)", 5.0);
        //drawDataset(context, graphAccelerations, "rgba(220,110,110,1)", 5.0);
    } // onPaint vége

    // Vízszintes vonal berajzolása.
    function drawHorizontalLine(context, dataValue, strokeStyle, verticalScaler)
    {
        var offset = height/2;

        context.beginPath();
        context.lineWidth = 1;
        context.strokeStyle = strokeStyle;
        // Mozgás a vonal elejére.
        context.moveTo(0, offset - verticalScaler * dataValue);
        // Vonal végére mozgás.
        context.lineTo(width, offset - verticalScaler * dataValue);
        context.stroke();
    }
    function drawVerticallLine(context, dataValue, strokeStyle, verticalScaler)
    {
        var offset = width/2;

        context.beginPath();
        context.lineWidth = 1;
        context.strokeStyle = strokeStyle;
        // Mozgás a vonal elejére.
        context.moveTo(offset - verticalScaler * dataValue, 0);
        // Vonal végére mozgás.
        context.lineTo(offset - verticalScaler * dataValue, height);
        context.stroke();
    }
    function drawcircle(context, dataValue1,dataValue2, strokeStyle, verticalScaler)
    {
        var offsetw = width/2;
        var offseth = height/2;
        context.beginPath();
        context.lineWidth = 5;
        context.strokeStyle = strokeStyle;

        // kör kirajzolása
        context.arc(offsetw + verticalScaler *dataValue1, offseth - verticalScaler *dataValue2, 5, 0, 360,false);
        context.stroke();
    }
    function drawDataset(context, datarow, strokeStyle, verticalScaler)
    {
        var offset = height/2;

        context.beginPath();
        context.lineWidth = 3;
        context.strokeStyle = strokeStyle;
        context.moveTo(0, offset-datarow[0]);
        // A vektoron végigmenve behúzzuk a grafikon szakaszait.

        for(var i=0; i<graphVelocities.length;i++)
        {
            context.lineTo(10*i, offset - verticalScaler * datarow[i][0]);
        }
        context.stroke();
    }
}

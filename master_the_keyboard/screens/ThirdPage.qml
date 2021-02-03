import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import QtCharts 2.0
import local.api.backend 1.0

Item {
    id: resultsScreen
    Image {
        id:backgroundImage;
        anchors.fill:parent;
        source: "qrc:/img/images/background.png";
    }

    Text {
        id: title;

        font.family: "serif";
        font.pixelSize: parent.height/25;
        text: "Results";
        x: parent.width/2 - title.width/2;
        y: parent.height/35;
    }

    Button {
        id: tryAgainButton

        text: qsTr("Try again")
        font.pointSize: 12
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        onClicked: {
            backend.resetText()
            stack.push(typingPage);
        }
    }

    Item {
        id: charts
        width: 990*parent.width/1000
        height: 8*parent.height/10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        ChartView {
            id: accuracyChart
            width: parent.width/2
            height: parent.height
            anchors.left: charts.left
            anchors.leftMargin: 0
            antialiasing: true
            Component.onCompleted: {
                var listLength = backend.accuracyHistory.length;
                var xAxis = Qt.createQmlObject("import QtQuick 2.0; import QtCharts " +
                                               "2.0; ValueAxis { min: " + 1 + "; max: " +
                                               listLength + "; }", accuracyChart);
                var yAxis = Qt.createQmlObject("import QtQuick 2.0; import QtCharts " +
                                               "2.0; ValueAxis { min: " +
                backend.accuracyHistory.reduce(function(a,b) {return Math.min(a,b)}) +
                                               "; max: " +
                backend.accuracyHistory.reduce(function(a,b) {return Math.max(a,b)}) +
                                               "; }", accuracyChart);
                var series = accuracyChart.createSeries(ChartView.SeriesTypeLine,
                                                        "ACCURACY HISTORY", xAxis,
                                                        yAxis);
                series.pointsVisible = true;
                series.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
                 // connect onHovered signal to a function
                series.hovered.connect(function(point, state){ console.log(point); });
                var y = 0;
                for(var x=1; x<=listLength; x++)
                {
                    y = backend.accuracyHistory[listLength-x];
                    series.append(x, y);
                }
            }
        }

        ChartView {
            id: speedChart
            width: parent.width/2
            height: parent.height
            anchors.left: accuracyChart.right;
            anchors.leftMargin: 0
            antialiasing: true
            Component.onCompleted: {
                var listLength = backend.speedHistory.length;
                var xAxis = Qt.createQmlObject("import QtQuick 2.0; import QtCharts " +
                                               "2.0; ValueAxis { min: " + 1 + "; max: " +
                                               listLength + "; }", speedChart);
                var yAxis = Qt.createQmlObject("import QtQuick 2.0; import QtCharts " +
                                               "2.0; ValueAxis { min: " +
                backend.speedHistory.reduce(function(a,b) {return Math.min(a,b)}) +
                                               "; max: " +
                backend.speedHistory.reduce(function(a,b) {return Math.max(a,b)}) +
                                               "; }", speedChart);
                var series = speedChart.createSeries(ChartView.SeriesTypeLine,
                                                     "SPEED HISTORY", xAxis, yAxis);
                series.pointsVisible = true;
                series.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
                // connect onHovered signal to a function
                series.hovered.connect(function(point, state){ console.log(point); });
                var y = 0;
                for(var x=1; x<=listLength; x++)
                {
                    y = backend.speedHistory[listLength-x];
                    series.append(x, y);
                }
            }
        }
    }
}

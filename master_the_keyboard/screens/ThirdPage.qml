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
            id: speedChart
            width: parent.width/2
            height: parent.height
            anchors.left: charts.left
            anchors.leftMargin: 0
            //title: "SPEED HISTORY"
            antialiasing: true

    //        LineSeries {
    //            //name: "SPEED HISTORY"
    //            XYPoint { x: 1; y: backend.speedHistory[0] }
    //            XYPoint { x: 2; y: backend.speedHistory[1] }
    //            XYPoint { x: 3; y: backend.speedHistory[2] }
    //            XYPoint { x: 4; y: backend.speedHistory[3] }
    //            XYPoint { x: 5; y: backend.speedHistory[4] }
    //            XYPoint { x: 6; y: backend.speedHistory[5] }
    //        }
            //TESTE
            LineSeries {
                name: "SPEED HISTORY"
                XYPoint { x: 1; y: 2 }
                XYPoint { x: 2; y: 4 }
                XYPoint { x: 3; y: 6 }
                XYPoint { x: 4; y: 8 }
                XYPoint { x: 5; y: 2 }
                XYPoint { x: 6; y: 1 }
            }
        }

        ChartView {
            id: accuracyChart
            width: parent.width/2
            height: parent.height
            anchors.left: speedChart.right
            anchors.leftMargin: 0
            //title: "ACCURACY HISTORY"
            antialiasing: true

    //        LineSeries {
    //            //name: "ACCURACY HISTORY"
    //            XYPoint { x: 1; y: backend.accuracyHistory[0] }
    //            XYPoint { x: 2; y: backend.accuracyHistory[1] }
    //            XYPoint { x: 3; y: backend.accuracyHistory[2] }
    //            XYPoint { x: 4; y: backend.accuracyHistory[3] }
    //            XYPoint { x: 5; y: backend.accuracyHistory[4] }
    //            XYPoint { x: 6; y: backend.accuracyHistory[5] }
    //        }
            //TESTE
            LineSeries {
                name: "ACCURACY HISTORY"
                XYPoint { x: 1; y: 2 }
                XYPoint { x: 2; y: 4 }
                XYPoint { x: 3; y: 6 }
                XYPoint { x: 4; y: 8 }
                XYPoint { x: 5; y: 2 }
                XYPoint { x: 6; y: 1 }
            }
        }
    }
}

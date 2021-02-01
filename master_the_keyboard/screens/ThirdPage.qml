import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
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
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        onClicked: {
            backend.resetText()
            stack.push(typingPage);
        }
    }
}

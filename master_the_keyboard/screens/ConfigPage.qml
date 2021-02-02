import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    id: configurationScreen
    Image {
        id:backgroundImage;
        anchors.fill:parent;
        source: "qrc:/img/images/background.png";
    }

    Text {
        id: title;

        font.family: "serif";
        font.pixelSize: parent.height/25;
        text: "Options";
        x: parent.width/2 - title.width/2;
        y: parent.height/35;
    }

    Button {
        id: continueButton

        text: qsTr("Continue exercise")
        font.pointSize: 12
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        onClicked: {
            backend.resetText()
            stack.push(typingPage)
        }
    }

    Button {
        id: clearData

        anchors.top: title.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Clear user data")
        font.pointSize: 12
        onClicked: {
            backend.clearUserData()
            backend.resetText()
            stack.push(homePage)
        }
    }

    Button {
        id: deleteAccount

        anchors.top: clearData.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Delete account")
        font.pointSize: 12
        onClicked: {
            backend.deleteAccount()
            backend.setUserName("")
            stack.push(homePage)
        }
    }
}

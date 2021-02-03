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

    Rectangle {
        id: configBox
        width: 0.9*parent.width
        height: 0.8*parent.height
        color: "#f3f4f4"
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0.05*parent.height

        Frame {
            id: frame1

            width: 0.98*parent.width
            height: 0.2*parent.height
            anchors.top: parent.top
            anchors.topMargin: 0.01*parent.width
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                id: config1;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Clear data history:"
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
            }

            Label {
                id: config11;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Deleting your data is permanent, but your profile will remain active."
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
                anchors.top: config1.bottom
                anchors.topMargin: 0
                anchors.right: clearDataButton.left
                anchors.rightMargin: 0.02*parent.width
            }

            Button {
                id: clearDataButton

                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 0.01*parent.width
                text: qsTr("Clear")
                font.pointSize: 12
                onClicked: {
                    backend.clearUserData()
                    backend.resetText()
                    stack.push(homePage)
                }
            }
        }

        Frame {
            id: frame2

            width: 0.98*parent.width
            height: 0.2*parent.height
            anchors.top: frame1.bottom
            anchors.topMargin: 0.01*parent.width
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                id: config2;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Delete profile:"
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
            }

            Label {
                id: config21;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Deleting your profile is permanent and will remove all saved data."
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
                anchors.top: config2.bottom
                anchors.topMargin: 0
                anchors.right: deleteProfileButton.left
                anchors.rightMargin: 0.02*parent.width
            }

            Button {
                id: deleteProfileButton

                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 0.01*parent.width
                text: qsTr("Delte")
                font.pointSize: 12
                onClicked: {
                    backend.deleteAccount()
                    backend.setUserName("")
                    stack.push(homePage)
                }
            }
        }
    }
}

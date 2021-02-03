import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    id: settingsScreen
    Image {
        id:backgroundImage;
        anchors.fill:parent;
        source: "qrc:/img/images/hexagon.jpg";
    }

    Text {
        id: title;

        font.family: "serif"
        text: "Options";
        font.pixelSize: 19
        font.italic: true
        font.bold: true
        x: parent.width/2 - title.width/2;
        y: parent.height/35;
    }

    Button {
        id: continueButton
        text: qsTr("Continue practicing")

        checkable: true
        font.bold: true
        font.family: "serif"
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
        id: settingBox
        width: 0.9*parent.width
        height: 0.8*parent.height
        color: "#d1d8d8"
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
                id: setting1;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Clear data history:"
                font.family: "serif"
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
            }

            Label {
                id: setting11;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Deleting your data is permanent, but your profile will remain active."
                font.family: "serif"
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
                anchors.top: setting1.bottom
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
                clip: false
                layer.mipmap: true
                highlighted: true
                font.bold: true
                font.family: "serif"
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
                id: setting2;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Delete profile:"
                font.family: "serif"
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
            }

            Label {
                id: setting21;

                font.pointSize: 12
                wrapMode: Text.WordWrap
                text: "Deleting your profile is permanent and will remove all saved data."
                font.family: "serif"
                anchors.left: parent.left
                anchors.leftMargin: 0.01*parent.width
                anchors.top: setting2.bottom
                anchors.topMargin: 0
                anchors.right: deleteProfileButton.left
                anchors.rightMargin: 0.02*parent.width
            }

            Button {
                id: deleteProfileButton

                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 0.01*parent.width
                text: qsTr("Delete")
                highlighted: true
                font.bold: true
                font.family: "serif"
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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

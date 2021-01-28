import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    id: page02

    visible: true
    anchors.topMargin: 0
    Image {
        id: backgroundImage02
        anchors.topMargin: 0
        anchors.fill: parent
        source: "qrc:/img/images/background.png"
    }

    Text {
        id: title02
        x: parent.width/2 - title02.width/2;
        text: "Master The Keyboard"
        anchors.top: parent.top
        anchors.topMargin: 35
        font.family: "serif"
        font.pixelSize: parent.height/10
    }

    Rectangle {
        id: loginBox
        anchors.centerIn: parent
        width: 349
        height: 249
        color: "#f3f4f4"
        radius: 30

        Text {
            id: element
            x: 128
            y: 35
            width: 88
            height: 26
            text: qsTr("Login")
            font.family: "Tahoma"
            lineHeight: 1
            fontSizeMode: Text.Fit
            textFormat: Text.AutoText
            elide: Text.ElideNone
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 21
        }

        TextField {
            id: textUsername
            x: 51
            y: 88
            width: 242
            height: 42
            font.pointSize: 10
            transformOrigin: Item.Center
            horizontalAlignment: Text.AlignLeft
            onTextChanged: backend.userNameInput = text;
            TextEdit {
                selectByMouse: true
                Text {
                    x: 12
                    y: 5
                    width: 92
                    height: 32
                    color: "#aaaaaa"
                    text: "Username"
                    font.bold: false
                    font.pointSize: 10
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    visible: !textUsername.text
                }
                wrapMode: Text.Wrap
            }
        }

        Button {
            id: buttonsignIn
            x: 51
            y: 182
            width: 99
            height: 32
            text: qsTr("Sign in")
            font.pointSize: 11
            font.bold: false
            enabled: textUsername.text
            onClicked: {
                backend.signInUser()
            }
        }

        Button {
            id: buttonRegister
            x: 194
            y: 182
            width: 99
            height: 32
            text: qsTr("Register")
            font.pointSize: 11
            font.bold: false
            enabled: textUsername.text
            onClicked: {
                backend.registerUser()
            }
        }

        Label {
            id: userInfo
            x: 51
            y: 136
            width: 242
            height: 28
            color: "#ff0000"
            text: "*User not foud."
            visible: false
            verticalAlignment: Text.AlignVCenter
        }
    }

    Button {
        id: typingPageButton

        text: qsTr("Typing Page")
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 63
        onClicked: {
            mystackview.push(typingPage);
        }
    }
}

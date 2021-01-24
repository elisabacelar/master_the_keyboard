import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    id: page02
    x: 0
    y: 0
    width: 1000
    height: 650
    visible: true
    anchors.topMargin: 0
    Image {
        id: backgroundImage02
        anchors.topMargin: 0
        anchors.fill: parent
        source: "./images/background.png"
    }

    Text {
        id: title02
        x: 188
        y: 48
        text: "Master The Keyboard"
        font.family: "serif"
        font.pixelSize: parent.height/10
    }

    Rectangle {
        id: loginBox
        x: 292
        y: 177
        color: "#f3f4f4"
        radius: 30
        anchors.rightMargin: 292
        anchors.leftMargin: 292
        anchors.bottomMargin: 177
        anchors.topMargin: 177
        anchors.fill: parent

        Button {
            id: buttonsignIn
            x: 145
            y: 193
            width: 126
            height: 32
            text: qsTr("Log in")
            onClicked: {
                if(textUsername.text && textPassword.txt)
                {
                    if(backend.signInUser(textUsername.txt, textPassword.txt))
                    {
                        textUsername.clear();
                        textPassword.clear();
                    }
                }
            }
        }

        Text {
            id: element
            x: 167
            y: 31
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
            x: 89
            y: 77
            width: 242
            height: 42
            transformOrigin: Item.Center
            horizontalAlignment: Text.AlignLeft
            TextEdit {
                selectByMouse: true
                Text {
                    x: 12
                    y: 5
                    width: 60
                    height: 32
                    color: "#aaaaaa"
                    text: "Username"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    visible: !textUsername.text
                }
                wrapMode: Text.Wrap
            }
        }

        TextField {
            id: textPassword
            x: 89
            y: 135
            width: 242
            height: 42
            echoMode: TextInput.Password
            horizontalAlignment: Text.AlignLeft
            TextEdit {
                selectByMouse: true
                Text {
                    x: 12
                    y: 5
                    width: 69
                    height: 32
                    color: "#aaaaaa"
                    text: "Password"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    visible: !textPassword.text
                }
                wrapMode: Text.Wrap
            }
        }

        Button {
            id: buttonRegister
            x: 145
            y: 241
            width: 126
            height: 32
            text: qsTr("Register")
            onClicked: {
                if(textUsername.text && textPassword.txt)
                {
                    backend.registerUser(textUsername.txt, textPassword.txt)
                    textUsername.clear();
                    textPassword.clear();
                }
            }
        }
    }

    Button {
        id: typingPageButton
        x: 450
        y: 501
        text: qsTr("Typing Page")
    }

    anchors.leftMargin: 0
    anchors.margins: root.globalMargin
    anchors.fill: parent
    anchors.bottomMargin: 0
    anchors.rightMargin: 0
}

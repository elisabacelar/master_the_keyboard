import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    id: homeScreen
    Layout.minimumWidth: 128
    Layout.minimumHeight: 72
    Image {
        id:backgroundImage;

        anchors.fill:parent;
        source: "qrc:/img/images/background.png";
    }

    Text {
        id: backgroundSource;

        font.family: "serif";
        font.pixelSize: 10;
        text: qsTr("Image by Michael Schwarzenberger from Pixabay <https://pixabay.com/>");
        x: parent.width-width;
        y: parent.height-height;
    }

    Text {
        id: title;

        font.family: "serif";
        font.pixelSize: parent.height/7;
        text: "Master The Keyboard";
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: parent.height/10
        x: parent.width/2 - title.width/2;
        color: "#0c1faa"
    }

    Button {
        id: starButton

        text: qsTr("Get Started")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            if(backend.userNameInput.length > 0)
            {
                stack.push(typingPage);
                login.visible = false
            }
            else
            {
                login.visible = true
                //stack.push(signInPage);
            }
        }
    }


    Item {
        id: login

        visible: false
        x: 160
        y: 142
        width: 320
        height: 320
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: loginBox
            width: 320
            height: 320
            color: "#f3f4f4"
            radius: 30

            Text {
                id: loginTitle
                x: 138
                y: 30
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
                y: 86
                width: 242
                height: 42
                anchors.horizontalCenterOffset: -4
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 10
                transformOrigin: Item.Center
                horizontalAlignment: Text.AlignLeft
                TextEdit {
                    selectByMouse: true
                    Text {
                        x: 11
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
                id: signInButton
                x: 35
                y: 205
                width: 110
                height: 32
                text: qsTr("Sign in")
                anchors.horizontalCenterOffset: -72
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 11
                font.bold: false
                enabled: textUsername.text
                onClicked: {
                    userInfo.text = backend.signInUser(textUsername.text)
                }
            }

            Button {
                id: registerButton
                x: 175
                y: 205
                width: 110
                height: 32
                text: qsTr("Create")
                font.pointSize: 11
                font.bold: false
                enabled: textUsername.text
                onClicked: {
                    userInfo.text = backend.registerUser(textUsername.text)
                }
            }

            Label {
                id: userInfo
                y: 136

                width: 242
                height: 40
                color: "#ff0000"
                wrapMode: Text.WordWrap
                anchors.horizontalCenterOffset: -4
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
            }

            Button {
                id: typingPageButton
                x: 106
                y: 257

                text: qsTr("Continue")
                enabled: (backend.userNameInput.length > 0)
                onClicked: {
                    stack.push(typingPage);
                }
            }
        }
    }
}

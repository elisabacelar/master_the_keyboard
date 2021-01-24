import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2

import local.api.backend 1.0

//ApplicationWindow {
//    id: root
//    width: 300
//    height: 480
//    visible: true

//    BackEnd {
//        id: backend
//    }

//    TextField {
//        text: backend.inputText
//        placeholderText: qsTr("User name")
//        anchors.centerIn: parent

//        onEditingFinished: backend.inputText = text
//    }
//}

ApplicationWindow {
    id: root;

    height: 650;
    title: qsTr("Master The Keyboard");
    visible: !loginWindow.visible;
    width: 1000;
    BackEnd {
        id: backend;

        loginWindowVisibility: loginWindow.visible;
    }
    Image {
        id:backgroundImage;

        anchors.fill:parent;
        source: "./images/background.png";
    }
    Item {
        id: applicationArea;

        height: 550;
        width: 800;
        x: (parent.width-width)/2;
        Rectangle {
            id: backgroundColor;

            anchors.fill: parent;
            color: "#FFFFCC";
            opacity: 0.9;
        }
        Text {
            id: title;

            font.family: "serif";
            font.pixelSize: parent.height/10;
            text: "Master The Keyboard";
            x: parent.width/10;
            y: parent.height/20;
        }
        Item {
            id: correctnessDisplay;

            height: correctnessValue.height;
            width: 1*textDisplay.width/5;
            x: textDisplay.x+textDisplay.width/5
            y: 1*(parent.height-height)/4;
            Rectangle {
                id: correctnessDisplayBorder;

                border.color: "#000000";
                color: "transparent";
                height: parent.height;
                width: parent.width;

            }
            Text {
                id: correctnessValue;

                font.family: "serif";
                font.pixelSize: 32;
                textFormat: Text.RichText;
                text: backend.correctness;
                width: parent.width;
                wrapMode: Text.Wrap;
            }
        }
        Item {
            id: timeDisplay;

            height: timeValue.height;
            width: 1*textDisplay.width/5;
            x: textDisplay.x+3*textDisplay.width/5
            y: 1*(parent.height-height)/4;
            Rectangle {
                id: timeDisplayBorder;

                border.color: "#000000";
                color: "transparent";
                height: parent.height;
                width: parent.width;

            }
            Text {
                id: timeValue;

                font.family: "serif";
                font.pixelSize: 32;
                textFormat: Text.RichText;
                text: backend.correctness;
                width: parent.width;
                wrapMode: Text.Wrap;
            }
        }
        Item {
            id: textDisplay;

            height: outputText.height;
            width: 3*parent.width/5;
            x: 1*parent.width/5;
            y: 7*(parent.height-height)/12;
            Rectangle {
                id: textDisplayBorder;

                border.color: "#000000";
                color: "transparent";
                height: parent.height;
                width: parent.width;

            }
            Text {
                id: outputText;

                font.family: "serif";
                font.pixelSize: 20;
                textFormat: Text.RichText;
                text: backend.displayedText;
                width: parent.width;
                wrapMode: Text.Wrap;
            }
        }
        Rectangle {
            id: userInputBox;

            color: "#FFFFFF";
            height: 2*parent.height/20;
            width: 9*parent.width/10;
            x: parent.width/20;
            y: 8*parent.height/10;
            TextEdit {
                id: userInput;

                anchors.fill: parent;
                onTextChanged: backend.inputText = text;
                width: parent.width;
                wrapMode: Text.Wrap;
                Text {
                    text: "Type something...";
                    color: "#AAAAAA"
                    visible: !parent.text
                }
            }
        }
    }
    Text {
        id: backgroundSource;

        font.family: "serif";
        font.pixelSize: 10;
        text: qsTr("Image by Michael Schwarzenberger from Pixabay <https://pixabay.com/>");
        x: parent.width-width;
        y: parent.height-height;
    }
    Button {
        id: newUserButton;

        height: loginButton.height;
        onClicked: loginWindow.showNormal();
        text: qsTr("New User");
        width: 100;
    }
    Window {
        id: loginWindow;
        color: "#CCCCCC";
        height: 200;
        title: qsTr("Login");
        visible: true;
        width: 200;
        x: (root.width-width)/2;
        y: (root.height-height)/2;
        Rectangle {
            id: userNameInputBox;

            color: "#FFFFFF";
            height: 25;
            width: 180;
            x: parent.width/20;
            y: 3*parent.height/10;
            TextField {
                id: userNameInputText;

                anchors.fill: parent;
                onFocusChanged: backend.userNameInput = text;
                width: parent.width;
                wrapMode: Text.Wrap;
                Text {
                    text: "Username";
                    color: "#AAAAAA"
                    visible: !parent.text
                }
            }
        }
        Rectangle {
            id: passwordInputBox;

            color: "#FFFFFF";
            height: 25;
            width: 180;
            x: parent.width/20;
            y: 9*parent.height/20;
            TextField {
                id: passwordInputText;

                anchors.fill: parent;
                echoMode: TextInput.Password;
                onFocusChanged: backend.passwordInput = text;
                width: parent.width;
                wrapMode: Text.Wrap;
                Text {
                    text: "Password";
                    color: "#AAAAAA"
                    visible: !parent.text
                }
            }
        }
        Button {
            id: loginButton;

            height: 25;
            onClicked: loginWindow.close();
            text: qsTr("Login");
            width: 70;
            x: passwordInputBox.x+passwordInputBox.width/18;
            y: 7*parent.height/10;
        }
        Button {
            id: registerButton;

            height: 25;
            onClicked: loginWindow.close();
            text: qsTr("Register");
            width: 70;
            x: passwordInputBox.x+10*passwordInputBox.width/18;
            y: 7*parent.height/10;
        }
    }
}

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

            Button {
                id: next_button
                x: 541
                y: 345
                text: qsTr("Next")
                onClicked: {
                    backend.resetText()
                }
            }
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
            id: speedDisplay;

            height: speedValue.height;
            width: 1*textDisplay.width/5;
            x: textDisplay.x+3*textDisplay.width/5
            y: 1*(parent.height-height)/4;
            Rectangle {
                id: speedDisplayBorder;

                border.color: "#000000";
                color: "transparent";
                height: parent.height;
                width: parent.width;

            }
            Text {
                id: speedValue;

                font.family: "serif";
                font.pixelSize: 32;
                textFormat: Text.RichText;
                text: backend.speed;
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
            TextField {
                id: userInput;

                text: backend.inputText
                onTextChanged: backend.inputText = text
                placeholderText: qsTr("Start typing!")
                anchors.centerIn: parent
                anchors.fill: parent;
                width: parent.width;
                wrapMode: Text.Wrap;
                visible: !parent.text
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
        Button {
            id: loginButton;

            height: 25;
            text: qsTr("Login");
            width: 70;
            x: userNameInputBox.x+userNameInputBox.width/18;
            y: 7*parent.height/10;
            onClicked: {
                if(userNameInputText.text)
                {
                    if(backend.signInUser(userNameInputText.txt))
                    {
                        userNameInputText.clear();
                    }
                }
                loginWindow.close();
            }

        }
        Button {
            id: registerButton;

            height: 25;
            text: qsTr("Register");
            width: 70;
            x: userNameInputBox.x+10*userNameInputBox.width/18;
            y: 7*parent.height/10;
            onClicked: {
                if(userNameInputText.text)
                {
                    backend.registerUser(userNameInputText.txt)
                    userNameInputText.clear();
                }
                loginWindow.close();
            }
        }
    }
}

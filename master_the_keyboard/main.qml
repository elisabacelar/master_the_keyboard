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
    visible: true;
    width: 1000;
    BackEnd {
        id: backend;
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
                    userInput.clear()
                    backend.setSampleText(20)
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
            id: textDisplay;

            height: outputText.height;
            width: 3*parent.width/5;
            x: 1*parent.width/5;
            y: (parent.height-height)/2;
            Rectangle {
                id: displayBorder;

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
}

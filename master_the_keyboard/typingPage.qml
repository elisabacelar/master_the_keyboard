import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    id: page01
    x: 0
    y: 0
    width: 1000
    height: 650
    visible: true
    anchors.rightMargin: 0
    anchors.leftMargin: 0
    anchors.bottomMargin: 0
    anchors.topMargin: 0
    anchors.margins: root.globalMargin
    anchors.fill: parent

    Image {
        id:backgroundImage;
        anchors.topMargin: 0

        anchors.fill:parent;
        source: "./images/background.png";
    }


    Text {
        id: backgroundSource;
        x: 668
        y: 638

        font.family: "serif";
        font.pixelSize: 10;
        text: qsTr("Image by Michael Schwarzenberger from Pixabay <https://pixabay.com/>");
    }

    Rectangle {
        id: applicationArea
        x: 82
        y: 48
        color: "#ffffcc"
        opacity: 0.8
        anchors.rightMargin: 25
        anchors.leftMargin: 25
        anchors.bottomMargin: 25
        anchors.topMargin: 25
        anchors.fill: parent

        Text {
            id: title01
            x: 142
            y: 42
            width: 588
            height: 78
            text: "Master The Keyboard"
            fontSizeMode: Text.Fit
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "serif"
            font.pixelSize: parent.height/10
        }

        Item {
            id: textDisplay;
            y: 277

            height: outputText.height;
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.right: parent.right
            anchors.rightMargin: 100
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
            x: 48
            y: 448

            color: "#FFFFFF";
            height: 2*parent.height/20;
            width: 9*parent.width/10;
            TextEdit {
                id: userInput;

                onTextChanged: backend.inputText = text;
                width: parent.width;
                selectByMouse: false
                wrapMode: Text.Wrap;
                Text {
                    text: "Type something...";
                    color: "#AAAAAA"
                    visible: !parent.text
                }
            }
        }

        Button {
            id: next_button
            x: 750
            y: 374
            text: qsTr("Next")
            onClicked: {
                userInput.clear()
                backend.setSampleText(20)
            }
        }

        Button {
            id: initialPageButton
            x: 394
            y: 374
            text: qsTr("Initial page")
        }
    }
}

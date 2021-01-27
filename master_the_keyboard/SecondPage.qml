import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    id: element
    visible: true;

    Image {
        id:backgroundImage;
        anchors.fill:parent;
        source: "qrc:/img/images/background.png";
    }

    Text {
        id: title;

        font.family: "serif";
        font.pixelSize: parent.height/25;
        text: "Master The Keyboard";
        x: parent.width/2 - title.width/2;
        y: parent.height/35;
    }

    Item {
        id: textDisplay;

        height: outputText.height*1.3;
        width: 3*parent.width/5;
        x: parent.width/20;
        y: (parent.height-height)/9;
        Rectangle {
            id: textDisplayBorder;

            border.color: "#000000";
            color: "#dfd4d4"
            opacity: 0.95
            height: parent.height;
            width: parent.width;

        }
        Text {
            id: outputText;

            font.family: "serif";
            font.pixelSize: 20;
            textFormat: Text.RichText;
            text: backend.displayedText;
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            width: parent.width;
            wrapMode: Text.Wrap;
        }
    }

    Button {
        id: next_button

        y: textDisplay.y
        anchors.left: textDisplay.right
        anchors.leftMargin: 20
        width: 2*textDisplay.height
        height: textDisplay.height
        text: qsTr("Next")

        onClicked: {
            backend.resetText()
        }
    }

    Rectangle {
        id: userInputBox;

        color: "#FFFFFF";
        anchors.top: textDisplay.bottom
        anchors.topMargin: 50
        opacity: 0.8

        height: textDisplay.height;
        width: textDisplay.width;
        x: parent.width/20;


        TextField {
            id: userInput;

            text: backend.inputText
            font.pixelSize: 20
            onTextChanged: backend.inputText = text
            placeholderText: qsTr("Start typing!")
            anchors.centerIn: parent
            anchors.fill: parent;
            width: parent.width;
            wrapMode: Text.Wrap;
            visible: !parent.text
        }
    }

    Item {
        x: 20
        anchors.top: userInputBox.bottom
        anchors.topMargin: 70
        Item {
            id: correctnessDisplay

            width: 120;
            height: 30

            Rectangle {
                id: correctnessDisplayBorder;

                border.color: "#000000";
                width: parent.width;
                height: 30
                color: "#ffffff"
                radius: 3
                opacity: 0.9
            }

            Text {
                id: correctnessValue;
                x: 0
                y: 0

                font.family: "serif";
                font.pixelSize: 20;
                textFormat: Text.RichText;
                text: backend.correctness;
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: parent.width;
                height: 30
                wrapMode: Text.Wrap;
            }
        }

        Label {
            id: labelAccuracy

            anchors.bottom: parent.top
            anchors.bottomMargin: 10
            width: 120
            height: 20
            text: qsTr("Accuracy")
            font.family: "serif";
            font.pixelSize: 20;
            renderType: Text.QtRendering
            textFormat: Text.AutoText
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Item {
        x: 200
        anchors.top: userInputBox.bottom
        anchors.topMargin: 70
        Item {
            id: speedDisplay

            width: 120;
            height: 30

            Rectangle {
                id: speedDisplayBorder;

                border.color: "#000000";
                width: parent.width;
                height: 30
                color: "#ffffff"
                radius: 3
                opacity: 0.9
            }

            Text {
                id: speedValue;
                x: 0
                y: 0

                font.family: "serif";
                font.pixelSize: 20;
                textFormat: Text.RichText;
                text: backend.speed;
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: parent.width;
                height: 30
                wrapMode: Text.Wrap;
            }
        }

        Label {
            id: labelSpeed

            anchors.bottom: parent.top
            anchors.bottomMargin: 10
            width: 120
            height: 20
            text: qsTr("Speed")
            font.family: "serif";
            font.pixelSize: 20;
            renderType: Text.QtRendering
            textFormat: Text.AutoText
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}

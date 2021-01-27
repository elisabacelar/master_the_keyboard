import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {

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
        x: parent.width/2 - title.width/2;
        y: parent.height/2 - title.height/2;
        color: "#0c1faa"
    }

    GridView {
        id: mygridview
        width: parent.width
        height: parent.height
        cellWidth: parent.width / 4
        cellHeight: 5
        anchors.centerIn: parent
        visible: true;

        model: ListModel {
            ListElement {
                name: 'Page 1'
            }
            ListElement {
                name: 'Page 2'
            }
            ListElement {
                name: 'Page 3'
            }
            ListElement {
                name: 'Page 4'
            }
        }
        delegate: Button {
            id: mybutton
            text: name
            onClicked: {
                load_page(text);
            }
        }
    }
}

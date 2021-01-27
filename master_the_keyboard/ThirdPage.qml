import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {    
    Rectangle {
        anchors.fill: parent
        color: 'green'
        visible: true;
        Button {
            anchors.centerIn: parent
            text: 'Exit'
            onClicked: {
                Qt.quit();
            }
        }
    }
}

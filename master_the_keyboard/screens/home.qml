import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

Item {
    ListView {
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        visible: true;
        model: ListModel {
            ListElement {
                mytext: 'Juan'
            }
            ListElement {
                mytext: 'Pedro'
            }
            ListElement {
                mytext: 'Ana'
            }
            ListElement {
                mytext: 'Luis'
            }
            ListElement {
                mytext: 'José'
            }
        }
        delegate: Button {
            text: mytext
        }
    }
}

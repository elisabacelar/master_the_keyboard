import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

ApplicationWindow {
    id: root;
    width: 1000;
    height: 650;
    title: qsTr("Master The Keyboard");
    visible: true;

    BackEnd {
        id: backend;
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("<")
                onClicked: mystackview.pop()
            }
            Label {
                text: "Home Screen"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }

    StackView {
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: parent.top
        }

        id: mystackview
        initialItem: typingPage
    }

    Component {
        id: second_page
        SecondPage {}
    }
    Component {
        id: third_page
        ThirdPage {}
    }
    Component {
        id: typingPage
        Typing {}
    }
    Component {
        id: fourth_page
        FourthPage {}
    }


    function load_page(page) {
        switch (page) {
        case 'Page 1':
            mystackview.push(typingPage);
            break;
        case 'Page 2':
            mystackview.push(second_page);
            break;
        case 'Page 3':
            mystackview.push(third_page);
            break;
        }
    }
}

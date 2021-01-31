import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import local.api.backend 1.0

ApplicationWindow {
    id: root;
    width: 1280;
    height: 720;
    title: qsTr("Master The Keyboard");
    visible: true;

    BackEnd {
        id: backend;
    }

    header: ToolBar {
        id: control
        implicitHeight: 40
        RowLayout {
            ToolButton {
                id: homeButtom

                anchors.leftMargin: 0
                anchors.topMargin: 0
                width: 40
                height: 40
                text: qsTr("HOME")
                onClicked: stack.push(homePage);
            }

            ToolButton {
                id: menuButtom

                anchors.topMargin: 0
                width: 40
                height: 40
                text: qsTr("MENU")
                onClicked: stack.push(third_page);
            }

            ToolButton {
                id: logoutButton

                anchors.right: root.right
                anchors.rightMargin: 10
                anchors.topMargin: 0
                height: 40
                text: qsTr("LOG OUT")
                visible: (backend.userNameInput.length > 0)
                onClicked:
                {
                    backend.setUserName("")
                    stack.push(homePage);
                }
            }
        }
    }

    StackView {
        id:stack
        anchors.fill: parent
        initialItem: homePage
    }

    Component {
        id: homePage
        HomePage {}
    }
    Component {
        id: typingPage
        Typing {}
    }
    Component {
        id: third_page
        ThirdPage {}
    }
}

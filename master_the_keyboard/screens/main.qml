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
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    text: qsTr("<")
                    onClicked: mystackview.push(homePage);
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
        initialItem: homePage
    }

    Component {
        id: signInPage
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
    Component {
        id: homePage
        HomePage {}
    }


    function loadPage(page) {
        switch (page) {
        case 'Page 1':
            mystackview.push(homePage);
            break;
        case 'Page 2':
            mystackview.push(typingPage);
            break;
        case 'Page 3':
            mystackview.push(third_page);
            break;
        case 'Page 4':
            mystackview.push(signInPage);
            break;
        }
    }
}

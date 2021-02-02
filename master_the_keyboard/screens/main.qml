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
        height: 40
        width: parent.width
        RowLayout {
            width: parent.width
            ToolButton {
                id: homeButtom

                width: 40
                height: parent.height
                text: qsTr("HOME")
                onClicked: stack.push(homePage);
            }

            ToolButton {
                id: configButtom

                width: 40
                height: parent.height
                anchors.left: homeButtom.right
                anchors.leftMargin: 10
                text: qsTr("OPTIONS")
                visible: (backend.userNameInput.length > 0)
                onClicked:
                {
                    stack.push(configurationPage);
                }
            }

            ToolButton {
                id: resultsButtom

                width: 40
                height: parent.height
                anchors.left: configButtom.right
                anchors.leftMargin: 10
                text: qsTr("RESULTS")
                visible: (backend.userNameInput.length > 0)
                onClicked:
                {
                    backend.getDataHistory()
                    stack.push(third_page);
                }
            }

            ToolButton {
                id: logoutButton

                height: parent.height
                anchors.left: resultsButtom.right
                anchors.leftMargin: 10
                text: qsTr("LOGOUT")
                visible: (backend.userNameInput.length > 0)
                onClicked:
                {
                    backend.resetText()
                    backend.setUserName("")
                    stack.push(homePage);
                }
            }

            Item {
                id: profile

                visible: (backend.userNameInput.length > 0)
                implicitWidth: profileName.width + profileImage.width
                height: 40
                anchors.right: parent.right
                anchors.rightMargin: 10


                Text {
                    id: profileName

                    height: 40
                    anchors.right: profile.right
                    anchors.rightMargin: 0
                    font.family: "serif";
                    text: backend.userNameInput
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 18
                    fontSizeMode: Text.VerticalFit
                }

                Rectangle {
                    id: profileImage

                    width: 40
                    height: 40
                    anchors.right: profileName.left
                    anchors.rightMargin: 5
                    color: "transparent"
                    Image {
                        anchors.fill: parent
                        source: "qrc:/img/images/profile-icon.png"
                    }
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
    Component {
        id: configurationPage
        ConfigPage {}
    }
}

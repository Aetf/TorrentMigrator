import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    id: root

    property real verticalSpacing: 5
    property real horizontalSpacing: 0
    property alias title: titleLabel.text
    property var backendModel: dummyBackendModel

    RowLayout {
        id: backendChooser
        anchors {
            top: root.top; topMargin: verticalSpacing
            left: root.left; leftMargin: horizontalSpacing
            right: root.right; rightMargin: horizontalSpacing
        }

        Label {
            id: titleLabel
        }
        ComboBox {
            id: backendCombo
            model: backendModel
            textRole: "name"

            onCurrentIndexChanged: {
                if (currentIndex != -1) {
                    backendConfigPanel.show(model.get(currentIndex).configPanelSource);
                }
            }
        }
    }

    Item {
        id: backendConfigPanel
        anchors {
            top: backendChooser.bottom; topMargin: verticalSpacing
            left: root.left; leftMargin: horizontalSpacing
            right: root.right; rightMargin: horizontalSpacing
        }
        clip: true

        property alias source: panelPlaceHolder.source

        function show(src) {
            if (typeof src !== undefined) {
                backendConfigPanel.source = src;
            }

            backendConfigPanel.state = "expanded";
        }

        function hide() {
            backendConfigPanel.state = "collapsed";
        }

        Loader {
            id: panelPlaceHolder
            anchors.fill: parent
        }

        MouseArea {
            anchors.fill: panelPlaceHolder

            onClicked: backendConfigPanel.hide()
        }

        state: "collapsed"
        states: [
            State {
                name: "collapsed"
                PropertyChanges {
                    target: backendConfigPanel
                    implicitHeight: 0
                }
            },
            State {
                name: "expanded"
                PropertyChanges {
                    target: backendConfigPanel
                    implicitHeight: 70
                }
            }
        ]
        transitions: [
            Transition {
                NumberAnimation {
                    property: "implicitHeight"
                    duration: 200
                    easing.type: Easing.InOutQuart
                }
            }
        ]
    }

    Item {
        id: torrentsList
        anchors {
            top: backendConfigPanel.bottom; topMargin: verticalSpacing
            bottom: root.bottom; bottomMargin: verticalSpacing
            left: root.left; leftMargin: horizontalSpacing
            right: root.right; rightMargin: horizontalSpacing
        }

        Rectangle {
            anchors.fill: parent
            color: Qt.lighter("red")
        }
    }

    ListModel {
        id: dummyBackendModel
        ListElement {
            name: "uTorrent"
            configPanelSource: "uTorrentConfigPanel.qml"
        }
        ListElement {
            name: "qBittorrent"
            configPanelSource: "qBittorrentConfigPanel.qml"
        }
    }
}

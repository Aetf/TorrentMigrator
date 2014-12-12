import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RecordsModel 1.0

Item {
    id: root

    property real verticalSpacing: 5
    property real horizontalSpacing: 0
    property alias title: titleLabel.text
    property alias backendModel: backendCombo.model

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
            model: dummyBackendModel
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

            Connections {
                target: panelPlaceHolder.item
                onAccepted: {
                    recordsModel.accessor = panelPlaceHolder.item.getConfigedAccessor();
                    backendConfigPanel.hide();
                }
            }
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
        anchors {
            top: backendConfigPanel.bottom; topMargin: verticalSpacing
            bottom: root.bottom; bottomMargin: verticalSpacing
            left: root.left; leftMargin: horizontalSpacing
            right: root.right; rightMargin: horizontalSpacing
        }

        TableView {
            id: torrentsList
            anchors.fill: parent

            Repeater {
                model: recordsModel.columnRoles()

                TableViewColumn {
                    role: recordsModel.roleName(modelData)
                    title: recordsModel.headerData(recordsModel.columnRoleToSection(modelData))
                    width: 100
                }
            }

            model: recordsModel;
        }

        RecordsModel {
            id: recordsModel;
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

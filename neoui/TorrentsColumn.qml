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
        Button {
            id: backendConfigButton
            checkable: true
            checked: backendConfigPanel.expanded
            text: qsTr("Show Configure")
            onClicked: {
                backendConfigPanel.toggle();
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
        property bool expanded: false

        onExpandedChanged: {
            backendConfigButton.checked = expanded;
        }

        function toggle() {
            if (expanded) hide();
            else show();
        }

        function show(src) {
            if (src) {
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
                    height: 0
                    expanded: false
                }
            },
            State {
                name: "expanded"
                PropertyChanges {
                    target: backendConfigPanel
                    height: panelPlaceHolder.implicitHeight
                    expanded: true
                }
            }
        ]
        transitions: [
            Transition {
                NumberAnimation {
                    property: "height"
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
            model: recordsModel;

            function clearAndDestoryColumns() {
                while (columnCount > 0) {
                    var column = getColumn(0);
                    removeColumn(0);
                    column.destroy();
                }
            }

            function populateHeaderData() {
                clearAndDestoryColumns();
                for (var i = 0; i < model.columnRoles().length; i++) {
                    var role = model.columnRoles()[i],
                        roleName = model.roleName(role),
                        section = model.columnRoleToSection(role),
                        title = model.headerData(section);

                    addColumn(headerComponent.createObject(torrentsList,
                                     { "role": roleName, "title": title }));
                }
            }

            onModelChanged: {
                model.modelReset.connect(populateHeaderData);
            }
        }

        Component {
            id: headerComponent
            TableViewColumn { }
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

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import RecordsModel 1.0
import "3rdparty"

Item {
    id: root

    property real verticalSpacing: 5
    property real horizontalSpacing: 0
    property alias title: titleLabel.text
//    property alias backendModel: backendCombo.model
    property alias model: recordsModel
    property alias selection: torrentsList.selection

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
            model: RecordsAccessorFactory.availableAccessors
            textRole: "name"

            onCurrentIndexChanged: {
                if (currentIndex != -1) {
                    backendConfigPanel.show(model[currentIndex].configPanelSource);
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
            expanded = !expanded;
        }

        function show(src) {
            if (src) {
                backendConfigPanel.source = src;
            }

            backendConfigPanel.expanded = true;
        }

        Loader {
            id: panelPlaceHolder
            anchors.fill: parent

            Connections {
                target: panelPlaceHolder.item
                onAccepted: {
                    var args = panelPlaceHolder.item.getConfigedArgs();
                    var name = panelPlaceHolder.item.name;
                    recordsModel.setAccessor(name, args);
                    backendConfigPanel.expanded = false;
                }
            }
        }

        states: [
            State {
                name: "collapsed"
                when: !backendConfigPanel.expanded
                PropertyChanges {
                    target: backendConfigPanel
                    height: 0
                }
            },
            State {
                name: "expanded"
                when: backendConfigPanel.expanded
                PropertyChanges {
                    target: backendConfigPanel
                    height: panelPlaceHolder.implicitHeight
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
            selectionMode: SelectionMode.MultiSelection

            onModelChanged: {
                model.modelReset.connect(populateHeaderData);
            }

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

                    var col = addColumn(headerComponent.createObject(torrentsList,
                                     { "role": roleName, "title": title }));
                    if (role === ColumnRoles.NaturalIndexRole) {
                        col.width = 25;
                    }
                }
            }
        }

        CustomBusyIndicator {
            anchors.centerIn: torrentsList
            width: 250
            height: 250
            running: recordsModel.busy
            visible: recordsModel.busy

            bLines: 10
            bLength: 15
            bWidth: 7
            bRadius: 5
            bCorner: 1
            bSpeed: 100
            bTrail: 0.5
            bOpacity: 0.5
            bBgColor: "transparent"
        }

        Component {
            id: headerComponent
            TableViewColumn { }
        }

        RecordsModel {
            id: recordsModel;
        }
    }
}

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.1
import RecordsModel 1.0

ColumnLayout {
    id: root

    property alias btnTransferToRight: btnTransferToRight
    property alias btnTransferToLeft: btnTransferToLeft
    property real buttonHeight: 25
    property real buttonWidth: 25
    property real animationDuration: 350
    property int easingType: Easing.InOutQuart

    TransferButton {
        id: btnTransferToRight
        Layout.alignment: Qt.AlignCenter

        height: root.buttonHeight
        briefWidth: root.buttonWidth
        detailWidth: settingsButtonBox.fullWidth()
        briefText: "►"
        detailText: qsTr("Transfer To Right ►")
        animationDuration: root.animationDuration
        easingType: root.easingType

        state: detailSettings.state
    }

    Item {
        id: detailSettings
        Layout.alignment: Qt.AlignCenter
        Layout.preferredHeight: root.buttonHeight
        Layout.preferredWidth: root.buttonWidth

        property bool compact: true

        clip: true

        ListView {
            id: transformerList
            anchors.fill: parent
            implicitHeight: 200
            clip: true
            model: TransformerModel { }

            footer: Rectangle {
                height: 25
                width: ListView.view.width
                color: "transparent"
            }
            delegate: Column {
                id: itemRoot
                Text {
                    id: briefText
                    width: itemRoot.ListView.view.width
                    text: model.name
                    horizontalAlignment: Text.AlignHCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: transformerList.currentIndex = index
                        onDoubleClicked: {
                            var st = itemRoot.state === "" ? "editing" : ""
                            itemRoot.state = st
                        }
                    }
                }
                Item {
                    id: detailEditWrapper
                    anchors.left: briefText.left
                    anchors.right: briefText.right
                    anchors.margins: 3
                    height: 0
                    enabled: false
                    visible: false
                    clip: true
                    TextArea {
                        id: detailEdit
                        width: parent.width
                        height: itemRoot.ListView.view.height - briefText.height - 3
                        inputMethodHints: Qt.ImhNoAutoUppercase
                        frameVisible: false
                        style: TextAreaStyle {
                            backgroundColor: "#BBFFFFFF"
                        }
                    }
                }

                states: State {
                    name: "editing"
                    PropertyChanges {
                        target: detailEditWrapper
                        height: detailEdit.height + 3
                        focus: true
                        enabled: true
                        visible: true
                    }
                    PropertyChanges {
                        target: itemRoot.ListView.view
                        interactive: false
                    }
                }
                transitions: Transition {
                    to: "editing"
                    reversible: true
                    SequentialAnimation {
                        ScriptAction {
                            script: {
                                flyout.enableDetect = itemRoot.state === "";
                                if (!flyout.enableDetect) flyout.show = false;
                            }
                        }
                        PropertyAction {
                            properties: "enabled,visible"
                        }
                        NumberAnimation {
                            properties: "height"
                            duration: 300
                            easing.type: Easing.InOutQuad
                        }

                        ScriptAction {
                            script: {
                                var pos = itemRoot.ListView.view.contentY
                                var destPos
                                itemRoot.ListView.view.positionViewAtIndex(
                                            index, ListView.Begining)
                                destPos = itemRoot.ListView.view.contentY
                                scrollAnim.from = pos
                                scrollAnim.to = destPos
                                scrollAnim.running = true
                            }
                        }
                    }
                }
            }
            NumberAnimation {
                id: scrollAnim
                target: transformerList
                property: "contentY"
                duration: 100
            }
            highlight: Rectangle {
                color: "lightblue"
                radius: 5
            }
            highlightResizeDuration: 50
        }

        FlyoutPanel {
            id: addMenu
            anchors.bottom: flyout.top
            anchors.horizontalCenter: flyout.horizontalCenter
            anchors.bottomMargin: 2
            enableDetect: false
            show: false

            property bool canPopup: flyout.show

            onCanPopupChanged: {
                if (!canPopup) show = false;
            }

            onShowChanged: {
                flyout.enableDetect = !show
            }

            Flickable {
                id: flickable
                height: root.buttonHeight
                width: detailSettings.width
                contentHeight: root.buttonHeight
                contentWidth: contentItem.childrenRect.width
                MouseArea {
                    anchors.fill: parent
                    onWheel: {
                        flickable.flick(wheel.angleDelta.y * 1.5, 0);
                    }
                }

                Row {
                    Button {
                        text: "PathRegex"
                        onClicked: {
                            addMenu.show = false;
                            var cur = transformerList.currentIndex
                            transformerList.model.insertRow(cur,
                                                            "PathRegexTransformer")
                        }
                    }
                    Button {
                        text: "DeviceMap"
                        onClicked: {
                            addMenu.show = false;
                            var cur = transformerList.currentIndex
                            transformerList.model.insertRow(cur,
                                                            "DeviceMapTransformer")
                        }
                    }
                }
            }
        }

        FlyoutPanel {
            id: flyout
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            enableDetect: false

            FusionButton {
                id: settingsButtonBox

                height: root.buttonHeight
                buttonWidth: root.buttonWidth
                animationDuration: root.animationDuration
                easingType: root.easingType
                compact: detailSettings.compact

                mainButton: Component {
                    Button {
                        implicitWidth: 25
                        iconSource: "qrc:/images/Gear_icon.png"
                        onClicked: {
                            detailSettings.compact = false
                        }
                    }
                }

                alternativeButton: Component {
                    Button {
                        implicitWidth: root.buttonWidth
                        iconSource: "qrc:/images/Yes_icon.png"
                        onClicked: {
                            detailSettings.compact = true
                        }
                    }
                }

                Button {
                    implicitWidth: root.buttonWidth
                    iconSource: "qrc:/images/Up_icon.png"
                    onClicked: {
                        var cur = transformerList.currentIndex
                        if (cur === 0)
                            return
                        transformerList.model.moveRow(cur, cur - 1)
                    }
                }
                Button {
                    implicitWidth: root.buttonWidth
                    iconSource: "qrc:/images/Down_icon.png"
                    onClicked: {
                        var cur = transformerList.currentIndex
                        if (cur === transformerList.model.rowCount() - 1)
                            return
                        transformerList.model.moveRow(cur, cur + 1)
                    }
                }
                Button {
                    id: addBtn
                    implicitWidth: root.buttonWidth
                    iconSource: "qrc:/images/Add_icon.png"
                    onClicked: {
                        addMenu.show = !addMenu.show;
                    }
                }
                Button {
                    implicitWidth: root.buttonWidth
                    iconSource: "qrc:/images/Subtract_icon.png"
                    onClicked: {
                        var cur = transformerList.currentIndex
                        transformerList.model.removeRow(cur)
                    }
                }
            }
        }

        states: [
            State {
                name: "compact"
                when: detailSettings.compact
                PropertyChanges {
                    target: detailSettings
                    Layout.preferredHeight: root.buttonHeight
                    Layout.preferredWidth: settingsButtonBox.compactWidth()
                }
                PropertyChanges {
                    target: flyout
                    enableDetect: false
                    show: true
                }
                PropertyChanges {
                    target: transformerList
                    visible: false
                }
            },
            State {
                name: "full"
                when: !detailSettings.compact
                PropertyChanges {
                    target: detailSettings
                    Layout.preferredHeight: transformerList.implicitHeight
                    Layout.preferredWidth: settingsButtonBox.fullWidth()
                }
                PropertyChanges {
                    target: flyout
                    enableDetect: true
                }
                PropertyChanges {
                    target: transformerList
                    visible: true
                }
            }
        ]
        transitions: [
            Transition {
                to: "full"
                SequentialAnimation {
                    PropertyAction {
                        target: transformerList
                        property: "visible"
                    }
                    NumberAnimation {
                        properties: "Layout.preferredWidth,Layout.preferredHeight"
                        duration: root.animationDuration
                        easing.type: root.easingType
                    }
                    PropertyAction {
                        target: flyout
                        property: "enableDetect"
                    }
                }
            },
            Transition {
                to: "compact"
                SequentialAnimation {
                    PropertyAction {
                        target: flyout
                        property: "enableDetect"
                    }
                    NumberAnimation {
                        properties: "Layout.preferredWidth,Layout.preferredHeight"
                        duration: root.animationDuration
                        easing.type: root.easingType
                    }
                    PropertyAction {
                        target: transformerList
                        property: "visible"
                    }
                }
            }
        ]
    }

    TransferButton {
        id: btnTransferToLeft
        Layout.alignment: Qt.AlignCenter

        height: root.buttonHeight
        briefWidth: root.buttonWidth
        detailWidth: settingsButtonBox.fullWidth()
        briefText: "◄"
        detailText: qsTr("◄ Transfer To Left")
        animationDuration: root.animationDuration
        easingType: root.easingType

        state: detailSettings.state
    }
}

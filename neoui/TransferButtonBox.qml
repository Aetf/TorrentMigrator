import QtQuick 2.3
import QtQuick.Controls 1.2
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
            model: TransformerModel { }
            delegate: listDelegate
            highlight: listHighLight

            Component {
                id: listDelegate
                Text {
                    text: model.name
                    MouseArea {
                        anchors.fill: parent
                        onClicked: transformerList.currentIndex = index
                    }
                }
            }
            Component {
                id: listHighLight
                Rectangle {
                    color: "lightblue"
                    radius: 5
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
                            detailSettings.compact = false;
                        }
                    }
                }

                alternativeButton: Component {
                    Button {
                        implicitWidth: root.buttonWidth
                        iconSource: "qrc:/images/Yes_icon.png"
                        onClicked: {
                            detailSettings.compact = true;
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
                    implicitWidth: root.buttonWidth
                    iconSource: "qrc:/images/Add_icon.png"
                    onClicked: {
                        var cur = transformerList.currentIndex
                        transformerList.model.insertRow(cur,
                                                        "PathRegexTransformer")
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

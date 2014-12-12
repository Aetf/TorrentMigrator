import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout {
    id: root

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
        briefText: ">"
        detailText: "Transfer To Right >"
        animationDuration: root.animationDuration
        easingType: root.easingType
    }

    Item {
        id: detailSettings
        Layout.alignment: Qt.AlignCenter
        Layout.preferredHeight: root.buttonHeight
        Layout.preferredWidth: root.buttonWidth

        clip: true

        Rectangle {
            id: transformationList
            anchors { top: parent.top; right: parent.right; bottom: parent.bottom; left: parent.left }
            implicitHeight: 200

            color: "orange"
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

                mainButton: Component {
                    Button {
                        implicitWidth: 25
//                        iconSource: "qrc:/images/more.png"
                        text: "..."
                        onClicked: {
                            settingsButtonBox.expand();
                            detailSettings.state = "full";
                        }
                    }
                }

                alternativeButton: Component {
                    Image {
//                        implicitWidth: 25
                        width: 25
                        source: "qrc:/images/more.png"
//                        text: "OK"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                settingsButtonBox.collapse();
                                detailSettings.state = "compact";
                            }
                        }
                    }
                }

                Repeater {
                    model: ["yellow", "cyan", "green", "red"]

                    Rectangle {
                        height: root.buttonHeight
                        width: root.buttonWidth
                        radius: width / 2
                        color: Qt.lighter(modelData)
                    }
                }
            }
        }

        state: "compact"
        states: [
            State {
                name: "compact"
                PropertyChanges {
                    target: detailSettings
                    Layout.preferredHeight: root.buttonHeight
                    Layout.preferredWidth: settingsButtonBox.compactWidth()
                }
                PropertyChanges {
                    target: btnTransferToRight
                    state: "brief"
                }
                PropertyChanges {
                    target: btnTransferToLeft
                    state: "brief"
                }
                PropertyChanges {
                    target: flyout
                    enableDetect: false
                }
                PropertyChanges {
                    target: transformationList
                    visible: false
                }
            },
            State {
                name: "full"
                PropertyChanges {
                    target: detailSettings
                    Layout.preferredHeight: transformationList.implicitHeight
                    Layout.preferredWidth: settingsButtonBox.fullWidth()
                }
                PropertyChanges { target: btnTransferToRight; state: "detail" }
                PropertyChanges { target: btnTransferToLeft; state: "detail" }
                PropertyChanges {
                    target: flyout
                    enableDetect: true
                }
                PropertyChanges {
                    target: transformationList
                    visible: true
                }
            }
        ]
        transitions: [
            Transition {
                to: "full"
                SequentialAnimation {
                    PropertyAction { target: transformationList; property: "visible" }
                    NumberAnimation {
                        properties: "Layout.preferredWidth,Layout.preferredHeight"
                        duration: root.animationDuration
                        easing.type: root.easingType
                    }
                    PropertyAction { target: flyout; property: "enableDetect" }
                }
            },
            Transition {
                to: "compact"
                SequentialAnimation {
                    PropertyAction { target: flyout; property: "enableDetect" }
                    NumberAnimation {
                        properties: "Layout.preferredWidth,Layout.preferredHeight"
                        duration: root.animationDuration
                        easing.type: root.easingType
                    }
                    PropertyAction { target: transformationList; property: "visible" }
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
        briefText: "<"
        detailText: "< Transfer To Left"
        animationDuration: root.animationDuration
        easingType: root.easingType
    }
}
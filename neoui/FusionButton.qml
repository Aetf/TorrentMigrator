import QtQuick 2.3
import QtQuick.Layouts 1.1

Item {
    id: root
    clip: true

    default property alias extraButtons: extraButtonBox.children
    property alias mainButton: mainButtonBox.sourceComponent
    property alias alternativeButton: alternativeButtonBox.sourceComponent

    property real buttonWidth: 25
    property real buttonHeight: height
    property real spacing: 5
    property real animationDuration: 200
    property int easingType: Easing.InOutQuart
    property bool compact: true

    function compactWidth() {
        return buttonWidth;
    }

    function fullWidth() {
        return extraButtonBox.width + spacing + buttonWidth;
    }

    Loader {
        id: alternativeButtonBox
        anchors.fill: mainButtonBox

        sourceComponent: Component {
            Rectangle {
                color: Qt.lighter("gray")
                MouseArea {
                    anchors.fill: parent
                    onClicked: expand()
                }
            }
        }
    }

    Loader {
        id: mainButtonBox
        anchors.right: parent.right
        width: parent.buttonWidth
        height: parent.buttonHeight

        sourceComponent: Component {
            Rectangle {
                color: Qt.lighter("blue")
                MouseArea {
                    anchors.fill: parent
                    onClicked: collapse()
                }
            }
        }
    }

    Row {
        id: extraButtonBox
        anchors.right: mainButtonBox.left
        anchors.rightMargin: parent.spacing
        spacing: parent.spacing
    }

    state: compact ? "compact" : "full"
    states: [
        State {
            name: "compact"
            PropertyChanges { target: root; implicitWidth: compactWidth() }
            PropertyChanges { target: mainButtonBox; opacity: 1; enabled: true}
            PropertyChanges { target: alternativeButtonBox; opacity: 0; enabled: false}
        },
        State {
            name: "full"
            PropertyChanges { target: root; implicitWidth: fullWidth() }
            PropertyChanges { target: mainButtonBox; opacity: 0; enabled: false}
            PropertyChanges { target: alternativeButtonBox; opacity: 1; enabled: true}
        }
    ]
    transitions: [
        Transition {
            PropertyAction { target: alternativeButtonBox; property: "enabled"}
            NumberAnimation {
                target: root
                property: "implicitWidth"
                duration: animationDuration
                easing.type: easingType
            }
            NumberAnimation {
                target: mainButtonBox
                property: "x"
                duration: animationDuration
                easing.type: easingType
            }
            NumberAnimation {
                targets: [mainButtonBox, alternativeButtonBox]
                properties: "opacity"
                duration: animationDuration
                easing.type: easingType
            }
            PropertyAction { target: mainButtonBox; property: "enabled"}
        }
    ]
}

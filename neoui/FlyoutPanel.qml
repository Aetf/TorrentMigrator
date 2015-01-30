import QtQuick 2.3

Item {
    id: root
    implicitHeight: placeholder.childrenRect.height
    implicitWidth: placeholder.childrenRect.width
    clip: true

    default property alias content: placeholder.children
    property bool enableDetect: false
    property bool show: true

    MouseArea {
        id: hoverDetector
        anchors.fill: parent
        hoverEnabled: true

        onContainsMouseChanged: {
            if (enableDetect) {
                root.show = containsMouse;
            }
        }

        Item {
            id: placeholder
            implicitWidth: childrenRect.width
            implicitHeight: childrenRect.height
            clip: true
        }
    }

    states: [
        State {
            name: "show"
            when: show
            PropertyChanges {
                target: placeholder
                y: 0
            }
        },
        State {
            name: "hide"
            when: !show
            PropertyChanges {
                target: placeholder
                y: placeholder.implicitHeight
            }
        }
    ]
    transitions: [
        Transition {
            to: "show"
            PropertyAnimation {
                target: placeholder; property: "y"
                easing.type: Easing.InOutQuint
                duration: 200
            }
        },
        Transition {
            to: "hide"
            PropertyAnimation {
                target: placeholder; property: "y"
                easing.type: Easing.OutQuart
                duration: 100
            }
        }
    ]
}

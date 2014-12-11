import QtQuick 2.3

Item {
    id: root
    implicitHeight: placeholder.childrenRect.height
    implicitWidth: placeholder.childrenRect.width
    clip: true

    default property alias content: placeholder.children
    property bool enableDetect: false

    function show() {
        root.state = "show"
    }

    function hide() {
        root.state = "hide"
    }

    onEnableDetectChanged: {
        if (!enableDetect) show();
    }

    MouseArea {
        id: hoverDetector
        anchors.fill: parent
        hoverEnabled: true

        onContainsMouseChanged: {
            if (enableDetect) {
                if (containsMouse)
                    show();
                else
                    hide();
            }
        }
    }

    Item {
        id: placeholder
        implicitWidth: childrenRect.width
        implicitHeight: childrenRect.height
    }

    state: "show"
    states: [
        State {
            name: "show"
            PropertyChanges {
                target: placeholder
                y: 0
            }
        },
        State {
            name: "hide"
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

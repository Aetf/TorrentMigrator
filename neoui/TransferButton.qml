import QtQuick 2.3
import QtQuick.Controls 1.2

Button {
    id: root
    implicitHeight: 25
    implicitWidth: 25

    property string briefText: ">"
    property string detailText: "Transfer To Right >"
    property real briefWidth: 25
    property real detailWidth: 145
    property real animationDuration: 200
    property int easingType: Easing.InOutQuart

    text: briefText

    state: "brief"
    states: [
        State {
            name: "brief"
            PropertyChanges {
                target: root
                implicitWidth: briefWidth
                text: briefText
            }
        },
        State {
            name: "detail"
            PropertyChanges {
                target: root
                implicitWidth: detailWidth
                text: detailText
            }
        }
    ]
    transitions: [
        Transition {
            PropertyAnimation {
                property: "implicitWidth"
                easing.type: easingType
                duration: animationDuration
            }
        },
        Transition {
            to: "brief"
            SequentialAnimation {
                PropertyAnimation {
                    property: "implicitWidth"
                    easing.type: easingType
                    duration: animationDuration
                }
                PropertyAction { property: "text" }
            }
        }
    ]
}

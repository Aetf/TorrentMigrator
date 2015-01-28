import QtQuick 2.3
import QtQuick.Controls 1.2

Button {
    id: root
    implicitHeight: 25
    implicitWidth: 25

    property string briefText: ">"
    property string detailText: qsTr("Transfer To Right >")
    property real briefWidth: 25
    property real detailWidth: 145
    property real animationDuration: 200
    property int easingType: Easing.InOutQuart

    text: briefText

    state: "compact"
    states: [
        State {
            name: "compact"
            PropertyChanges {
                target: root
                implicitWidth: briefWidth
                text: briefText
            }
        },
        State {
            name: "full"
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
            to: "compact"
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

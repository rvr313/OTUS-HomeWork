import QtQuick 2.12

Rectangle {
    id: root

    implicitHeight: 40
    implicitWidth: 150
    color: area.pressed ? "gray" : "lightgray"
    border.color: "darkgray"
    border.width: 2
    radius: 10
    property alias text: textButton.text

    signal clicked(var event)

    Text {
        id: textButton

        anchors.centerIn: parent
        text: "Connect"
    }

    TapHandler {
        id: area

        onTapped: {
            dbc.connectDb()
        }
    }
}

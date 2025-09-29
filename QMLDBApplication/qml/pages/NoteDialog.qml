import QtQuick 2.0
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0

Dialog {
    objectName: "personalDataPage"
    allowedOrientations: Orientation.All

    property alias title: pageHeader.title
    property alias date: dateInput.text
    property alias note: noteArea.text

    ColumnLayout {
        id: layout
        objectName: "layout"
        width: parent.width
        DialogHeader {
            acceptText: qsTr("Save note")
            cancelText: qsTr("Don't save")
        }
        PageHeader {
            id: pageHeader
            objectName: "pageHeader"
            title: qsTr("New note")
        }
        TextField {
            id: dateInput
            width: parent.width
            validator: RegExpValidator {
                regExp: /[0-9/,:.]+/
            }
            placeholderText: qsTr("Date")
            label: qsTr("Date")
            EnterKey.onClicked: noteArea.focus = true
        }
        TextArea {
            id: noteArea
            anchors.top: dateInput.bottom
            anchors.bottom: parent.bottom
            width: parent.width
        }
    }
}

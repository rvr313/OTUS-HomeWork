import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels
//import MyTableModel 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Gold Price Table")

    // HorizontalHeaderView {
    //     id: horizontalHeader
    //     anchors.left: tableViewId.left
    //     anchors.top: parent.top
    //     syncView: tableViewId
    // }

    // VerticalHeaderView {
    //     id: verticalHeader
    //     anchors.top: tableViewId.top
    //     anchors.left: parent.left
    //     syncView: tableViewId
    // }
    // HorizontalHeaderView {
    //     id: horizontalHeader
    //     anchors.left: tableViewId.left
    //     anchors.top: parent.top
    //     syncView: tableViewId
    //     clip: true
    // }

    // VerticalHeaderView {
    //     id: verticalHeader
    //     anchors.top: tableViewId.top
    //     anchors.left: parent.left
    //     syncView: tableViewId
    //     clip: true
    // }

    // MyTableModel {
    //     id: tableModelId

    // }

    // TableView {
    //     id: tableViewId

    //     model: tableModelId

    // }

    // Connections {
    //     target: dbc
    //     function onDbConnected() {
    //         console.log("DB connected")
    //         tableModelId.allDataChanged()
    //     }
    // }

    ColumnLayout {
        id: columnLayoutId
        anchors.fill: parent
        spacing: 5


        TableView {
            id: tableViewId
            Layout.fillHeight: true

            model: table_model
        }

        ConnectButton {
            id: connectButtonId
            Layout.fillWidth: true
        }
    }
}

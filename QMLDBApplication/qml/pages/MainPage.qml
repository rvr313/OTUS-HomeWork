import QtQuick 2.0
import Sailfish.Silica 1.0
import "../assets/Database.js" as DB
import Aurora.Controls 1.0

Page {
    id: root
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    AppBar {
        id: bar
        headerText: qsTr("Notes")
        AppBarSpacer {}

        AppBarButton {
            context: "Add note"
            icon.source: "image://theme/icon-m-add"
            onClicked: {
                var dialog = pageStack.push(Qt.resolvedUrl("NoteDialog.qml"), {"title": "New Note"})
                dialog.accepted.connect(function() {
                    var rowid = parseInt(DB.dbInsert(dialog.date, dialog.note), 10)
                    if (rowid) {
                        noteModel.insert(0, {"rowid": rowid, "date": dialog.date, "note": dialog.note})
                    } else {
                        statustext.text = qsTr("Failed to insert row")
                    }
                })
            }
        }
    }

    SilicaListView {
        id: notesView
        width: parent.width
        anchors.top: bar.bottom
        anchors.bottom: parent.bottom
        model: ListModel { id: noteModel }
        section {
            property: "date"
            delegate: SectionHeader {
                text: section
                font.bold: true
                font.pixelSize: Theme.fontSizeHuge
            }
        }

        delegate: ListItem {
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Delete note")
                    onClicked: {
                        DB.dbDelete(rowid)
                        noteModel.remove(index)
                    }
                }
                MenuItem {
                    text: qsTr("Update note")
                    onClicked: {
                        var dialog = pageStack.push(Qt.resolvedUrl("NoteDialog.qml"),
                                                    {"title": "Update Note", "date":date, "note": note})
                        dialog.accepted.connect(function() {
                            DB.dbUpdate(rowid, dialog.date, dialog.note)
                            noteModel.set(index, {"date": dialog.date, "note": dialog.note})
                        })
                    }
                }
            }

            Label {
                width: notesView.width
                wrapMode: Text.Wrap
                text: note
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
            }
        }
    }

    Component.onCompleted: {
        DB.dbInit()
        DB.dbReadAll()
    }
}

import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    PageHeader {
        width: parent.width
        anchors.top: parent.top
        title: qsTr("Регистрация")
    }

    Column {
        width: parent.width
        anchors.centerIn: parent

        TextField {
            id: login
            placeholderText: "Введите логин"
            label: "Логин"
            width: parent.width
            leftItem: Icon {
                source: "image://theme/icon-m-person"
            }
            validator: RegExpValidator { regExp: /^[a-z][a-z0-9_-]{6,15}$/ }
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
        }
        TextField {
            id: phone
            placeholderText: "Введите номер телефона с +7"
            label: "Номер телефона"
            width: parent.width
            leftItem: Icon {
                source: "image://theme/icon-m-phone"
            }
            validator: RegExpValidator { regExp: /^\+[0-9]{6,}$/ }
            inputMethodHints: Qt.ImhDialableCharactersOnly | Qt.ImhNoPredictiveText
        }
        Button {
            id: saveButton
            border.color: Theme.secondaryColor
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Register"
            onClicked: {
                if (!login.errorHighlight && !phone.errorHighlight) {
                    pageStack.push(Qt.resolvedUrl("PersonalDataPage.qml"))
                } else {
                    console.log("Некорректный формат логина или номера телефона")
                }
            }
        }
    }
}

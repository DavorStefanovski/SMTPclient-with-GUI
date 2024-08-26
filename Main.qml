import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Mail Client"

    property bool isLoggedIn: false

    Rectangle {
        id: loginScreen
        anchors.fill: parent
        color: "lightgray"
        visible: !isLoggedIn

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20
            width: parent.width * 0.9
            TextField {
                id: emailField
                placeholderText: "Enter your email"
                Layout.fillWidth: true
            }

            TextField {
                id: passwordField
                placeholderText: "Enter your password"
                //echoMode: TextInput.Password
                Layout.fillWidth: true
            }

            Button {
                text: "Login"
                width: 80
                height: 40
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    // Implement login logic here
                    isLoggedIn = Manager.login(emailField.text,passwordField.text);  // Toggle to show mail form after login
                }
            }
        }
    }


    Rectangle {
        id: mailForm
        anchors.fill: parent
        color: "white"
        visible: isLoggedIn

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20
            width: parent.width * 0.9

            TextField {
                id: toField
                placeholderText: "To"
                Layout.fillWidth: true
            }

            TextField {
                id: ccField
                placeholderText: "CC"
                Layout.fillWidth: true
            }

            TextField {
                id: subjectField
                placeholderText: "Subject"
                Layout.fillWidth: true
            }

            TextArea {
                id: bodyField
                placeholderText: "Body"
                Layout.fillWidth: true
                Layout.preferredHeight: 200
            }

            FileDialog {
                id: fileDialog
                fileMode: FileDialog.OpenFiles
                title: "Select attachments"
                nameFilters: ["All files (*)"]
                onAccepted: {
                    for (var i = 0; i < fileDialog.selectedFiles.length; i++) {
                                            var path = fileDialog.selectedFiles[i].toString()
                                            attachments.append({"filePath": path.split('/').pop()})
                                        }
                }
            }
            ListModel {
                id: attachments
            }
            ListView {
                id: listview
                Layout.fillWidth: true
                height: 50
                model: attachments
                delegate: Text {
                    text: model.filePath
                }

            }

            Button {
                text: "Attach Files"
                width: 80
                height: 40
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    fileDialog.open()
                }
            }

            Button {
                text: "Send"
                width: 80
                height: 40
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    console.log(fileDialog.selectedFiles)
                    // Implement email sending logic here
                    if(Manager.send(toField.text, ccField.text, subjectField.text, bodyField.text, fileDialog.selectedFiles)){
                        isLoggedIn = false
                    }
                }
            }
        }
    }
}

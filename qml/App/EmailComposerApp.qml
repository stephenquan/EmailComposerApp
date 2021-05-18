import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import ArcGIS.AppFramework.Labs.Email 1.0

Page {
    header: Frame {

        background: Rectangle {
            color: styles.titleBackgroundColor
        }

        RowLayout {
            width: parent.width

            Text {
                Layout.fillWidth: true

                text: app.title
                font.pointSize: styles.titleTextPointSize
            }
        }
    }

    Flickable {
        id: flickable

        anchors.fill: parent
        anchors.margins: 10

        contentWidth: columnLayout.width
        contentHeight: columnLayout.height
        clip: true

        ColumnLayout {
            id: columnLayout

            width: flickable.width

            Button {
                text: qsTr("Send")

                font.pointSize: styles.textPointSize

                onClicked: {
                    Email.send();
                }
            }

            Text {
                id: debugText

                Layout.fillWidth: text
            }
        }
    }

    footer: Frame {
        RowLayout {
            width: parent.width

            Text {
                text: Email.qtVersion

                font.pointSize: sttles.textPointSize
            }
        }
    }

    Connections {
        target: Email

        function onDebug(message) {
            debugText.text += message + "\n";
        }
    }

}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "App"

Window {
    id: app

    width: 640
    height: 480
    visible: true
    title: qsTr("Email Composer App")

    QtObject {
        id: styles

        property int titleTextPointSize: 14
        property color titleBackgroundColor: "#e0e0e0"
        property int textPointSize: 12
    }

    EmailComposerApp {
        anchors.fill: parent
    }
}

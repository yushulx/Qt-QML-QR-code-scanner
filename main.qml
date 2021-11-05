import QtQuick 2.0
import QtMultimedia 5.4

import com.dynamsoft.barcode 1.0

Item {
    width: 1280
    height: 720

    Camera {
        id: camera
        captureMode: Camera.CaptureVideo
        focus {
            focusMode: Camera.FocusContinuous
            focusPointMode: Camera.FocusPointCenter
        }
        objectName: "qrcamera"
    }

    VideoOutput {
        id: viewfinder
        width: parent.width
        height: parent.height - 50
        source: camera
        anchors.fill: parent
        autoOrientation: true
        filters: [ qrcodefilter ]
    }

    QRCodeFilter {
        id: qrcodefilter
        onFinished: {
            info.text = result.text;
        }
    }

    Column {
        x: 10
        y: 10
        Text {
            font.pointSize: 24
            color: "green"
            text: "Qt Demo: QR Code Scanner"
        }
        Text {
            id: info
            font.pointSize: 12
            color: "green"
            text: info.text
        }
    }
}

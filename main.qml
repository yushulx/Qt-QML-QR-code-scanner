import QtQuick
import QtMultimedia
import com.dynamsoft.barcode

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    FrameProcessor {
        id: frameProcessor
        videoSink: viewfinder.videoSink
        onBarcodeDetected: {
            info.text = result
        }
    }

    CaptureSession {
        id: captureSession
        camera: Camera {
            id: camera
        }
        videoOutput: viewfinder
    }

    VideoOutput {
        id: viewfinder
        visible: true
        anchors.fill: parent
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 10

        Text {
            id: info
            font.pointSize: 12
            color: "green"
            text: frameProcessor.displayString
            horizontalAlignment: Text.AlignHCenter
        }

    }

    Component.onCompleted: camera.start()
}

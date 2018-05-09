import QtQuick 2.0

Item  {
    id: container

    property variant scrollArea

    // orientation can be either Qt.Vertical or Qt.Horizontal
    property int orientation: Qt.Vertical

    opacity: 1.0

    // get button position
    function position()
    {
        var pos = 0;
        if (container.orientation === Qt.Vertical)
            pos = scrollArea.visibleArea.yPosition * (container.height-2) + 1;
        else
            pos = scrollArea.visibleArea.xPosition * (container.width-2) + 1;
        return pos;
    }

    // return button length
    function size()
    {
        var size;

        if (container.orientation === Qt.Vertical)
            size = scrollArea.visibleArea.heightRatio * (container.height-2);
        else
            size = scrollArea.visibleArea.widthRatio * (container.width-2);
        return size;
    }

    //background
    Rectangle  {
        id: bar
        anchors.fill: parent
        radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
        color: "black"
        opacity: 0.1
        Behavior on opacity {
            PropertyAnimation {
                duration: 100
                easing.type: Easing.InQuad
            }
        }
        //Scroll Button
        Rectangle {
            id: button
            x: orientation == Qt.Vertical ? 1 : position()
            y: orientation == Qt.Vertical ? position() : 1
            width: orientation == Qt.Vertical ? (parent.width-2) : size()
            height: orientation == Qt.Vertical ? size() : (parent.height-2)
            radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
            color: "black"
            opacity: 0.8

            MouseArea {
                id: ma_button
                anchors.fill: button
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton
                drag.target: button
                drag.axis: Qt.Vertical ? Drag.YAxis : Drag.XAxis
                drag.minimumY: 0
                drag.maximumY: Qt.Vertical ? container.height - button.height : 0
                drag.minimumX: 0
                drag.maximumX: Qt.Vertical ? 0 : container.width - button.width

                // click button and drag
                onMouseYChanged: {
                    if(ma_button.pressed) {
                        scrollArea.contentY = button.y / container.height * scrollArea.contentHeight;
                    }
                }
                onEntered: {
                    bar.opacity = 0.3
                }
                onExited: {
                    bar.opacity = 0.1
                }
            }
        }
    }
}

import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    property int fontPixelSize
    property int itemWidth
    property int itemHeight
    id: container
    anchors.fill: parent
    color: "#100404"
    //radius: 2
    //border.color: "#100404"
    Item {
        id:menu
        height:itemHeight
        width:itemWidth
        x:0
        y:0

        Text {
            id:close
            //objectName:"close"
            color: "#f6f5f5"
            //anchors.fill: parent
            text:"<"
            style: Text.Outline
            font.pixelSize: fontPixelSize *2
            font.bold: true

        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                view.CloseLastTime();
                lm.clear();
                container.visible = false;
            }
        }
    }

    Rectangle {
        id: content
        y:menu.y+menu.height

        width:parent.width
        height:parent.height-y
        color:"#ffffff"
        //data:

        ListView {
            id:showView
            anchors.fill: parent
            delegate: ItemDelegate {
                height: fontPixelSize+4
                width: parent.width
                text:sendMsg
                font.pixelSize: fontPixelSize
            }
            model: ListModel {
                id: lm
            }
        }
    }
    function updateShowModel(_index,_msg) {
        //content.Set
        //lm.revert()
        //console.log(_index,_msg)
        var len = lm.count;
        if (len <= _index) {
            lm.append({'sendMsg': _msg});
            return;
        }
        var da = lm.get(_index)
        if (da === null){
            lm.append({'sendMsg': _msg});
        }else{
            if (da.sendMsg !== _msg){
                da.sendMsg = _msg;
            }
        }

    }

}


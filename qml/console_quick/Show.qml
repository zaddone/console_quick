import QtQuick 2.0
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
                container.visible = false;
                view.ClearTmpShow();
                lm.clear();


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
            delegate: Item {
                height: close.height/2
                width: parent.width
                Text {
                    //id:tag
                    text: msg
                    //objectName:tag
                    //data:scale
                    //tag:index
                    anchors.fill: parent
                    font.pixelSize :fontPixelSize
                    anchors.verticalCenter: parent.verticalCenter
                }


            }
            model: ListModel {
                id: lm
            }
        }
    }
    function updateShowModel(_index,_msg) {
        //content.Set
        //lm.revert()

        var len = lm.count;
        if (len <= _index) {
            lm.append({'msg': _msg});
            return;
        }
        var da = lm.get(_index)
        if (da === null){
            lm.append({'msg': _msg});
        }else{
            if (da.msg != _msg){
                da.msg = _msg;
            }
        }

    }

}


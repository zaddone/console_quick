import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.0

ApplicationWindow {
    id: myRect
    objectName:"myRect"
    visible: true
    x:0
    y:0
    width: Screen.desktopAvailableWidth>800?800:Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight>600?600:Screen.desktopAvailableHeight
    title: qsTr("console")
    /**
    Keys.onPressed:{
        edit.focus = true;
        edit.text += event.text;
        edit.cursorPosition = edit.length
    }
    **/
    TextEdit {
        id: edit
        x: 8
        y: 8

        //activeFocusOnPress:true
        width: (parent.width-x*2)
        height:getEditHeight(myRect.height/24,32)
        text:focus?"":"Input"
        font.pixelSize :height-y
        wrapMode:TextEdit.WordWrap
        //onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
        Keys.onReturnPressed: {
            //appendModel(text);
            view.HandleInput(text);
            text= "";
        }
        function getEditHeight(x,y){
            return x>y?x:y;
        }
    }
    ScrollView {
        x: parent.x
        y: parent.y+edit.y*2+edit.height
        width: parent.width
        height:parent.height -y
        contentWidth: width
        //anchors.fill: parent
        ListView {
            id:listView1
            anchors.fill: parent
            //width: parent.width
            model: ListModel {

            }
            delegate: ItemDelegate {
                text: msg
                width: parent.width
                height:edit.height
            font.pixelSize:edit.font.pixelSize
                onClicked:{
                    edit.text = text
                    edit.cursorPosition = edit.length
                    edit.focus = true
                }
            }
            Keys.onPressed:{
                edit.focus = true;
                edit.text += event.text;
                edit.cursorPosition = edit.length
            }
        }
    }
    function appendModel(msg) {
        listView1.contentY = 0;
        listView1.model.insert(0, {'msg': msg});
        if (listView1.model.count>1000){
            listView1.model.remove(1000);
        }
    }
    Show{
        id:showWindows
        objectName:"showWindows"
        visible:false
        fontPixelSize:edit.font.pixelSize
        itemHeight:edit.height*2
        itemWidth:edit.width
    }
}

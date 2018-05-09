import QtQuick 2.0
import QtQuick.Window 2.0
//import Client 1.0

Rectangle {

    id: myRect
    width: Screen.desktopAvailableWidth>800?800:Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight>600?600:Screen.desktopAvailableHeight
    Keys.onPressed:{
        edit.focus = true;
        edit.text += event.text;
        edit.cursorPosition = edit.length
    }

    Rectangle {
        id: rectangle1
        x: 8
        y: 8
        width: getWidth()
        height: parent.height-y*2
        color: "#ffffff"
        radius: 2
        border.color: "#100404"
        function getWidth(){
            var w = (parent.width-x*2);
            return w<100?100:w;
        }
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
                view.HandleInput(text);
            }
            function getEditHeight(x,y){
                return x>y?x:y;
            }
        }
        ListView {
            id: listView1
            x: edit.x
            y: parent.y+edit.y+edit.height
            width: edit.width
            height:parent.height -y - edit.y*2
            clip:true
            delegate: Item {
                x: 0
                height: edit.height
                width: edit.width
                Text {
                    id:te
                    text: name                    
                    //tag:index
                    anchors.fill: parent
                    font.pixelSize :edit.font.pixelSize
                    anchors.verticalCenter: parent.verticalCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        //Text.data
                        edit.text = name
                        //edit.data = data
                        edit.cursorPosition = edit.length
                        edit.focus = true
                        //parent.radius= 2
                        //parent.border.color="#100404"
                    }
                }
            }
            model: ListModel {
                //id: fruitModel
                /**
                ListElement {
                    name: "Bill Smith"
                    number: "555 3264"
                }
                **/
            }
        }
        ScrollBar  {
            id:scroll
            visible : listView1.contentHeight>listView1.height
            scrollArea: listView1
            height: listView1.height
            y:listView1.y
            width: 10
            anchors.right: listView1.right
        }
    }
    function appendModel(msg) {
        listView1.contentY = 0;
        listView1.model.insert(0, {'name': msg})
        if (listView1.model.count>1000){
            listView1.model.remove(1000)
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



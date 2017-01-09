import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4

Item {

    width: 800
    height: 600

    signal sgn_send_message(string content);

    Rectangle{
        width: parent.width
        anchors{
            top: parent.top
            bottom: id_text_input.top;
            bottomMargin: 1
        }
        radius: 2
        border.color: "#333"
        border.width: 1

        TextArea{
            id: id_text_output
            anchors.fill: parent
            font.pixelSize: 16
            readOnly: true
        }
    }

    TextField {

        id : id_text_input
        width : parent.width
        anchors.bottom: parent.bottom
        focus: true

        style: TextFieldStyle {
            textColor: "black"
            font.pixelSize: 16
            background: Rectangle {
                radius: 2
                border.color: "#333"
                border.width: 1
            }
        }

        Keys.onPressed: {
            if(event.key == 16777220) //enter key
            {
                if(id_text_input.text == "")
                    return;
                sgn_send_message(id_text_input.text)
                id_text_output.append("mine: " + id_text_input.text)
                id_text_input.text = "";
            }
        }
    }
}

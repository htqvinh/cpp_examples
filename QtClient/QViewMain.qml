import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4

Item {

    width: 800
    height: 600

    property var is_sign_in : false
    signal sgn_send_message(string content)
    signal sgn_recv_message(string content)
    signal sgn_signin(string usrname)
    signal sgn_signout(string usrname)

    onSgn_recv_message:{
        id_text_output.append(content)
    }

    Rectangle{
        width: 200
        anchors{
            top: parent.top
            right : parent.right
        }
        TextField{
            id: id_text_usrname
            width: parent.width
            font.pixelSize: 16
        }
        Button{
            id: id_btn_sign
            width: parent.width
            text: (!is_sign_in) ? "Sign-In" : "Sign-Out"
            anchors{
                top: id_text_usrname.bottom
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(id_text_usrname.text == "")
                        return;
                    if(is_sign_in){
                        id_text_usrname.text = "" ;
                        id_text_usrname.enabled = true;
                        sgn_signout(id_text_usrname.text);
                    }else{
                        id_text_usrname.enabled = false;
                        sgn_signin(id_text_usrname.text);
                    }
                    is_sign_in = !is_sign_in;
                }
            }
        }
    }

    Rectangle{
        width: 600
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
        width : 600
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
                if(!is_sign_in)
                    return;
                if(id_text_input.text == "")
                    return;

                sgn_send_message(id_text_usrname.text + ": " + id_text_input.text)
                id_text_output.append("mine" + ": " + id_text_input.text)
                id_text_input.text = "";
            }
        }
    }
}

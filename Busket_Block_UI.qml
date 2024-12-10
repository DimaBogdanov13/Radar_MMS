import QtQuick 2.15
import QtQuick.Controls 2.15

import Actions 1.0

Item {
    width: parent.width
    height: parent.height

    property var busket

    signal cliekd_Button

    function get_Last_Action(action){

        switch(action){

        case Actions.Extracted_Blue_Ball:
            return "извлекли синий шар"

        case Actions.Extracted_Red_Ball:
            return "извлекли красный шар"

        case Actions.Error_Action:
            return "не получилось достать шар"

        default:
            return ""

        }
    }

    Rectangle{
        width: parent.width
        height: parent.height
        radius: 16
        color: "#9EA9FB"

        Column{
            width: parent.width - spacing_value
            height: parent.height - spacing_value
            anchors.centerIn: parent
            spacing: spacing_value

            Label{
                text: "Корзина " + busket.num_Busket
            }

            Label{
                text: "Шаров в корзине: " + (busket.count_Blue_Ball + busket.count_Red_Ball)
            }

            Label{
                text: "Синих шаров в корзине: " + busket.count_Blue_Ball
            }

            Label{
                text: "Красных шаров в корзине: " + busket.count_Red_Ball
            }

            Label{
                text: "Вероятность достать синий шар: " + busket.blue_Probability.toFixed(2) + " %"
            }

            Label{
                text: "Вероятность достать красный шар: " + busket.red_Probability.toFixed(2) + " %"
            }

            Label{
                text: "Последнее действие: " + get_Last_Action(busket.last_Action)
            }

            Button{
                text: "Переложить шар в корзину " + busket.num_Put_Busket
                anchors.horizontalCenter: parent.horizontalCenter

                onClicked: {

                    cliekd_Button()
                }
            }

        }
    }

}

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import Main_Page_Logic 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Radar MMS")

    property int spacing_value: 10

    Main_Page_Logic{
        id: main_Page_Logic

        onLess_Than_Two_Balls_Signal: {

            warning_Label.text = "В корзине меньше двух шаров!"
        }
    }

    Column{
        width: parent.width - spacing_value * 2
        height: parent.height - spacing_value * 2
        anchors.centerIn: parent
        spacing: spacing_value

        Row{
            width: parent.width
            height: parent.height * 0.6 - parent.spacing / 2
            spacing: spacing_value

            Busket_Block_UI{
                width: parent.width * 0.5 - parent.spacing / 2
                busket: main_Page_Logic.busket_Values_1

                onCliekd_Button: {

                    main_Page_Logic.set_Ball_Busket(true)

                }
            }

            Busket_Block_UI{
                width: parent.width * 0.5 - parent.spacing / 2
                busket: main_Page_Logic.busket_Values_2

                onCliekd_Button: {

                    main_Page_Logic.set_Ball_Busket(false)
                }
            }
        }

        Item{
            width: parent.width
            height: parent.height * 0.4 - parent.spacing / 2

            Column{
                width: parent.width - spacing_value
                height: parent.height - spacing_value
                anchors.centerIn: parent
                spacing: spacing_value

                Label{
                    text: "Вероятность достать 2 сниних шара " + main_Page_Logic.probability_Two_Blue_Balls + " %"
                }

                Label{
                    text: "Вероятность достать 2 красных шара " + main_Page_Logic.probability_Two_Red_Balls + " %"
                }

                Label{
                    text: "Вероятность достать 1 красный и 1 сниний шары " + main_Page_Logic.probability_One_Blue_And_One_Red_Balls + " %"
                }

                Label{
                    id: warning_Label
                }

                Button{
                    text: "Извлечь два шара из случайной корзины"
                    anchors.horizontalCenter: parent.horizontalCenter

                    onClicked: {

                        main_Page_Logic.get_Two_Balls()
                    }
                }

            }
        }
    }


}

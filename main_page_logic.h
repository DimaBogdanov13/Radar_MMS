#ifndef MAIN_PAGE_LOGIC_H
#define MAIN_PAGE_LOGIC_H

#include <QObject>
#include <QDebug>
#include <QRandomGenerator>

#include "busket_values.h"
#include "abstract.h"

class Main_Page_Logic : public QObject, public Abstract
{
    Q_OBJECT

    Q_PROPERTY(Busket_Values* busket_Values_1 MEMBER busket_Values_1 NOTIFY busket_Values_Signal)

    Q_PROPERTY(Busket_Values* busket_Values_2 MEMBER busket_Values_2 NOTIFY busket_Values_Signal)


    Q_PROPERTY(float probability_Two_Blue_Balls MEMBER probability_Two_Blue_Balls NOTIFY float_Changed)

    Q_PROPERTY(float probability_Two_Red_Balls MEMBER probability_Two_Red_Balls NOTIFY float_Changed)

    Q_PROPERTY(float probability_One_Blue_And_One_Red_Balls MEMBER probability_One_Blue_And_One_Red_Balls NOTIFY float_Changed)

public:

    inline explicit Main_Page_Logic(QObject *parent = nullptr) : QObject(parent) {

        calculate_Probability();

    }

public slots:

    void set_Ball_Busket(bool set_Second_Busket){

        int action;

        if(set_Second_Busket){

            action = busket_Values_1->get_Actions_Ball();
        }
        else{

            action = busket_Values_2->get_Actions_Ball();

        }


        if(action != Actions::Error_Action){

            if(action == Actions::Extracted_Blue_Ball){

                qDebug() << "Получили синий шар";

                if(set_Second_Busket){

                    busket_Values_2->set_Blue_Ball();

                }
                else{

                    busket_Values_1->set_Blue_Ball();

                }
            }
            else{

                qDebug() << "Получили красный шар";

                if(set_Second_Busket){

                    busket_Values_2->set_Red_Ball();

                }
                else{

                    busket_Values_1->set_Red_Ball();

                }

            }

        }
        else{

            qDebug() << "ошибка ";
        }

        calculate_Probability();


    }

    void get_Two_Balls(){

        if(get_All_Count_Ball_In_Buskets() > 2){

            for(int i = 0; i < 2; i++){

                if(busket_Values_1->get_All_Count_Ball() > 0 && busket_Values_2->get_All_Count_Ball() > 0){

                    int num = QRandomGenerator::global()->bounded(0, 2);

                    if(num == 0){

                        busket_Values_1->get_Actions_Ball();

                    }
                    else{

                        busket_Values_2->get_Actions_Ball();

                    }

                }
                else{

                    // Эта ситуация возможна если какая-то корзина пустая

                    if(busket_Values_1->get_All_Count_Ball() > 1){

                        busket_Values_1->get_Actions_Ball();

                    }
                    else{

                        busket_Values_2->get_Actions_Ball();

                    }

                }

            }

            calculate_Probability();

        }
        else{

            emit less_Than_Two_Balls_Signal();

        }

    }


private:

    Busket_Values *busket_Values_1 = new Busket_Values(1, 2, 5, 1); // Последние два аргумента количество синих и красных шаров

    Busket_Values *busket_Values_2 = new Busket_Values(2, 1, 3, 4);

    float probability_Two_Blue_Balls, probability_Two_Red_Balls, probability_One_Blue_And_One_Red_Balls;

    int get_All_Count_Ball_In_Buskets(){return busket_Values_1->get_All_Count_Ball() + busket_Values_2->get_All_Count_Ball();}

    int get_Blue_Count_Ball_In_Buskets(){return busket_Values_1->get_Count_Blue_Ball() + busket_Values_2->get_Count_Blue_Ball();}

    int get_Red_Count_Ball_In_Buskets(){return busket_Values_1->get_Count_Red_Ball() + busket_Values_2->get_Count_Red_Ball();}


    void calculate_Probability(){

        if(get_All_Count_Ball_In_Buskets() > 1){

            if(get_Blue_Count_Ball_In_Buskets() == get_All_Count_Ball_In_Buskets()){

                probability_Two_Blue_Balls = 100;

                probability_Two_Red_Balls = 0;

                probability_One_Blue_And_One_Red_Balls = 0;
            }
            else{

                if(get_Red_Count_Ball_In_Buskets() == get_All_Count_Ball_In_Buskets()){

                    probability_Two_Blue_Balls = 0;

                    probability_Two_Red_Balls = 100;

                    probability_One_Blue_And_One_Red_Balls = 0;
                }
                else{

                    probability_Two_Blue_Balls = ((float) get_Blue_Count_Ball_In_Buskets() / (float) get_All_Count_Ball_In_Buskets()) *  (float)((get_Blue_Count_Ball_In_Buskets() - 1) / (float) (get_All_Count_Ball_In_Buskets() - 1) );

                    probability_Two_Red_Balls = ((float) get_Red_Count_Ball_In_Buskets() / (float) get_All_Count_Ball_In_Buskets()) * (float)((get_Red_Count_Ball_In_Buskets() - 1) / (float) (get_All_Count_Ball_In_Buskets() - 1) );

                    probability_One_Blue_And_One_Red_Balls = 1 - probability_Two_Blue_Balls - probability_Two_Red_Balls;

                }


            }


        }
        else{

            // У нас остался один шар следовательно вероятность достать два шара равна 0

            emit less_Than_Two_Balls_Signal();

            probability_Two_Blue_Balls = 0;

            probability_Two_Red_Balls = 0;

            probability_One_Blue_And_One_Red_Balls = 0;

        }


        emit float_Changed(probability_Two_Blue_Balls);

        emit float_Changed(probability_Two_Red_Balls);

        emit float_Changed(probability_One_Blue_And_One_Red_Balls);

    }

    void calculate_probability_One_Blue_And_One_Red_Balls(){

        probability_One_Blue_And_One_Red_Balls = 1 - probability_Two_Blue_Balls - probability_Two_Red_Balls;

    }


signals:

    void busket_Values_Signal(const Busket_Values *value);

    void float_Changed(const float value);

    void less_Than_Two_Balls_Signal();


};

#endif // MAIN_PAGE_LOGIC_H

#ifndef BUSKET_VALUES_H
#define BUSKET_VALUES_H

#include <QObject>
#include <QDebug>
#include <QRandomGenerator>

#include "actions.h"
#include "abstract.h"

class Busket_Values : public QObject, public Abstract
{
    Q_OBJECT

    Q_PROPERTY(int num_Busket MEMBER num_Busket NOTIFY int_Changed)

    Q_PROPERTY(int num_Put_Busket MEMBER num_Put_Busket NOTIFY int_Changed)

    Q_PROPERTY(int count_Blue_Ball MEMBER count_Blue_Ball NOTIFY int_Changed)

    Q_PROPERTY(int count_Red_Ball MEMBER count_Red_Ball NOTIFY int_Changed)

    Q_PROPERTY(int last_Action MEMBER last_Action NOTIFY int_Changed)


    Q_PROPERTY(float blue_Probability MEMBER blue_Probability NOTIFY float_Changed)

    Q_PROPERTY(float red_Probability MEMBER red_Probability NOTIFY float_Changed)


public:

    Busket_Values(int num_Busket, int num_Put_Busket, int count_Blue_Ball, int count_Red_Ball){

        this->num_Busket = num_Busket;

        this->num_Put_Busket = num_Put_Busket;

        this->count_Blue_Ball = count_Blue_Ball;

        this->count_Red_Ball = count_Red_Ball;


       calculate_Probability();
    }


    int get_Actions_Ball(){

        int answer = Actions::Error_Action;

        if(get_All_Count_Ball() > 0){

            if(get_All_Count_Ball() != 1){

                int num = QRandomGenerator::global()->bounded(1, get_All_Count_Ball());

                if(num < count_Blue_Ball){

                    // Получили синий шар
                    answer = pop_Blue_Ball();
                }
                else{

                    // Получили красный шар
                    answer = pop_Red_Ball();
                }

            }
            else{

                if(count_Blue_Ball != 0){

                    // Остался только синий шар
                    answer = pop_Blue_Ball();

                }
                else{

                    // Остался только красный шар
                    answer = pop_Red_Ball();


                }
            }

            calculate_Probability();

        }

        this->last_Action = answer;

        emit int_Changed(last_Action);


        return answer;

    }



    int pop_Blue_Ball(){

        count_Blue_Ball--;

        emit int_Changed(count_Blue_Ball);

        return Actions::Extracted_Blue_Ball;

    }

    int pop_Red_Ball(){

        count_Red_Ball--;

        emit int_Changed(count_Red_Ball);

        return Actions::Extracted_Red_Ball;

    }


    void set_Blue_Ball(){

        count_Blue_Ball++;

        emit int_Changed(count_Blue_Ball);

        calculate_Probability();
    }

    void set_Red_Ball(){

        count_Red_Ball++;

        emit int_Changed(count_Red_Ball);

        calculate_Probability();
    }


    int get_Count_Blue_Ball(){return count_Blue_Ball;}

    int get_Count_Red_Ball(){return count_Red_Ball;}

    int get_All_Count_Ball(){return count_Blue_Ball + count_Red_Ball;}

private:

    int num_Busket, num_Put_Busket, count_Blue_Ball, count_Red_Ball, last_Action = Actions::No_Action;

    float blue_Probability, red_Probability;


    void calculate_Probability(){

        this->blue_Probability = get_Probability(count_Blue_Ball, get_All_Count_Ball());

        this->red_Probability = get_Probability(count_Red_Ball, get_All_Count_Ball());


        emit float_Changed(blue_Probability);

        emit float_Changed(red_Probability);

    }


signals:

    void int_Changed(const int value);

    void float_Changed(const float value);

};

#endif // BUSKET_VALUES_H

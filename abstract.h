#ifndef ABSTRACT_H
#define ABSTRACT_H


class Abstract
{

protected:

    float get_Probability(int value, int all_Count){

        float answer = 0;

        if(all_Count != 0){

            answer = (float)(value * 100) / (all_Count);
        }

        return answer;
    }
};

#endif // ABSTRACT_H

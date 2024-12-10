#pragma once

#include <QObject>
#include <QMetaEnum>

class Actions
{
    Q_GADGET

public:

    enum Types{
        No_Action,
        Extracted_Blue_Ball,
        Extracted_Red_Ball,
        Error_Action

    };

   Q_ENUM(Types)

private:
    explicit Actions();
};

typedef Actions::Types My_Actions;


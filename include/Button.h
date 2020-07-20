//
// Created by PGD384 on 7/4/2020.
//

#ifndef ARDUPOMPER_BUTTON_H
#define ARDUPOMPER_BUTTON_H

class Button {
public:
    Button();

    virtual bool isPressed();

    virtual int getState();
};

#endif //ARDUPOMPER_BUTTON_H

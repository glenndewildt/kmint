//
// Created by administrator on 4-1-18.
//

#ifndef KMINTFRAMEWORK_BASE_STATE_H
#define KMINTFRAMEWORK_BASE_STATE_H

 class base_state {
private:
public:
    virtual ~base_state() {};

    virtual void check_state() {};

    virtual void update() {};

    virtual void draw() {};
};

#endif //KMINTFRAMEWORK_BASE_STATE_H

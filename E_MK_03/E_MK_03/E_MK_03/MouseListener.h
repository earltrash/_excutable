#pragma once
#include "IListener.h"
//using Callback = std::function<void(const MSG&)>;

class MouseListener : public IListener {
public:

    explicit MouseListener(Callback cb) : callback(std::move(cb)) {}
    void _OnEvent(const MSG& msg) override {
        if (callback) callback(msg);
    }

    bool Matches(const MSG& msg)const  override {
        return msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST;

    }
private:
    Callback callback; //button의 worked함수로 거의 고정일 거 같긴 함.

};
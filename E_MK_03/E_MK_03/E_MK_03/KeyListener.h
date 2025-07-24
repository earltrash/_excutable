#pragma once
#include "pch.h"
#include "IListener.h"
using Callback = std::function<void(const MSG&)>;

class KeyListener : public IListener
{
    explicit KeyListener(Callback cb) : callback(std::move(cb)) {}
    void _OnEvent(const MSG& msg) override {
        if (callback) callback(msg);
    }
    bool Matches(const MSG& msg)const  override {
        return msg.message == WM_KEYDOWN || msg.message == WM_KEYUP;
    } 
private:
    Callback callback;

};
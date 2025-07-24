#pragma once
#include "pch.h"
#include "Listener.h"

using Callback = std::function<void(const MSG&)>;

class MouseListenerComponent : public ListenerComponent //���ο� shared-raw-shared�� ������ ����ȭ�� ���� ����.
{
public:
	explicit MouseListenerComponent(Callback cb) : callback(std::move(cb)) {}
	~MouseListenerComponent() = default;

	void _OnEvent(const MSG& msg) override {

		if (callback) callback(msg);
	};
	bool Matches(const MSG& msg)const {
		return msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST;

	};  // ���� �ִ� �޽����� �ް�
private:
	Callback callback;
};

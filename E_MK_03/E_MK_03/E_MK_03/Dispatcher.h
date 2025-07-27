#pragma once
#include "pch.h"
#include "Listener.h"

using RawEventCallback = std::function<void(const MSG&)>;

class EventDispatcher {
public:

    EventDispatcher() = default;
    ~EventDispatcher() {

        // listeners.clear();
    };


    void AddListener(ListenerComponent* listener) { //IListener�� �׳� 
        listeners.push_back(listener);
    }

    void RemoveListener(ListenerComponent* listener) {

        /*listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
            [listener](ListenerComponent* ptr) {
                return ptr == listener;
            }),
            listeners.end());*/
        m_pendingRemove.emplace(listener);
    }// ��ü�� �����ϴ�, �̷������� ������ ���ϰ� �� �� ����, �� ���� �ϳ��� ����.

    void Broadcast(const MSG& msg) {

        for (size_t i = 0; i < listeners.size(); ++i) {
            ListenerComponent* l = listeners[i];

            if (!l) continue;

            if (std::find(m_pendingRemove.begin(), m_pendingRemove.end(), l) != m_pendingRemove.end())
                continue;

            // 3. ���� ����ִ� �����ʸ� �޽��� ó��
            if (l->Matches(msg))
                l->_OnEvent(msg);
        }

        for (auto& ptr : m_pendingRemove) {
            listeners.erase(std::remove(listeners.begin(), listeners.end(), ptr), listeners.end());
        }
        m_pendingRemove.clear();
    }

    void ListnerCount()
    {
        std::cout << listeners.size() << std::endl;
    }

    void clean() 
        //���ڱ� ���ų�, End Scene���� ���� ������ �� ��쿡 ���� �� �ֱ� ������ ���� 
        //���� �� �ڿ������� Scene ������ windowquit�� ȣ��� ���� x �׷��� �׳� ��������...
    {
        for (auto& e : listeners)
        {
            RemoveListener(e);
        }

        for (auto& ptr : m_pendingRemove) { 
            listeners.erase(std::remove(listeners.begin(), listeners.end(), ptr), listeners.end());
        }
        m_pendingRemove.clear();
    }

public:

    std::vector<ListenerComponent*> listeners;
    std::unordered_set<ListenerComponent*> m_pendingRemove; //use - after -free ����
};

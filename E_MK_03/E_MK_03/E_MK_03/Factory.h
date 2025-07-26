#pragma once
#include "pch.h"
#include "Object.h"
#include "Scene.h"

class ObjFactory {

    using ObjectCreator = std::function<std::unique_ptr<Object>()>;
    using SceneCreator = std::function<std::shared_ptr<SceneStandard>()>;
private:
    ObjFactory() = default;
    ~ObjFactory() = default;
public:

    static ObjFactory& Get(){
    
        static ObjFactory fac;
        return fac;
    }



    void RegisterObject(const std::string& name, ObjectCreator func) {
        m_objectCreators[name] = std::move(func);
    }


    void RegisterScene(const std::string& name, SceneCreator func) {
        m_SceneCreators[name] = std::move(func);
    }


    std::unique_ptr<Object> CreateObject(const std::string& name) {
        auto& creators = m_objectCreators;
        auto it = creators.find(name);
        if (it == creators.end()) {
            std::cerr << "Object key not registered: " << name << "\n";
            return nullptr;
        }
        return it->second();
    }


    std::shared_ptr<SceneStandard> CreateScene(const std::string& name) {
        return m_SceneCreators.at(name)();
    }


public:
    std::unordered_map<std::string, ObjectCreator> m_objectCreators;
    std::unordered_map<std::string, SceneCreator> m_SceneCreators;


};
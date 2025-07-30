#pragma once
#include "pch.h"
#include "Object.h"
#include "Scene.h"


class ObjFactory { //¾ê´Â ±×³É 

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


    std::unique_ptr<Object> CreateObject(const std::string& name) {
        auto& creators = m_objectCreators;
        auto it = creators.find(name);
        if (it == creators.end()) {
            std::cerr << "Object key not registered: " << name << "\n";
            return nullptr;
        }
        return it->second();
    }


public:
    std::unordered_map<std::string, ObjectCreator> m_objectCreators;


};
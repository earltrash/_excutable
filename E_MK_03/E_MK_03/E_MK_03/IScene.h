#pragma once
#include "pch.h"



class IScene //�̹��� RAII ��Ű��
{
public:
	IScene() = default;
	virtual ~IScene() = default; //
public:
	virtual void Initalize() = 0;
	virtual void Update() = 0;
	virtual void LogicUpdate(float delta) = 0;
	virtual void Clean() = 0;
	virtual void Enter()=0 ;
	virtual void Exit() =0;
};
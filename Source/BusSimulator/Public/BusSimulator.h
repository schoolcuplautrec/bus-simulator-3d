#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDefaultGameModuleImpl : public IModuleInterface
{
public:
	FDefaultGameModuleImpl();

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

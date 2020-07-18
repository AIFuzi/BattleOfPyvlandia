#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "MainGameSession.generated.h"


UCLASS()
class BATTLEOFPYVLANDIA_API AMainGameSession : public AGameSession
{
	GENERATED_BODY()
	
public:

	virtual void RegisterServer() override;


};

//#include "..//Public/Game/MainGameSession.h"
#include "MainGameSession.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

void AMainGameSession::RegisterServer()
{
	Super::RegisterServer();

	UE_LOG(LogTemp, Log, TEXT("Register server ----------------------"));
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	//if (SubSystem) return;

	IOnlineSessionPtr Session = SubSystem->GetSessionInterface();

	FOnlineSessionSettings OnlineSettings;
	OnlineSettings.bIsDedicated = true;
	OnlineSettings.bIsLANMatch = false;
	OnlineSettings.bAllowJoinInProgress = true;
	OnlineSettings.bShouldAdvertise = true;
	OnlineSettings.NumPublicConnections = 16;
	OnlineSettings.bUsesPresence = true;

	Session->CreateSession(0, GameSessionName, OnlineSettings);
	UE_LOG(LogTemp, Log, TEXT("Session create ----------------------"));
}
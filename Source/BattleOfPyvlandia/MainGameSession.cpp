#include "..//Public/Game/MainGameSession.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

void AMainGameSession::RegisterServer()
{
	UE_LOG(LogTemp, Log, TEXT("Register server ----------------------"));
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();

	IOnlineSessionPtr Session = SubSystem->GetSessionInterface();

	FOnlineSessionSettings OnlineSettings;
	OnlineSettings.bIsDedicated = true;
	OnlineSettings.bIsLANMatch = false;
	OnlineSettings.bAllowJoinInProgress = true;
	OnlineSettings.bShouldAdvertise = true;

	Session->CreateSession(0, GameSessionName, OnlineSettings);
	UE_LOG(LogTemp, Log, TEXT("Session create ----------------------"));
}
//Copyright 2020, Cody Dawe, All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Http.h"
#include "NaziZombieGameInstanceBase.generated.h"

USTRUCT(BlueprintType)
struct FMapInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString MapURL;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString MapName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString MapDescription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UTexture2D* MapImage;
};

USTRUCT(BlueprintType)
struct FServerData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ServerID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString IPAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ServerName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString MapName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int CurrentPlayers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxPlayers;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FServersReceived);

UCLASS()
class WORLDATWAR_API UNaziZombieGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
public:
	UNaziZombieGameInstanceBase();

protected:
	FHttpModule* Http;
	const FString WebAPIURL = FString("https://gametestserver.gear.host/api/Host/");
	//https://localhost:44389/api/Host
	//https://gametestserver.gear.host/api/Host

	TArray<FServerData> ServerList;

	UFUNCTION(BlueprintCallable)
		TArray<FServerData>& GetServerList();

	UPROPERTY(BlueprintAssignable)
		FServersReceived FOnServersReceived;

	UFUNCTION(BlueprintCallable)
		void GenerateServerList();

	void OnServerListRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);

	UFUNCTION(BlueprintCallable)
		void GoToMap(FString MAPURL);

public:
	const FString& GetWebAPIURL() {return WebAPIURL;}
};

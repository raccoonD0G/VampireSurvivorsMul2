// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/VSGameInstance.h"
#include "HttpModule.h"
#include "Json.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

void UVSGameInstance::Init()
{
	Super::Init();
    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    Settings->SetScreenResolution(FIntPoint(1280, 720));
    Settings->SetFullscreenMode(EWindowMode::Windowed);
    Settings->ApplySettings(false);
}

void UVSGameInstance::RequestJoinMatch()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

    Request->SetURL("http://127.0.0.1:8000/join-match");
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");
    Request->SetContentAsString(TEXT("{}")); 

    Request->OnProcessRequestComplete().BindUObject(this, &UVSGameInstance::OnJoinMatchResponse);
    Request->ProcessRequest();
}

void UVSGameInstance::OnJoinMatchResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to reach matchmaker server"));
        return;
    }

    FString ResponseStr = Response->GetContentAsString();

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);

    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        FString IP = JsonObject->GetStringField("ip");
        int32 Port = JsonObject->GetIntegerField("port");

        FString Address = FString::Printf(TEXT("%s:%d"), *IP, Port);
        UE_LOG(LogTemp, Log, TEXT("Connecting to server at %s"), *Address);

        UGameplayStatics::OpenLevel(GetWorld(), FName(*Address), true, TEXT("?listen"));
    }
}

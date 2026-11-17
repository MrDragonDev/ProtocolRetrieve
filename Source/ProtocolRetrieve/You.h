#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInterface.h"
#include "GameFramework/Character.h"
#include "You.generated.h"

UCLASS()
class PROTOCOLRETRIEVE_API AYou : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYou();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	AActor* PreviousActor = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void InteractLobby();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	UMaterialInterface* LobbyOutline;


	UFUNCTION()
	AActor* GetActorFromMouse();
};
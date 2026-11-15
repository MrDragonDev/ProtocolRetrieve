#include "You.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/MeshComponent.h"


// Sets default values
AYou::AYou()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> OutlineMaterial(TEXT("/Game/LobbyOutline.LobbyOutline"));

	if(OutlineMaterial.Succeeded()){
		LobbyOutline = OutlineMaterial.Object;
	}
}

// Called when the game starts or when spawned
void AYou::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PcGaming = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if(PcGaming){

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PcGaming->SetInputMode(InputMode);

		PcGaming->SetShowMouseCursor(true);
	}
}

// Called every frame
void AYou::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	InteractLobby();
}

// Called to bind functionality to input
void AYou::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AYou::InteractLobby(){
	AActor* HoveredActor = GetActorFromMouse();
	TArray<AActor*> FoundActor;

	if(HoveredActor != nullptr &&HoveredActor->ActorHasTag("InteractLobby")){
		UE_LOG(LogTemp, Warning, TEXT("Yay"));

// Gets the meshes (access to overlay)
		TArray<UMeshComponent*> MeshComp;
		HoveredActor->GetComponents<UMeshComponent>(MeshComp);

		for(UMeshComponent* CurrentMesh : MeshComp){
// Sets overlay
			CurrentMesh->SetOverlayMaterial(LobbyOutline);
		}
	}
}

AActor* AYou::GetActorFromMouse(){
	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	FHitResult hit;

	// Detect a click
	pc->GetHitResultUnderCursor(ECC_Visibility, true, hit);

	return hit.GetActor();
};
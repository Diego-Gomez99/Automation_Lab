#include "Misc/AutomationTest.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Mechanics/HealthComponent.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
FHealthComponentIntegrationTest,
"AutomationLab.Integration.HealthComponent.ActorDamage",
EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter
)

bool FHealthComponentIntegrationTest::RunTest(const FString& Parameters)
{
 AutomationOpenMap(TEXT("/Game/ThirdPerson/Maps/ThirdPersonMap"));
  // 1 Arrange: Get or load the testmap
 UWorld* World = nullptr;
 if(GEngine && GEngine->GetWorldContexts().Num() > 0)
 {
  World = GEngine->GetWorldContexts()[0].World();
 }

 if(!TestNotNull("The World must be load correctly", World))
 {
     return false;  
 }

  //2 Spawn actor in the level
 FActorSpawnParameters SpawnParams;
 AActor* TargetActor = World->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
  if(!TestNotNull("Target Actor must be created in the level",TargetActor))
  {
   return false;
  }

 // Dynamic creation and registration of the actor component
 UHealthComponent* HealthComp = NewObject<UHealthComponent>(TargetActor, TEXT("TestHealthComp"));
 HealthComp->RegisterComponent();
 HealthComp->InitializeHealth(100.0f,100.0f);
 
AddInfo(TEXT("[Integration] Actor and HealthComponent registered ans instaciaded on the level" ));

// 3 Action: Apply damage to the component attached to the actor
 HealthComp->TakeDamage(40.0f);

// 4 Assert: Validate the health after level interaction
TestEqual("The Actor's Health most be 60 HP  after received damage", HealthComp->GetCurrentHealth(), 60.0f);

// Cleanup: Destroy the actor
TargetActor->Destroy();

return true;

}


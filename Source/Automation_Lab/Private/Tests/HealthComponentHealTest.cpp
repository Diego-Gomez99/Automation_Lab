#include "Misc/AutomationTest.h"
#include "Mechanics/HealthComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
FHHealthComponentHealTest,
"AutomationLab.Mechanics.HealthComponent.Heal",
EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter
)

bool FHHealthComponentHealTest::RunTest(const FString& Parameters)
{

  // 1 Arrange
  UHealthComponent* HealthComp = NewObject<UHealthComponent>();
  HealthComp->InitializeHealth(100.0f, 50.0f); // Health Component Initialized with 50/100 HP
  AddInfo(TEXT("Health Component Initialized with 50/100 HP"));

  // 2 Action - Standard Healing
  HealthComp->Heal(30.0f);

 // 3 Validations - Partial Heal
 TestEqual("Current health should be 80 after healing 30 HP", HealthComp->GetCurrentHealth(), 80.0f);
 AddInfo(FString::Printf(TEXT("[Check 1] Normal heal applied correctly. Current health is %f"), HealthComp->GetCurrentHealth()));

 // 4 Action Try Overheal
 HealthComp->Heal(50.0f); // 80 + 50 = 130, but Maxhealth is 100

//  5 Validations - Health Limit 
TestEqual("Health should not exceed MaxHealth", HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());
AddInfo(TEXT("[CHECK 2] Overheal prevented successfully!!"));

return true;
}
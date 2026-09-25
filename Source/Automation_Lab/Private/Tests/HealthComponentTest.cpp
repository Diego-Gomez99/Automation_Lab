#include "Misc/AutomationTest.h"
#include "Mechanics/HealthComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
FHHealthComponentDamageTest,
"AutomationLab.Mechanics.HealthComponent.TakeDamage",
EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter
)

bool FHHealthComponentDamageTest::RunTest(const FString& Parameters)
{
 // 1 Arrange
 UHealthComponent* HealthComp = NewObject<UHealthComponent>();
 HealthComp->InitializeHealth(100.0f, 100.0f); 
 AddInfo(TEXT("[Step 1] Health Component initialized in 100 HP"));

 // 2 Action
 HealthComp->TakeDamage(30.0f);

 // 3 Validations
 TestEqual("The Current Health should be 70 after taking 30 of damage", HealthComp->GetCurrentHealth(), 70.0f);
 AddInfo(FString::Printf(TEXT("[CHECK 1] Salud reducida correctamente a: %f"), HealthComp->GetCurrentHealth()));

 TestFalse("The Character should not have been dead", HealthComp->GetIsDead());
 AddInfo(TEXT("[CHECK 2] Confirm: Character still alive!"));

 // Testing lethal damage
 HealthComp->TakeDamage(80.0f);
 TestEqual("Health should not be less than 0", HealthComp->GetCurrentHealth(), 0.0f);
 TestTrue("Character should be DEAD", HealthComp->GetIsDead());
 AddInfo(TEXT("[CHECK 3] Lethal damages applied: Character has dead!"));
 
 return true;

}
// These are the necessary headers for the HUD, user widget, and widget controller.
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

// Function to get or create the overlay widget controller.
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
    // If the OverlayWidgetController doesn't already exist, create a new one.
    if (!OverlayWidgetController)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        // Set the widget controller parameters after creation.
        OverlayWidgetController->SetWidgetControllerParams(WCParams);

        OverlayWidgetController->BindCallbacksToDependencies();

        return OverlayWidgetController;
    }
    // Return the overlay widget controller.
    return OverlayWidgetController;
}

// Initialization function for overlay.
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    // Ensure the Overlay classes are initialized properly.
    checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
    checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
    
    // Create a new user widget of the OverlayWidgetClass type.
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    // Cast the created user widget to AuraUserWidget.
    OverlayWidget = Cast<UAuraUserWidget>(Widget);
    
    // Fill up the widget controller parameters.
    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
    // Get or create the overlay widget controller with the given parameters.
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
    
    // Set the widget controller for the overlay widget.
    OverlayWidget->SetWidgetController(WidgetController);
    WidgetController->BroadcastInitialValues();

    // Add the widget to the viewport.
    Widget->AddToViewport();
}
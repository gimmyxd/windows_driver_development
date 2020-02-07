// Module Name:
//
//     elamsample.c
//
// Abstract:
//
//     This driver demonstrates how to use the Boot Driver Callback APIs
//     IoRegisterBootDriverCallback and IoUnRegisterBootDriverCallback and
//     the callback type PBOOT_DRIVER_CALLBACK_FUNCTION.
//
// Environment:
//
//     Kernel mode only.
//

#include "elamsample.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#endif // ALLOC_PRAGMA

//
// Trace level to use for kernel debugger DbgPrintEx output.
//

#define ELAMSAMPLE_TRACE_LEVEL DPFLTR_TRACE_LEVEL

//
// Callback handle returned by IoRegisterBootDriverCallback.
//

static PVOID g_IoRegisterBootDriverCallbackHandle = NULL;

//
// Current status update type from the callback.
//

static BDCB_STATUS_UPDATE_TYPE g_CurrentBcdCallbackContextType =
BdCbStatusPrepareForDependencyLoad;

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
/*++

Routine Description:

    This routine is called by the Operating System to initialize the driver.

    It creates the device object, fills in the dispatch entry points and
    completes the initialization.

Arguments:

    DriverObject - Supplies a pointer to the object that represents this device
         driver.

    RegistryPath - Supplies a pointer to the Services key in the registry.

Return Value:

    STATUS_SUCCESS if initialized successfully.

    Error status if the driver could not be initialized.

--*/
{
    WDF_OBJECT_ATTRIBUTES Attributes;
    WDF_DRIVER_CONFIG Config;
    WDFDRIVER Driver;
    NTSTATUS Status;

    DbgPrintEx(DPFLTR_IHVDRIVER_ID,
        DPFLTR_ERROR_LEVEL,
        "ElamSample simple is being initialized.\r\n");

    //
    // Initialize a non-PnP driver with the framework.
    //

    WDF_DRIVER_CONFIG_INIT(&Config, WDF_NO_EVENT_CALLBACK);

    Config.DriverInitFlags |= WdfDriverInitNonPnpDriver;

    //
    // Non-PnP drivers must register an unload routine.
    //

    Config.EvtDriverUnload = ElamSampleEvtDriverUnload;

    //
    // Create a framework driver object.
    //

    WDF_OBJECT_ATTRIBUTES_INIT(&Attributes);

    Status = WdfDriverCreate(DriverObject,
        RegistryPath,
        &Attributes,
        &Config,
        &Driver);

    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    return STATUS_SUCCESS;
}

VOID
ElamSampleEvtDriverUnload(
    _In_ WDFDRIVER Driver
)
/*++

Routine Description:

    This routine is called by the I/O subsystem before unloading the driver.

    It creates the device object, fills in the dispatch entry points and
    completes the initialization.

Arguments:

    Driver - Supplies a handle to a framework driver object.

Return Value:

    None.

--*/
{
    UNREFERENCED_PARAMETER(Driver);

    DbgPrintEx(DPFLTR_IHVDRIVER_ID,
        DPFLTR_ERROR_LEVEL,
        "ElamSample simple is being unloaded.\r\n");
}

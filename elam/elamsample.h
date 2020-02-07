/*++
Module Name:

    elamsample.h

Abstract:

    Contains function prototypes and includes other neccessary header files.

Environment:

    Kernel mode only.

--*/

//
// ------------------------------------------------------------------- Includes
//

#include <ntddk.h>
#include <wdf.h>

//
// -------------------------------------------------------- Function Prototypes
//

DRIVER_INITIALIZE
DriverEntry;
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

EVT_WDF_DRIVER_UNLOAD
ElamSampleEvtDriverUnload;
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





#include <xc.h>
#include <p33ep512mc502.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

void prvSetupHardware( void )
{
   BaseType_t xStatus;
   XScuGic_Config *pxGICConfig;

   portDISABLE_INTERRUPTS();

   pxGICConfig = XScuGic_LookupConfig( XPAR_SCUGIC_SINGLE_DEVICE_ID );

   configASSERT( pxGICConfig );
   configASSERT( pxGICConfig->CpuBaseAddress == ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET ) );
   configASSERT( pxGICConfig->DistBaseAddress == configINTERRUPT_CONTROLLER_BASE_ADDRESS );

   xStatus = XScuGic_CfgInitialize( &xInterruptController, pxGICConfig, pxGICConfig->CpuBaseAddress );
   configASSERT( xStatus == XST_SUCCESS );
   ( void ) xStatus; /* Remove compiler warning if configASSERT() is not defined. 
   xStatus = XScuGic_SelfTest(&xInterruptController);
   configASSERT( xStatus == XST_SUCCESS );

   ( void ) xStatus; /* Remove compiler warning if configASSERT() is not defined. */

   xTxMutex = xSemaphoreCreateMutex();
   configASSERT( xTxMutex );

   xPort = xSerialPortInitMinimal( configCLI_BAUD_RATE, cmdQUEUE_LENGTH );

   /* Disable cache on OCM */
   Xil_SetTlbAttributes(OCM_START_ADDR,0x14de2);  // S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0
}

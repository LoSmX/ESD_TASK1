//*****************************************************************************
//
// RGB_4x4_click
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

/* Defines */
#define T0H 42U
#define T0L 96U
#define T1H 84U
#define T1L 72U
#define TRES 7000U
#define IN1 GPIO_PORTP_BASE, GPIO_PIN_4

/* Prototypes */
void reset_4x4_rgb(void);   /* Sends signal for Reset */
void send_1_4x4_rgb(void);  /* Sends signal for 1 */
void send_0_4x4_rgb(void);  /* Sends signal for 0 */
void IN1_HIGH(void);        /* Set IN1 HIGH */
void IN1_LOW(void);         /* Set IN1 LOW */
void delay(unsigned int j);  /* Delays for a number of time */

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int
main(void)
{
    int j = 0;
    int i = 0;

    SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 120000000);

    //
    // Enable the GPIO port that is used for the IN1.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOP))
    {
    }

    //
    // Enable the GPIO pin for the LED (PP4).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_4);

    reset_4x4_rgb();

    //
    // Loop forever.
    //
    while(1)
    {
        for(j=0; j < 3; j++){

            // Green
            for(i=0; i < 8; i++){
                send_0_4x4_rgb();
            }
            // Red
            for(i=0; i < 8; i++){
                send_0_4x4_rgb();
            }
            // Blue
            for(i=0; i < 8; i++){
                send_1_4x4_rgb();
            }

            reset_4x4_rgb();
        }
    }
}

void reset_4x4_rgb(void){
    IN1_LOW();
    delay(TRES);
}

void send_1_4x4_rgb(void){
    IN1_HIGH();
    delay(T1H);

    IN1_LOW();
    delay(T1L);
}

void send_0_4x4_rgb(void){
    IN1_HIGH();
    delay(T0H);

    IN1_LOW();
    delay(T0L);
}

void IN1_HIGH(void){
    GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_4, 0x1);
}

void IN1_LOW(void){
    GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_4, 0x0);
}

void delay(unsigned int j){
    int i;
    for(i = 0; i < j; i++){
        SysCtlDelay(0);
    }
}

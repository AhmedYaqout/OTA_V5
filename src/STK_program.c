/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   15/Sept/2020
 *  Type    :   STK Program Executable File
 *  Version :   V2.0
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"
/* Define Callback Global pointer to function */
static void (*Global_pfCallback)(void);

/* Define Variable for interval mode */
static u8 STK_u8ModeOfInterval;

void STK_voidInit(void)
{ /* reset clock source bit 
    STK->CTRL &= ~(1 << STK_CLKSOURCE_LOCATION);*/
    /* switch on the clock source mode */
    switch (CLK_SOURCE)
    {
        /* if it is set to AHB/8 then set the bit to zero */
    case STK_AHB_DIV_8:
        STK->CTRL = STK_AHB_DIV_8;
        break;

        /* if the mode is set to AHB, then set the bit to one */
    case STK_AHB:
        STK->CTRL = STK_AHB;
        break;

        /* return error here if otherwise is written */
    default:
        /* error */
        break;
    }
}

void STK_voidSetBusyDelayMs(u32 Copy_u32TimeValue)
{ /* disable the system timer */
    CLR_BIT(STK->CTRL, 0);
    /* Enable interrupt */
   //SET_BIT(STK->CTRL,1);
    /* clear load value */
   // STK->LOAD = 0;
    /* get the clock source  */
    u8 Local_u8ClkSrc = GET_BIT(STK->CTRL, STK_CLKSOURCE_LOCATION);
    /* initialize local variable to store the actual working frequency */
    u32 Local_u32CurrentAHBFrequency = 0;
    /* initialize local variable to store the amount of ticks desired */
    u32 Local_u32DesiredTicks = 0;
    /* initialize local variable to store the number of overflows that are required */
    u32 Local_u32Overflow = 0;

    /* switch to get the actual working frequency */
    switch (Local_u8ClkSrc)
    {
        /* case the mode is AHB/8 */
    case STK_AHB_DIV_8:
        /* divide the original AHB frequency by 8 and then store them in the local variable*/
        Local_u32CurrentAHBFrequency = (STK_AHB_FREQUENCY / 8);
        break;
        /* case the mode is AHB */
    case STK_AHB:
        /* store the original frequency in the local variable  */
        Local_u32CurrentAHBFrequency = STK_AHB_FREQUENCY;
        break;

    default:
        /* Return Error */
        break;
    }
    /* convert the desired time, which is in milliseconds, to the required ticks */
    Local_u32DesiredTicks = ((Copy_u32TimeValue  * Local_u32CurrentAHBFrequency)/ 1000);
    /* checking if the number of ticks is within the resolution of the timer */
    if (Local_u32DesiredTicks <= 0x00FFFFFF)
    { /* load the desired ticks immediately on the RELOAD register */
        STK->LOAD = Local_u32DesiredTicks;
        /* Clear the value register which will clear the countflag as well */
        //STK->VAL = 0;
        /* Enable the timer itself to start counting down */
        SET_BIT(STK->CTRL,0);
        /* wait till the flag is risen to proceed */
        while (GET_BIT(STK->CTRL, STK_COUNTFLAG_LOCATION) != 1)
            ;
        /* disable the system timer */
        CLR_BIT(STK->CTRL, 0);
        /* clear load value */
        STK->LOAD = 0;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
    }
    else
    {
        /* On the condition that the desired ticks exceed the resolution, then the number of required overflows is calculated */
        Local_u32Overflow = Local_u32DesiredTicks / 0x00FFFFFF;
        /* initialize overflow counter */
        u8 i = 0;
        for (i = 0; i < Local_u32Overflow; i++)
        { /* set the load register to the maximum value the timer can handle */
            STK->LOAD = 0x00FFFFFF;
            /* Clear the value register which will clear the countflag as well */
            STK->VAL = 0;
            /* Enable the timer itself to start counting down */
            SET_BIT(STK->CTRL,0);
            /* wait till the flag is risen to proceed */
            while (GET_BIT(STK->CTRL, STK_COUNTFLAG_LOCATION) != 1)
                ;
            /* subtract that max value from the desired amount of ticks */
            Local_u32DesiredTicks -= 0x00FFFFFF;
        }
        /* At this stage, the desired amount of ticks should be less than resolution of timer */
        /* Set the remaining to the load register and repeat the same process like above */
        STK->LOAD = Local_u32DesiredTicks;
        STK->VAL = 0;
        SET_BIT(STK->CTRL,0);
        while (GET_BIT(STK->CTRL, STK_COUNTFLAG_LOCATION) != 1)
            ;
        /* disable the system timer */
        CLR_BIT(STK->CTRL, STK_DISABLE);
        /* clear load value */
        STK->LOAD = 0;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
    }
}

void STK_voidSetSingleIntervalDelayMs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void))
{
    Global_pfCallback = Copy_pfFunction;

    STK_u8ModeOfInterval = STK_SINGLE_INTERVAL;

    /* disable the system timer */
    STK->CTRL |= STK_DISABLE;

    /* Clear the interrupt pin*/
    CLR_BIT(STK->CTRL, STK_TICKINT_LOCATION);

    /* clear load value */
    STK->LOAD = 0;

    /* get the clock source  */
    u8 Local_u8ClkSrc = GET_BIT(STK->CTRL, STK_CLKSOURCE_LOCATION);

    /* initialize local variable to store the actual working frequency */
    u32 Local_u32CurrentAHBFrequency = 0;

    /* initialize local variable to store the amount of ticks desired */
    u32 Local_u32DesiredTicks = 0;

    /* initialize local variable to store the number of overflows that are required */
    u32 Local_u32Overflow = 0;

    /* switch to get the actual working frequency */
    switch (Local_u8ClkSrc)
    {
        /* case the mode is AHB/8 */
    case STK_AHB_DIV_8:
        /* divide the original AHB frequency by 8 and then store them in the local variable*/
        Local_u32CurrentAHBFrequency = (STK_AHB_FREQUENCY / 8);
        break;
        /* case the mode is AHB */
    case STK_AHB:
        /* store the original frequency in the local variable  */
        Local_u32CurrentAHBFrequency = STK_AHB_FREQUENCY;
        break;

    default:
        /* Return Error */
        break;
    }
    /* convert the desired time, which is in milliseconds, to the required ticks */
    Local_u32DesiredTicks = ((Copy_u32TimeValue  * Local_u32CurrentAHBFrequency)/ 1000);
    /* checking if the number of ticks is within the resolution of the timer */
    if (Local_u32DesiredTicks <= 0x00FFFFFF)
    { /* load the desired ticks immediately on the RELOAD register */
        STK->LOAD = Local_u32DesiredTicks;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
        /* Enable the sytem timer interrupt */
        STK->CTRL |= STK_INTERRUPT_EN;
        /* Enable the timer itself to start counting down */
        STK->CTRL |= STK_ENABLE;
        /* wait till the flag is risen to proceed */
    }
    else
    {
        /* On the condition that the desired ticks exceed the resolution, then the number of required overflows is calculated */
        Local_u32Overflow = Local_u32DesiredTicks / 0x00FFFFFF;
        /* initialize overflow counter */
        u8 i = 0;
        for (i = 0; i < Local_u32Overflow; i++)
        { /* set the load register to the maximum value the timer can handle */
            STK->LOAD = 0x00FFFFFF;
            /* Clear the value register which will clear the countflag as well */
            STK->VAL = 0;
            /* Enable the sytem timer interrupt */
            STK->CTRL |= STK_INTERRUPT_EN;
            /* Enable the timer itself to start counting down */
            STK->CTRL |= STK_ENABLE;
            /* subtract that max value from the desired amount of ticks */
            Local_u32DesiredTicks -= 0x00FFFFFF;
        }
        /* At this stage, the desired amount of ticks should be less than resolution of timer */
        /* Set the remaining to the load register and repeat the same process like above */
        STK->LOAD = Local_u32DesiredTicks;
        STK->VAL = 0;
        STK->CTRL |= STK_INTERRUPT_EN;
        STK->CTRL |= STK_ENABLE;
    }
}

void STK_voidSetPeriodicDelayMs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void))
{
    STK_u8ModeOfInterval = STK_PERIOD_INTERVAL;

    Global_pfCallback = Copy_pfFunction;
    
    /* disable the system timer */
    STK->CTRL |= STK_DISABLE;
    
    /* Clear the interrupt pin*/
    CLR_BIT(STK->CTRL, STK_TICKINT_LOCATION);
    
    /* clear load value */
    STK->LOAD = 0;
    
    /* get the clock source  */
    u8 Local_u8ClkSrc = GET_BIT(STK->CTRL, STK_CLKSOURCE_LOCATION);
    
    /* initialize local variable to store the actual working frequency */
    u32 Local_u32CurrentAHBFrequency = 0;
    
    /* initialize local variable to store the amount of ticks desired */
    u32 Local_u32DesiredTicks = 0;
    
    /* initialize local variable to store the number of overflows that are required */
    u32 Local_u32Overflow = 0;

    /* switch to get the actual working frequency */
    switch (Local_u8ClkSrc)
    {
        /* case the mode is AHB/8 */
    case STK_AHB_DIV_8:
       
        /* divide the original AHB frequency by 8 and then store them in the local variable*/
        Local_u32CurrentAHBFrequency = (STK_AHB_FREQUENCY / 8);
        break;
       
        /* case the mode is AHB */
    case STK_AHB:
       
        /* store the original frequency in the local variable  */
        Local_u32CurrentAHBFrequency = STK_AHB_FREQUENCY;
       
        break;

    default:
        /* Return Error */
        break;
    }
    /* convert the desired time, which is in milliseconds, to the required ticks */
    Local_u32DesiredTicks = ((Copy_u32TimeValue  * Local_u32CurrentAHBFrequency)/ 1000);
    /* checking if the number of ticks is within the resolution of the timer */
    if (Local_u32DesiredTicks <= 0x00FFFFFF)
    { /* load the desired ticks immediately on the RELOAD register */
       /*  STK->LOAD = Local_u32DesiredTicks - 1; */
        STK->LOAD = Local_u32DesiredTicks;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
        /* Enable the sytem timer interrupt */
        STK->CTRL |= STK_INTERRUPT_EN;
        /* Enable the timer itself to start counting down */
        STK->CTRL |= STK_ENABLE;
        /* wait till the flag is risen to proceed */
    }
    else
    {
        /* On the condition that the desired ticks exceed the resolution, then the number of required overflows is calculated */
        Local_u32Overflow = Local_u32DesiredTicks / 0x00FFFFFF;
        /* initialize overflow counter */
        u8 i = 0;
        for (i = 0; i < Local_u32Overflow; i++)
        { /* set the load register to the maximum value the timer can handle */
            STK->LOAD = 0x00FFFFFF;
            /* Clear the value register which will clear the countflag as well */
            STK->VAL = 0;
            /* Enable the sytem timer interrupt */
            STK->CTRL |= STK_INTERRUPT_EN;
            /* Enable the timer itself to start counting down */
            STK->CTRL |= STK_ENABLE;
            /* subtract that max value from the desired amount of ticks */
            Local_u32DesiredTicks -= 0x00FFFFFF;
        }
        /* At this stage, the desired amount of ticks should be less than resolution of timer */
        /* Set the remaining to the load register and repeat the same process like above */
        STK->LOAD = Local_u32DesiredTicks - 1;
        STK->VAL = 0;
        STK->CTRL |= STK_INTERRUPT_EN;
        STK->CTRL |= STK_ENABLE;
    }
}
void STK_voidStartTimer  ( void )
{
	/*Disable Timer*/
	CLR_BIT(STK -> CTRL,0);

	/* Disable STK Interrupt */
	CLR_BIT(STK->CTRL, 1);

	/*Clear Value Register*/
	STK->VAL=0;
	STK->LOAD=1000000;
	/* Start Timer */
	SET_BIT(STK->CTRL, 0);
}
void STK_voidStopTimer(void)
{
    CLR_BIT(STK->CTRL, STK_ENABLE_LOCATION);

    /* Disable the interrupt pin*/
    CLR_BIT(STK->CTRL, STK_TICKINT_LOCATION);

    /* clear load value */
    STK->LOAD = 0;

    STK->VAL = 0;
}
u32 STK_u32GetElapsedTime(void)
{
	static u32 Local_u32Time=0;
	Local_u32Time= (STK->LOAD - STK->VAL);
	return Local_u32Time;
}
u32 STK_u32GetRemainingTime(void)
{
	static u32 Local_u32Time=0;
    	Local_u32Time = STK->VAL;
	return Local_u32Time;
}

void STK_voidSetBusyDelayUs(u32 Copy_u32TimeValue)
{ /* disable the system timer */
    STK->CTRL |= STK_DISABLE;
    /* clear load value */
    STK->LOAD = 0;
    /* get the clock source  */
    u8 Local_u8ClkSrc = GET_BIT(STK->CTRL, STK_CLKSOURCE_LOCATION);
    /* initialize local variable to store the actual working frequency */
    u32 Local_u32CurrentAHBFrequency = 0;
    /* initialize local variable to store the amount of ticks desired */
    u32 Local_u32DesiredTicks = 0;
    /* initialize local variable to store the number of overflows that are required */
    u32 Local_u32Overflow = 0;

    /* switch to get the actual working frequency */
    switch (Local_u8ClkSrc)
    {
        /* case the mode is AHB/8 */
    case STK_AHB_DIV_8:
        /* divide the original AHB frequency by 8 and then store them in the local variable*/
        Local_u32CurrentAHBFrequency = (STK_AHB_FREQUENCY / 8);
        break;
        /* case the mode is AHB */
    case STK_AHB:
        /* store the original frequency in the local variable  */
        Local_u32CurrentAHBFrequency = STK_AHB_FREQUENCY;
        break;

    default:
        /* Return Error */
        break;
    }
    /* convert the desired time, which is in milliseconds, to the required ticks */
    Local_u32DesiredTicks = (Copy_u32TimeValue  * Local_u32CurrentAHBFrequency)/1000000;
    /* checking if the number of ticks is within the resolution of the timer */
    if (Local_u32DesiredTicks <= 0x00FFFFFF)
    { /* load the desired ticks immediately on the RELOAD register */
        STK->LOAD = Local_u32DesiredTicks;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
        /* Enable the timer itself to start counting down */
        STK->CTRL |= STK_ENABLE;
        /* wait till the flag is risen to proceed */
        while (GET_BIT(STK->CTRL, STK_COUNTFLAG_LOCATION) != 1)
            ;
        /* disable the system timer */
        STK->CTRL |= STK_DISABLE;
        /* clear load value */
        STK->LOAD = 0;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
    }
    else
    {
        /* On the condition that the desired ticks exceed the resolution, then the number of required overflows is calculated */
        Local_u32Overflow = Local_u32DesiredTicks / 0x00FFFFFF;
        /* initialize overflow counter */
        u8 i = 0;
        for (i = 0; i < Local_u32Overflow; i++)
        { /* set the load register to the maximum value the timer can handle */
            STK->LOAD = 0x00FFFFFF;
            /* Clear the value register which will clear the countflag as well */
            STK->VAL = 0;
            /* Enable the timer itself to start counting down */
            STK->CTRL |= STK_ENABLE;
            /* wait till the flag is risen to proceed */
            while (GET_BIT(STK->CTRL, STK_COUNTFLAG_LOCATION) != 1)
                ;
            /* subtract that max value from the desired amount of ticks */
            Local_u32DesiredTicks -= 0x00FFFFFF;
        }
        /* At this stage, the desired amount of ticks should be less than resolution of timer */
        /* Set the remaining to the load register and repeat the same process like above */
        STK->LOAD = Local_u32DesiredTicks;
        STK->VAL = 0;
        STK->CTRL |= STK_ENABLE;
        while (GET_BIT(STK->CTRL, STK_COUNTFLAG_LOCATION) != 1)
            ;
        /* disable the system timer */
        STK->CTRL |= STK_DISABLE;
        /* clear load value */
        STK->LOAD = 0;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
    }
}

void STK_voidSetSingleIntervalDelayUs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void))
{
    Global_pfCallback = Copy_pfFunction;

    STK_u8ModeOfInterval = STK_SINGLE_INTERVAL;

    /* disable the system timer */
    STK->CTRL |= STK_DISABLE;

    /* Clear the interrupt pin*/
    CLR_BIT(STK->CTRL, STK_TICKINT_LOCATION);

    /* clear load value */
    STK->LOAD = 0;

    /* get the clock source  */
    u8 Local_u8ClkSrc = GET_BIT(STK->CTRL, STK_CLKSOURCE_LOCATION);

    /* initialize local variable to store the actual working frequency */
    u32 Local_u32CurrentAHBFrequency = 0;

    /* initialize local variable to store the amount of ticks desired */
    u32 Local_u32DesiredTicks = 0;

    /* initialize local variable to store the number of overflows that are required */
    u32 Local_u32Overflow = 0;

    /* switch to get the actual working frequency */
    switch (Local_u8ClkSrc)
    {
        /* case the mode is AHB/8 */
    case STK_AHB_DIV_8:
        /* divide the original AHB frequency by 8 and then store them in the local variable*/
        Local_u32CurrentAHBFrequency = (STK_AHB_FREQUENCY / 8);
        break;
        /* case the mode is AHB */
    case STK_AHB:
        /* store the original frequency in the local variable  */
        Local_u32CurrentAHBFrequency = STK_AHB_FREQUENCY;
        break;

    default:
        /* Return Error */
        break;
    }
    /* convert the desired time, which is in milliseconds, to the required ticks */
    Local_u32DesiredTicks = (Copy_u32TimeValue  * Local_u32CurrentAHBFrequency)/1000000;
    /* checking if the number of ticks is within the resolution of the timer */
    if (Local_u32DesiredTicks <= 0x00FFFFFF)
    { /* load the desired ticks immediately on the RELOAD register */
        STK->LOAD = Local_u32DesiredTicks;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
        /* Enable the sytem timer interrupt */
        STK->CTRL |= STK_INTERRUPT_EN;
        /* Enable the timer itself to start counting down */
        STK->CTRL |= STK_ENABLE;
        /* wait till the flag is risen to proceed */
    }
    else
    {
        /* On the condition that the desired ticks exceed the resolution, then the number of required overflows is calculated */
        Local_u32Overflow = Local_u32DesiredTicks / 0x00FFFFFF;
        /* initialize overflow counter */
        u8 i = 0;
        for (i = 0; i < Local_u32Overflow; i++)
        { /* set the load register to the maximum value the timer can handle */
            STK->LOAD = 0x00FFFFFF;
            /* Clear the value register which will clear the countflag as well */
            STK->VAL = 0;
            /* Enable the sytem timer interrupt */
            STK->CTRL |= STK_INTERRUPT_EN;
            /* Enable the timer itself to start counting down */
            STK->CTRL |= STK_ENABLE;
            /* subtract that max value from the desired amount of ticks */
            Local_u32DesiredTicks -= 0x00FFFFFF;
        }
        /* At this stage, the desired amount of ticks should be less than resolution of timer */
        /* Set the remaining to the load register and repeat the same process like above */
        STK->LOAD = Local_u32DesiredTicks;
        STK->VAL = 0;
        STK->CTRL |= STK_INTERRUPT_EN;
        STK->CTRL |= STK_ENABLE;
    }
}

void STK_voidSetPeriodicDelayUs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void))
{
    STK_u8ModeOfInterval = STK_PERIOD_INTERVAL;

    Global_pfCallback = Copy_pfFunction;
    
    /* disable the system timer */
    STK->CTRL |= STK_DISABLE;
    
    /* Clear the interrupt pin*/
    CLR_BIT(STK->CTRL, STK_TICKINT_LOCATION);
    
    /* clear load value */
    STK->LOAD = 0;
    
    /* get the clock source  */
    u8 Local_u8ClkSrc = GET_BIT(STK->CTRL, STK_CLKSOURCE_LOCATION);
    
    /* initialize local variable to store the actual working frequency */
    u32 Local_u32CurrentAHBFrequency = 0;
    
    /* initialize local variable to store the amount of ticks desired */
    u32 Local_u32DesiredTicks = 0;
    
    /* initialize local variable to store the number of overflows that are required */
    u32 Local_u32Overflow = 0;

    /* switch to get the actual working frequency */
    switch (Local_u8ClkSrc)
    {
        /* case the mode is AHB/8 */
    case STK_AHB_DIV_8:
       
        /* divide the original AHB frequency by 8 and then store them in the local variable*/
        Local_u32CurrentAHBFrequency = (STK_AHB_FREQUENCY / 8);
        break;
       
        /* case the mode is AHB */
    case STK_AHB:
       
        /* store the original frequency in the local variable  */
        Local_u32CurrentAHBFrequency = STK_AHB_FREQUENCY;
       
        break;

    default:
        /* Return Error */
        break;
    }
    /* convert the desired time, which is in milliseconds, to the required ticks */
    Local_u32DesiredTicks = (Copy_u32TimeValue  * Local_u32CurrentAHBFrequency)/1000000;
    /* checking if the number of ticks is within the resolution of the timer */
    if (Local_u32DesiredTicks <= 0x00FFFFFF)
    { /* load the desired ticks immediately on the RELOAD register */
       /*  STK->LOAD = Local_u32DesiredTicks - 1; */
        STK->LOAD = Local_u32DesiredTicks;
        /* Clear the value register which will clear the countflag as well */
        STK->VAL = 0;
        /* Enable the sytem timer interrupt */
        STK->CTRL |= STK_INTERRUPT_EN;
        /* Enable the timer itself to start counting down */
        STK->CTRL |= STK_ENABLE;
        /* wait till the flag is risen to proceed */
    }
    else
    {
        /* On the condition that the desired ticks exceed the resolution, then the number of required overflows is calculated */
        Local_u32Overflow = Local_u32DesiredTicks / 0x00FFFFFF;
        /* initialize overflow counter */
        u8 i = 0;
        for (i = 0; i < Local_u32Overflow; i++)
        { /* set the load register to the maximum value the timer can handle */
            STK->LOAD = 0x00FFFFFF;
            /* Clear the value register which will clear the countflag as well */
            STK->VAL = 0;
            /* Enable the sytem timer interrupt */
            STK->CTRL |= STK_INTERRUPT_EN;
            /* Enable the timer itself to start counting down */
            STK->CTRL |= STK_ENABLE;
            /* subtract that max value from the desired amount of ticks */
            Local_u32DesiredTicks -= 0x00FFFFFF;
        }
        /* At this stage, the desired amount of ticks should be less than resolution of timer */
        /* Set the remaining to the load register and repeat the same process like above */
        STK->LOAD = Local_u32DesiredTicks - 1;
        STK->VAL = 0;
        STK->CTRL |= STK_INTERRUPT_EN;
        STK->CTRL |= STK_ENABLE;
    }
}


void STK_Handler(void)
{

    if (STK_u8ModeOfInterval == STK_SINGLE_INTERVAL)
    {
        /* disable the system timer */
        STK->CTRL |= STK_DISABLE;

        /* Clear the interrupt pin*/
        CLR_BIT(STK->CTRL, STK_TICKINT_LOCATION);
        
        /* clear load value */
        STK->LOAD = 0;
        STK->VAL = 0;
    }
    Global_pfCallback();
    CLR_BIT(STK->CTRL,STK_COUNTFLAG_LOCATION);
}

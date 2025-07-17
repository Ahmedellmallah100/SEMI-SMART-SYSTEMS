#include "Adc_interface.h"
#include "../../Library/bit_math.h"
#include "../../Library/std_Bytes.h"
#include "Adc_private.h"
#include "Adc_config.h"








void AdcVoid_init(void){

//Select Reference Voltage  
#if    (REFERENCE_VOLTAGE ==AREF) 
     Clear_BIT(ADMUX_REG,6);
     Clear_BIT(ADMUX_REG,7);
#elif  (REFERENCE_VOLTAGE ==AVCC) 
     SET_BIT  (ADMUX_REG,6);
     Clear_BIT (ADMUX_REG,7);
#elif  (REFERENCE_VOLTAGE ==INTERNAL) 
     SET_BIT  (ADMUX_REG,6);
     SET_BIT  (ADMUX_REG,7);
#else
     Clear_BIT (ADMUX_REG,6);
     SET_BIT   (ADMUX_REG,7);
     #endif
 //********************************************************** 
 //********************************************************** 
//Select Right or Left Adjust
#if   (ADJUST == RIGHT )
     Clear_BIT (ADMUX_REG ,5);
#elif (ADJUST == LEFT )
     SET_BIT (ADMUX_REG ,5);
#endif
//********************************************************** 
//********************************************************** 
//Select ADC Enable
#if   (ADEN ==ENABLE)
    SET_BIT (ADCSRA_REG , 7);

#elif (ADEN ==DISABLE)
   Clear_BIT (ADCSRA_REG , 7);
   #endif
 //********************************************************** 
 //********************************************************** 
 // ADC auto Toggle 
#if   (ADATE ==ENABLE)
    SET_BIT (ADCSRA_REG , 5);
      #if( AUTO_TRIGGER_SOURCE == Free_Running_Mode )
      Clear_BIT(SFIOR_REG ,5);
      Clear_BIT(SFIOR_REG ,6);
      Clear_BIT(SFIOR_REG ,7);
      #elif (AUTO_TRIGGER_SOURCE == Analog_Comparator )
      SET_BIT(SFIOR_REG ,5);
      Clear_BIT(SFIOR_REG ,6);
      Clear_BIT(SFIOR_REG ,7);
      #elif (AUTO_TRIGGER_SOURCE == External_Interrupt_Request_0 )
      Clear_BIT(SFIOR_REG ,5);
      SET_BIT(SFIOR_REG ,6);
      Clear_BIT(SFIOR_REG ,7);
      #elif (AUTO_TRIGGER_SOURCE == Timer_Counter0_Compare_Match )
      SET_BIT(SFIOR_REG ,5);
      SET_BIT(SFIOR_REG ,6);
      Clear_BIT(SFIOR_REG ,7);
      #elif (AUTO_TRIGGER_SOURCE == Timer_Counter0_Overflow )
      Clear_BIT(SFIOR_REG ,5);
      Clear_BIT(SFIOR_REG ,6);
      SET_BIT(SFIOR_REG ,7);
      #elif (AUTO_TRIGGER_SOURCE == Timer_Counter1_Compare_MatchB )
      SET_BIT(SFIOR_REG ,5);
      Clear_BIT(SFIOR_REG ,6);
      SET_BIT(SFIOR_REG ,7);
      #elif (AUTO_TRIGGER_SOURCE == Timer_Counter1_Overflow )
      Clear_BIT(SFIOR_REG ,5);
      SET_BIT(SFIOR_REG ,6);
      SET_BIT(SFIOR_REG ,7);
      #elif (AUTO_TRIGGER_SOURCE == Timer_Counter1_Capture_Event )
    SET_BIT(SFIOR_REG ,5);
    SET_BIT(SFIOR_REG ,6);
    SET_BIT(SFIOR_REG ,7);
    #endif


#elif (ADATE ==DISABLE)
   Clear_BIT (ADCSRA_REG , 5);

   #endif
 //********************************************************** 
 //********************************************************** 
// Interput Enable and Disable
#if (ADIE ==ENABLE)
    SET_BIT (ADCSRA_REG ,3); // work with Interrupt
#elif (ADIE ==DISABLE)
    Clear_BIT (ADCSRA_REG ,3); // work with Polling

#endif
 //********************************************************** 
 //********************************************************** 
   // Select Adc Prescaler Select Bit
   // Decease frequency in micro controller

#if (PRESCALE == NOT_USE_PRESCALER)
//no thing happen
#elif (PRESCALE ==PRESCALER_DIVISION_BY_2)
      SET_BIT(ADCSRA_REG ,0);
      Clear_BIT(ADCSRA_REG ,1);
      Clear_BIT(ADCSRA_REG ,2);
#elif (PRESCALE ==PRESCALER_DIVISION_BY_4)
      Clear_BIT(ADCSRA_REG ,0);
      SET_BIT(ADCSRA_REG ,1);
      Clear_BIT(ADCSRA_REG ,2);
#elif (PRESCALE ==PRESCALER_DIVISION_BY_8)
      SET_BIT(ADCSRA_REG ,0);
      SET_BIT(ADCSRA_REG ,1);
      Clear_BIT(ADCSRA_REG ,2);
#elif (PRESCALE ==PRESCALER_DIVISION_BY_16)
      Clear_BIT(ADCSRA_REG ,0);
      Clear_BIT(ADCSRA_REG ,1);
      SET_BIT(ADCSRA_REG ,2);
#elif (PRESCALE ==PRESCALER_DIVISION_BY_32)
      SET_BIT(ADCSRA_REG ,0);
      Clear_BIT(ADCSRA_REG ,1);
      SET_BIT(ADCSRA_REG ,2);
#elif (PRESCALE ==PRESCALER_DIVISION_BY_64)
      Clear_BIT(ADCSRA_REG ,0);
      SET_BIT(ADCSRA_REG ,1);
      SET_BIT(ADCSRA_REG ,2);
#elif (PRESCALE ==PRESCALER_DIVISION_BY_128)
      SET_BIT(ADCSRA_REG ,0);
      SET_BIT(ADCSRA_REG ,1);
      SET_BIT(ADCSRA_REG ,2);

      #endif 
 
}










u16 ADC_u16ReadASynchronus ( u8 u8ChannelNumber  ) {

// Clear Mux
ADMUX_REG =( ADMUX_REG & 0b11110000); // I want to Clear Only First 4Bits so 0000 and Second 4Bits Still Same

//Select Channel
switch (u8ChannelNumber)
{
case ADC0: ADMUX_REG = ADMUX_REG | 0b00000000;             break;
case ADC1: ADMUX_REG = ADMUX_REG | 0b00000001;             break;
case ADC2: ADMUX_REG = ADMUX_REG | 0b00000010;             break;
case ADC3: ADMUX_REG = ADMUX_REG | 0b00000011;             break;
case ADC4: ADMUX_REG = ADMUX_REG | 0b00000100;             break;
case ADC5: ADMUX_REG = ADMUX_REG | 0b00000101;             break;
case ADC6: ADMUX_REG = ADMUX_REG | 0b00000110;             break;
case ADC7: ADMUX_REG = ADMUX_REG | 0b00000111;             break;

default:                                                   break;
}

//Start Channel
//Start Converstion
#if (ADATE ==ENABLE)
        // Start Conversion When Triggering Occures.
#elif (ADATE ==DISABLE)
        SET_BIT(ADCSRA_REG,6);  

#endif
//--------------------------------
#if (ADIE ==ENABLE)   // work with Interrupt
        // Start Conversion When Triggering Occures.
#elif (ADIE ==DISABLE)  // work with Polling
  u8 ADIF=0 ;
        while( ADIF == 0 )
        {
            ADIF = GET_BIT(ADCSRA_REG,4);    // Stuck on while untill Flag Raising 1 .
        }
#endif
//--------------------------------
#if (ADIE ==ENABLE)   // work with Interrupt
        // When ADC Finish conversion will Raising Interrupt Flag and Jump to ADC_ISR Function.    
#elif (ADIE ==DISABLE)  // work with Polling
/* Clear Flag */
SET_BIT(ADCSRA_REG,4);
#endif
  


//************************************** */
//Read Data
#if (ADJUST ==RIGHT)
return ADC_REG; // dont lose Data
#elif (ADJUST ==LEFT)
return ADCH_REG; //you will lose 2 data from ADCL
#endif
//************************************** */

    }
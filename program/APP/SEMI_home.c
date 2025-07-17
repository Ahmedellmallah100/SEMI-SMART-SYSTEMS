#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "../Library/std_Bytes.h"
#include "../Library/bit_math.h"
#include "../MCAL/Dio/Dio_interface.h"
#include "../HALL/7_Segment/7_segment_inter.h"
#include "../HALL/Led/Led_interface.h"
#include "../HALL/kypad/kypad_interface.h"
#include "../HALL/Lcd/Lcd_interface.h"
#include "../MCAL/ADC/Adc_config.h"
#include "../MCAL/ADC/Adc_interface.h"
#include "../MCAL/ADC/Adc_private.h"

#define line0 0
#define line1 1

#define TEMP_CHANNEL       ADC0     
#define LDR_CHANNEL        ADC1     
#define BUZZER_PORT        PORTD
#define BUZZER_PIN         PIN1
#define LED_PORT           PORTD
#define LED_PIN            PIN0

}

int main () {
    AdcVoid_init();
    lcd_init();
    DIO_voidSetPinDirect(BUZZER_PORT, BUZZER_PIN, OUTPUT);
    DIO_voidSetPinDirect(LED_PORT, LED_PIN, OUTPUT);

    lcdsend_cursor_atPosition(line0, 0);
    LCD_voidWriteString("SEMI SMART SYS");
    lcdsend_cursor_atPosition(line1, 0);
    LCD_voidWriteString("By AHMED HAMED");
    _delay_ms(1000);
    LCD_voidClearDisplay();

    while (1)
    {
        // Read TEMP
        u16 adc_temp = ADC_u16ReadASynchronus(TEMP_CHANNEL);
        u16 temp_mv = (adc_temp * 5000UL) / 1024;
        u16 temperature = temp_mv / 10;

        // TEMP DISPLAY ON LINE 1
        lcd_clear_line(line1);
        lcdsend_cursor_atPosition(line1, 0);
        LCD_voidWriteString("TEMP=");
        LCD_voidWrite_u32Number(temperature);
        LCD_voidWriteString(" C");

        // CHECK TEMP >= 50
        if (temperature >= 50) {
            DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, High);

            // Show FIRE message on line 0
            lcd_clear_line(line0);
            lcdsend_cursor_atPosition(line0, 0);
            LCD_voidWriteString(" FIRE...FIRE");
        } else {
            DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, Low);



        // Read LIGHT
        u16 light_read = ADC_u16ReadASynchronus(LDR_CHANNEL); 
        u8 light_percent = (light_read * 100UL) / 1023;

            // Show LIGHT info on line 0
            lcd_clear_line(line0);
            lcdsend_cursor_atPosition(line0, 0);
            LCD_voidWriteString("Light:");
            LCD_voidWrite_u32Number(light_percent);
            if (light_percent < 40) {
                LCD_voidWriteString(" Dark");
                DIO_voidSetPinValue(LED_PORT, LED_PIN, High);
            } else {
                LCD_voidWriteString(" Bright");
                DIO_voidSetPinValue(LED_PORT, LED_PIN, Low);
            }
        }

        _delay_ms(100);
    }

    return 0;
}

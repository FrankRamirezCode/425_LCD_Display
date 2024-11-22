/*
 * @file main.c
 *
 * @brief Main source code for the LCD Menu Design program.
 *
 * This file contains the main entry point and function definitions for the LCD Menu Design program.
 * It interfaces with the following:
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board 16x2 Liquid Crystal Display (LCD)
 *  - PMOD ENC Module (Rotary Encoder)
 *
 * @note For more information regarding the LCD, refer to the HD44780 LCD Controller Datasheet.
 * Link: https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
 *
 * @author
 */

#include "TM4C123GH6PM.h"
#include "string.h"
#include "EduBase_LCD.h"
#include "EduBase_Button_Interrupt.h"
#include "PMOD_ENC.h"
#include "Timer_0A_Interrupt.h"

#define MAX_COUNT 8

static uint8_t state = 0;
static uint8_t last_state = 0;
static uint8_t pmod_enc_btn_pressed = 0;
static int prev_main_menu_counter = 0xFF;
static int main_menu_counter = 0;

void PMOD_ENC_Task(void);

void Display_Main_Menu(int main_menu_state);

void Process_Main_Menu_Selection(void);

int main(void)
{
	SysTick_Delay_Init();
	
	EduBase_LCD_Init();
	
	PMOD_ENC_Init();
	
	Timer_0A_Interrupt_Init(&PMOD_ENC_Task);
	
	last_state = PMOD_ENC_Get_State();
	
	EduBase_LCD_Create_Custom_Character(HEART_SHAPE_LOCATION, heart_shape);
	EduBase_LCD_Create_Custom_Character(RIGHT_ARROW_LOCATION, right_arrow);
	
	EduBase_LEDs_Init;
	
//	while(1)
//	{
//		EduBase_LCD_Set_Cursor(0,0);
//		EduBase_LCD_Display_String("Error");
//		
//		EduBase_LCD_Set_Cursor(0,1);
//		EduBase_LCD_Display_Integer(123456789);
//		
//		SysTick_Delay1ms(100);
//		
//		for (int i = 0; i < 7; i++)
//		{
//			EduBase_LCD_Scroll_Display_Right();
//			SysTick_Delay1ms(200);
//		}
//		
//		for (int i = 0; i < 7; i++)
//		{
//			EduBase_LCD_Scroll_Display_Left();
//			SysTick_Delay1ms(200);
//		}
//	}
	
	while (1) 
		{
//			EduBase_LCD_Diplay_Heart();
//			SysTick_Delay1ms(500);
			if (prev_main_menu_counter != main_menu_counter) 
				{
					EduBase_LCD_Clear_Display();
					prev_main_menu_counter = main_menu_counter;
				}

			EduBase_LCD_Set_Cursor(0, 0);
			EduBase_LCD_Display_Integer(main_menu_counter);
			SysTick_Delay1ms(100);
		}
}

void PMOD_ENC_Task(void)
{
    state = PMOD_ENC_Get_State();

    if (PMOD_ENC_Button_Read(state) && !PMOD_ENC_Button_Read(last_state))
    {
        pmod_enc_btn_pressed = 1;
    }

    if (main_menu_counter < 0)
    {
        main_menu_counter = 0;
    }
    else if (main_menu_counter > MAX_COUNT)
    {
        main_menu_counter = MAX_COUNT;
    }
    else
    {
        main_menu_counter = main_menu_counter + PMOD_ENC_Get_Rotation(state, last_state);
    }

    last_state = state;
}

void Display_Main_Menu(int main_menu_state)
{
    switch(main_menu_state)
    {
        case 0x00:
        {
            EduBase_LCD_Set_Cursor(0, 0);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("TURN OFF LEDS");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("TURN ON LEDS");
            break;
        }

        case 0x01:
        {
            EduBase_LCD_Set_Cursor(0, 1);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("TURN OFF LEDS");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("TURN ON LEDS");
            break;
        }

        case 0x02:
        {
            EduBase_LCD_Set_Cursor(0, 0);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("TURN ON LEDS");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("FLASH LEDS");
            break;
        }

        case 0x03:
        {
            EduBase_LCD_Set_Cursor(0, 1);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("TURN ON LEDS");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("FLASH LEDS");
            break;
        }
				
				case 0x04:
        {
            EduBase_LCD_Set_Cursor(0, 1);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("FLASH LEDS");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("HEART SEQUENCE");
            break;
        }
				
				case 0x05:
        {
            EduBase_LCD_Set_Cursor(0, 1);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("FLASH LEDS");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("HEART SEQUENCE");
            break;
        }
				
				case 0x06:
        {
            EduBase_LCD_Set_Cursor(0, 1);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("HEART SEQUENCE");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("DISPLAY INFO");
            break;
        }
				
				case 0x07:
        {
            EduBase_LCD_Set_Cursor(0, 1);
            EduBase_LCD_Send_Data(0x03);
            EduBase_LCD_Set_Cursor(1, 0);
            EduBase_LCD_Display_String("HEART SEQUENCE");
            EduBase_LCD_Set_Cursor(1, 1);
            EduBase_LCD_Display_String("DISPLAY INFO");
            break;
        }
    }
}

void Process_Main_Menu_Selection(void) 
{
    if (pmod_enc_btn_pressed == 1) {
        pmod_enc_btn_pressed = 0;
        prev_main_menu_counter = 0xFF;

        switch (main_menu_counter) {
            case 0x00:
                EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
                break;

            case 0x01:
                EduBase_LEDs_Output(EDUBASE_LED_ALL_ON);
                break;

            case 0x02:
                EduBase_LEDs_Output(EDUBASE_LED_ALL_ON);
                break;

            case 0x03:
							for( int i =0; i <=5; i++)
								{
                EduBase_LEDs_Output(EDUBASE_LED_ALL_ON);
								SysTick_Delay1ms(500);
								EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
								SysTick_Delay1ms(500);
								}
                break;
						
						case 0x04:
								
                for( int i =0; i <=5; i++)
								{
                EduBase_LEDs_Output(EDUBASE_LED_ALL_ON);
								SysTick_Delay1ms(500);
								EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
								SysTick_Delay1ms(500);
								}
                break;
						
						case 0x05:
							EduBase_LCD_Enable_Display();
							EduBase_LCD_Clear_Display();
							EduBase_LCD_Set_Cursor(0, 0);
							EduBase_LCD_Diplay_Heart();
               for (int i = 0; i < 7; i++)
									{
									EduBase_LCD_Scroll_Display_Right();
									SysTick_Delay1ms(200);
									}
                break;
						
						case 0x06:
                EduBase_LCD_Enable_Display();
                EduBase_LCD_Clear_Display();
                EduBase_LCD_Set_Cursor(0, 0);
                EduBase_LCD_Display_String("DISPLAY");
                EduBase_LCD_Set_Cursor(0, 1);
                EduBase_LCD_Display_String("TEST");
                SysTick_Delay1ms(3000);
                EduBase_LCD_Clear_Display();
                break;
						
						case 0x07:
                EduBase_LCD_Enable_Display();
                EduBase_LCD_Clear_Display();
                EduBase_LCD_Set_Cursor(0, 0);
                EduBase_LCD_Display_String("DISPLAY TEXT");
                EduBase_LCD_Set_Cursor(0, 1);
                EduBase_LCD_Display_String("HELLO");
                SysTick_Delay1ms(3000);
                EduBase_LCD_Clear_Display();
                break;
        }
    }
}
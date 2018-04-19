#include "SSD1306.h"
#include "Font5x8.h"

int main(void)
{	
	GLCD_Setup();
	GLCD_SetFont(Font5x8, 5, 8, GLCD_OverWrite);

	GLCD_GotoXY(0, 0);
	GLCD_PrintString("Testing");
	GLCD_DrawLine(0, 8, 63, 31, GLCD_Black);
	GLCD_DrawLine(40, 0, 63, 31, GLCD_Black);
	GLCD_DrawCircle(63, 31, 10, GLCD_Black);
	GLCD_InvertRect(0, 0, 39, 7);
	GLCD_InvertScreen();

	GLCD_Render();

    while (1 == 1)
    {
		GLCD_ScrollLeft(0, 0x0F);
		_delay_ms(1000);
		GLCD_ScrollRight(0, 0x0F);
		_delay_ms(1000);
		GLCD_ScrollDiagonalLeft(0, 0x0F);
		_delay_ms(1000);
		GLCD_ScrollDiagonalRight(0, 0x0F);
		_delay_ms(1000);
		GLCD_ScrollStop();
		_delay_ms(1000);
	}

	return 0;
}

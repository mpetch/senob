#include "vga.h"

uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga_address = (uint16_t* const) 0xB8000;
const uint16_t defaultColor = (COLOR8_BLACK << 8) | (COLOR8_LIGHT_GREY << 12);
uint16_t currColor = defaultColor;

void reset()
{
    line = 0;
    column = 0;
    currColor = defaultColor;

    //loops threw all the line & columns and clears them with the for loop height & width
    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            vga_address[y * width + x] = ' ' | defaultColor;    //Every character has a character and a color
        }
        
    }
        
}

void newLine()
{
    if (line < height - 1)
    {
        line++;
        column = 0;
    }else
    {
        scrollUp();
        column = 0;
    }
    
}

void scrollUp()
{
    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            vga_address[(y-1) * width + x] = vga_address[y * width + x];
        }
    }
    for (uint16_t x = 0; x < width; x++)
    {
        vga_address[(height-1) * width + x] = ' ' | currColor;
    }
    
}

void print(const char* s)
{
    while (*s)
    {
        switch (*s)
        {
        case '\n':
            newLine();
            break;

        case '\r':
            column = 0;
            break;

        case '\t':
            if (column == width)
            {
                newLine();
            }
            uint16_t tablen = 4 - (column % 4);
            while (tablen != 0)
            {
                vga_address[line * width + (column++)] = ' ' | currColor;
                tablen--;
            }
            break;

        default:
            if (column == width)
            {
                newLine();
            }
            vga_address[line * width + (column++)] = *s | currColor;
            break;
        }
        s++;
    }
    
}

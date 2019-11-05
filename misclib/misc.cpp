#include <stdlib.h>
#include <uart.h>
#include <misc.h>


char htoa(uint8_t a)
{
	switch(a & 0xf) {
		case 0xa:
			return 'a';
		case 0xb:
			return 'b';
		case 0xc:
			return 'c';
		case 0xd:
			return 'd';
		case 0xe:
			return 'e';
		case 0xf:
			return 'f';
		default:
			return (a & 0xf) + 0x30;
	}
}

void printHex(uint8_t value)
{
	uint8_t h = value & 0xF0;
	h >>= 4;
	uint8_t l = value & 0x0F;
	uart_putchar(htoa(h));
	uart_putchar(htoa(l));
	uart_putchar(' ');
}

void printNumb(int16_t numb)
{
	char buf[6] = {0};
	int i = 0;
	itoa(numb, buf, 10);
	while(buf[i] != 0) {
		uart_putchar(buf[i]);
		i++;
	}
	uart_putchar(' ');
}

void msg(const char * str)
{
	while(*(str)) {
		uart_putchar(*(str++));
	}
}

// 0
// some var
// _end
// free ram
// __stack (grow to _end)

extern uint8_t _end;
extern uint8_t __stack;

uint8_t ramUsage()
{
	uint16_t a;
	a =	(100*((uint16_t)&__stack-(uint16_t)&a))/((uint16_t)&__stack-(uint16_t)&_end);
	return a;
}


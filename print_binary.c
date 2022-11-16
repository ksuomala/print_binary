/*

Prints any variable type in binary to the standard output.
First argument is the size of the next argument variable in bits.
If the argument is a string, set size_in_bits to 0.

*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

static void print_byte(uint8_t byte)
{
	printf("%c", (byte & 0x80 ? '1' : '0'));
	printf("%c", (byte & 0x40 ? '1' : '0'));
	printf("%c", (byte & 0x20 ? '1' : '0'));
	printf("%c ", (byte & 0x10 ? '1' : '0'));
	printf("%c", (byte & 0x08 ? '1' : '0'));
	printf("%c", (byte & 0x04 ? '1' : '0'));
	printf("%c", (byte & 0x02 ? '1' : '0'));
	printf("%c ", (byte & 0x01 ? '1' : '0'));
}

static void print_str(va_list ap)
{
	char *str;
	int i;

	i = -1;
	str = va_arg(ap, char *);
	while (str[++i])
		print_byte((uint8_t)str[i]);
}

void	print_char(va_list ap)
{
	uint8_t	chr;

	chr = (uint8_t)va_arg(ap, int);
	print_byte((uint8_t)chr);
}

void	print_int(va_list ap)
{
	uint32_t i;

	i = (uint32_t)va_arg(ap, int);
	print_byte(i >> 24 & 0xFF);
	print_byte(i >> 16 & 0xFF);
	print_byte(i >> 8 & 0xFF);
	print_byte(i & 0xFF);
	printf("\n");

}

void	print_ul(va_list ap)
{
		uint64_t ul;

		ul = (uint64_t)va_arg(ap, uint64_t);

		print_byte(ul >> 56 & 0xFF);
		print_byte(ul >> 48 & 0xFF);
		print_byte(ul >> 40 & 0xFF);
		print_byte(ul >> 32 & 0xFF);
		print_byte(ul >> 24 & 0xFF);
		print_byte(ul >> 16 & 0xFF);
		print_byte(ul >> 8 & 0xFF);
		print_byte(ul & 0xFF);
}

void	print_short(va_list ap)
{
	uint16_t shrt;

	shrt = (uint16_t)va_arg(ap, int);
	print_byte(shrt >> 8 & 0xFF);
	print_byte(shrt & 0xFF);
}

void	print_binary(int size_in_bits, ...)
{
	va_list		ap;

	va_start(ap, size_in_bits);
	if (!size_in_bits)
		print_str(ap);
	else if (size_in_bits == 8)
		print_char(ap);
	else if (size_in_bits == 16)
		print_short(ap);
	else if (size_in_bits == 32)
		print_int(ap);
	else if (size_in_bits == 64)
		print_ul(ap);
	else
	{
		printf("size_in_bits must be 0 (if it's a string), a multiple of 8 and <= 64");
		return ;
	}
	va_end(ap);
	return ;
}
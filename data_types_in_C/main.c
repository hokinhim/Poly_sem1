#include <stdio.h>
#include <time.h>
#include <math.h>

int numbers_int() {
	int i = 1, i_old = 0;
	while (i > i_old) {
		i_old = i;
		i *= 2;
	}
	return i_old;
}

short int numbers_short() {
	short int i = 1, i_old = 0;
	while (i > i_old) {
		i_old = i;
		i *= 2;
	}
	return i_old;
}

unsigned short int numbers_unsigned_short() {
	unsigned short int i = 1, i_old = 0;
	while (i > i_old) {
		i_old = i;
		i *= 2;
	}
	return i_old;
}

unsigned int numbers_unsigned_int() {
	unsigned int i = 1, i_old = 0;
	while (i > i_old) {
		i_old = i;
		i *= 2;
	}
	return i_old;
}

unsigned long long numbers_unsigned_long_long() {
	unsigned long long i = 1, i_old = 0;
	while (i > i_old) {
		i_old = i;
		i *= 2;
	}
	return i_old;
}

int numbers_float() {
	float i = 1, i_old = 0;
	while (i > i_old) {
		i_old = i;
		i *= 2;
	}
	return i_old;
}

int numbers_double() {
	double i = 1, i_old = 0;
	while (i > i_old) {
		i_old = i;
		i *= 2;
	}
	return i_old;
}

int main() {
	clock_t t = clock();

	int byte_int = (log2(numbers_int()) + 1 + 1) / 8;
	int MAX_INT = numbers_int() * 2 - 1;
	int MIN_INT = -2 * numbers_int();
	printf("int: byte = %d, MAX_INT = %d, MIN_INT = %d\n", byte_int, MAX_INT, MIN_INT);

	short byte_short = (log2(numbers_short()) + 1 + 1) / 8;
	short MAX_SHORT = numbers_short() * 2 - 1;
	short MIN_SHORT = -2 * numbers_short();
	printf("short int: byte = %d, MAX_INT = %d, MIN_INT = %d\n", byte_short, MAX_SHORT, MIN_SHORT);

	unsigned short byte_unsigned_short = (log2(numbers_unsigned_short()) + 1) / 8;
	unsigned short MAX_USHORT = numbers_unsigned_short() * 2 - 1;
	unsigned short MIN_USHORT = numbers_unsigned_short() * 2;
	printf("unsigned short int: byte = %u, MAX_UINT = %u, MIN_UINT = %u\n", byte_unsigned_short, MAX_USHORT, MIN_USHORT);

	unsigned int byte_unsigned_int = (log2(numbers_unsigned_int()) + 1)/8;
	unsigned int MAX_UINT = numbers_unsigned_int() * 2 - 1;
	unsigned int MIN_UINT = numbers_unsigned_int() * 2;
	printf("unsigned int: byte = %u, MAX_UINT = %u, MIN_UINT = %u\n", byte_unsigned_int, MAX_UINT, MIN_UINT);

	unsigned long long byte_unsigned_long_long = log2(((numbers_unsigned_long_long() - 1) * 2 + 1)) / 8;
	unsigned long long MAX_ULONG = (numbers_unsigned_long_long() - 1) * 2 + 1;
	unsigned long long MIN_ULONG = numbers_unsigned_long_long() * 2;
	printf("unsigned long long int: byte = %llu, MAX_LONG_INT = %llu, MIN_LONG_INT = %llu\n", byte_unsigned_long_long, MAX_ULONG, MIN_ULONG);

	char sym = 1, sym_old = 0;
	int count_char = 1;
	while (sym > sym_old) {
		sym_old = sym;
		sym += 1;
		count_char += 1;
	}
	int byte_char = log2((count_char) * 2)/8;
	printf("char: byte = %d, MAX_CHAR = %d, MIN_CHAR = %d\n", byte_char, sym_old, sym);

	unsigned char unsigned_sym = 1, unsigned_sym_old = 0;
	int count_unsigned_char = 1;
	while (unsigned_sym > unsigned_sym_old) {
		unsigned_sym_old = unsigned_sym;
		unsigned_sym += 1;
		count_unsigned_char += 1;
	}
	int byte_unsigned_char = log2((count_unsigned_char) * 2) / 8;
	printf("unsigned char: byte = %d, MAX_UCHAR = %d, MIN_UCHAR = %d\n", byte_unsigned_char, unsigned_sym_old, unsigned_sym);

	int byte_float = (log2((numbers_float() - 1) / 2 + 1) + 1 + 1) / 8;
	printf("float: byte = %d\n", byte_float);

	int byte_double = ((log2((numbers_double() - 1) / 2 + 1) + 1 + 1) * 2) / 8;
	printf("double: byte = %d\n", byte_double);

	double time = ((double)t) / CLOCKS_PER_SEC;
	printf("The program took %f seconds to execute \n", time);

	return 0;
}
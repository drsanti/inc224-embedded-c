#include "ternion.h"

int main(void)
{
	// Initialize the system.
	ternion_init(0);

	// Declare variables.
	uint8_t x;
	int16_t y;

	// Print information to UART1.
	uart_printf(UART_NUM_1, "x variable:\r\n");
	uart_printf(UART_NUM_1, "\t\tvalue: %u, address: 0x%04X, size: %d\r\n", x, &x, sizeof(x));

	uart_printf(UART_NUM_1, "y variable:\r\n");
	uart_printf(UART_NUM_1, "\t\tvalue: %u, address: 0x%04X, size: %d\r\n", y, &y, sizeof(y));

	// Start the system.
	ternion_start(0);
}

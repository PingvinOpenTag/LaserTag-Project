/*
 * Convert real code to IR sequence
 *
 * Package:
 *  1 1 1 0 -- HEADER
 *  1 0     -- Logick "0"
 *  1 0 0   -- Logick "1"
 *
 *  Example:
 *   code == 0x05 -- 0b0101
 *  ircode:
 *   |header | 0 | 1  | 0 | 1  | stop|
 *   |  1110 | 10| 100| 10| 100| 1   | == 11101010 01010010 == 0xEA 0x52
 */

int code2ir_shot(uint8_t *code, uint8_t *result, int size_of_bites);

/*
 * Convert IR sequence to real code
 *
 * Package:
 *  1 1 1 0 -- HEADER
 *  1 0     -- Logick "0"
 *  1 0 0   -- Logick "1"
 *
 *  Example:
 *   code == 0xEA 0x50 == 11101010 01010000
 *  ircode
 *   |  1110 | 10| 100| 10| 100| stop|
 *   |header | 0 | 1  | 0 | 1  |     | == 0x05
 */

int ir_shot2code(uint8_t *ircode, uint8_t *code);


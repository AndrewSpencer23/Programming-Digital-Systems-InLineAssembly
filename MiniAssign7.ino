void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  uint8_t resultLDI = 0;
  uint8_t resultLDI2 = 0;

  asm volatile(
    "ldi r16, 0x55 \n\t"           // Load 0x55 into r16
    "mov %[output], r16 \n\t"     // Move the value of r16 into output1
    "mov r17, r16 \n\t"           // Move the value of r16 into r17
    "mov %[output2], r17 \n\t"    // Move r17 into output2
    : [output] "=r" (resultLDI), [output2] "=r" (resultLDI2)
    :
    : "r16", "r17"
  );

  Serial.print("\nProgram 1: LDI Result (HEX)\n");
  Serial.println(resultLDI, HEX);
  Serial.print("\nProgram 2: LDI MOV Result (HEX)\n");
  Serial.println(resultLDI2, HEX);

  uint8_t valLow = 0x12;
  uint8_t valHigh = 0x34;

  asm volatile(
    "ldi r24, 0x12 \n\t"           // Load 0x12 into r24
    "ldi r25, 0x34 \n\t"           // Load 0x34 into r25
    "mov r26, r24 \n\t"            // Move r24 into r26
    "mov r27, r25 \n\t"            // Move r25 into r27
    "mov %[low], r26 \n\t"         // Move r26 into the low
    "mov %[high], r27 \n\t"        // Move r27 into the high
    : [low] "=r" (valLow), [high] "=r" (valHigh) // Output operands
    :
    : "r24", "r25", "r26", "r27"  // Clobbered registers
  );

  Serial.print("\nProgram 3: The results for r26:r27 (HEX) \n");
  Serial.println(valLow, HEX);
  Serial.println(valHigh, HEX);

  // Create an array with values 0x20 and 0x40
  uint8_t data[] = {0x20, 0x40};

  uint8_t* ptr = &data[0]; // Get the first value of the array

  uint8_t result; // Create a result variable

  // Load value from pointer into r16 using LD and X register (R27:R26)
  asm volatile (
    "mov r26, %A1\n\t"            // Move low byte of address into r26
    "mov r27, %B1\n\t"            // Move high byte into r27
    "ld r16, X\n\t"               // Load value pointed to by X into r16
    "mov %0, r16\n\t"             // Move r16 into result
    : "=r" (result)               // Output
    : "r" (ptr)                   // Input
    : "r16", "r26", "r27"         // Clobbers
  );

  // Print result
  Serial.print("\nProgram 4: Value in r16: ");
  Serial.println(result, HEX); // Print in hex to match 0x20

  uint8_t result1, result2;

  asm volatile (
    "mov r26, %A2\n\t"            // Load low byte of pointer into r26
    "mov r27, %B2\n\t"            // Load high byte into r27
    "ld r16, X+\n\t"              // Load value at X into r16, then increment X
    "ld r17, X\n\t"               // Load next value into r17
    "mov %0, r16\n\t"             // Move r16 into result1
    "mov %1, r17\n\t"             // Move r17 into result2
    : "=r" (result1), "=r" (result2)    // Outputs
    : "r" (ptr)                         // Input
    : "r16", "r17", "r26", "r27"       // Clobbers
  );

  // Print the results
  Serial.print("\nProgram 5: Value in r16: ");
  Serial.println(result1, HEX);

  Serial.print("\nValue in r17: ");
  Serial.println(result2, HEX);
}

void loop() {
  // put your main code here, to run repeatedly:

}

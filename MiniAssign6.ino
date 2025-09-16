uint8_t a = 0b11001100;
uint8_t b = 0b10101010;
uint8_t result = 0;
uint16_t result2 = 0;
int16_t result3;
int8_t a1 = -10;
int8_t b1 = 20;

void setup() {
  Serial.begin(9600);

  asm volatile (
    "mov r16, %[valA] \n\t"   // r16 = a
    "mov r17, %[valB] \n\t"   // r17 = b
    "and r16, r17 \n\t"       // r16 = r16 & r17
    "mov %[res], r16 \n\t"    // result = r16
    : [res] "=r" (result)     // output
    : [valA] "r" (a), [valB] "r" (b) // inputs
    : "r16", "r17"            // clobbered
  );

  Serial.print("\nProgram 1: AND\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  } // Got from ChatGpt to display the binary number

  Serial.print(" | Decimal: ");
  Serial.println(result);

  a = 0b11001100;
  asm volatile (
    "mov r16, %[valA] \n\t"
    "andi r16, 0xF0       \n\t"   // ANDI with 0xF0
    "mov %[res], r16      \n\t"   // Move result into 'result'
    : [res] "=r" (result)         // Output operand
    : [valA] "r" (a)              // Input operand
    : "r16"                       // Clobbered register
  );

  Serial.print("\nProgram 2: ANDI\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }

  Serial.print(" | Decimal: ");
  Serial.println(result);

  a = 0b11001100;
  asm volatile (
    "mov r16, %[valA] \n\t"
    "ori r16, 0xF0       \n\t"   // ANDI with 0xF0
    "mov %[res], r16      \n\t"   // Move result into 'result'
    : [res] "=r" (result)         // Output operand
    : [valA] "r" (a)              // Input operand
    : "r16"                       // Clobbered register
  );

  Serial.print("\nProgram 3: ORI\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }

  Serial.print(" | Decimal: ");
  Serial.println(result);

  a = 0b11001100;
  b = 0b10101010;
  asm volatile (
    "mov r16, %[valA] \n\t"
    "mov r17, %[valB] \n\t"
    "or r16, r17 \n\t"
    "mov %[res], r16 \n\t"
    : [res] "=r" (result)                  // Output operand
    : [valA] "r" (a), [valB] "r" (b)       // Input operand
    : "r16", "r17"                         // Clobbered register
  );

  Serial.print("\nProgram 4: OR\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }

  Serial.print(" | Decimal: ");
  Serial.println(result);

  a = 0b11001100;
  b = 0b10101010;
  asm volatile (
    "mov r16, %[valA] \n\t"
    "mov r17, %[valB] \n\t"
    "eor r16, r17 \n\t"
    "mov %[res], r16 \n\t"
    : [res] "=r" (result)                  // Output operand
    : [valA] "r" (a), [valB] "r" (b)       // Input operand
    : "r16", "r17"                         // Clobbered register
  );

  Serial.print("\nProgram 5: XOR\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }

  Serial.print(" | Decimal: ");
  Serial.println(result);

  a = 0b11001100;
  asm volatile(
    "mov r16, %[valA] \n\t"                // Move the value of A into r16
    "com r16 \n\t"                         // Take the 1s comp
    "mov %[res], r16 \n\t"                 // Move the result value into r16
    : [res] "=r" (result)                  // Output operand
    : [valA] "r" (a)                       // Input operand
    : "r16"                                // Clobbered register
  );

  Serial.print("\nProgram 6: Ones Complement\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }

  Serial.print(" | Decimal: ");
  Serial.println(result);

  asm volatile (
    "mov r16, %[valA] \n\t"   // Copy 'a' into r16
    "com r16         \n\t"    // One's complement: r16 = ~r16
    "inc r16         \n\t"    // Increment r16 by 1 → Two's complement
    "mov %[res], r16 \n\t"    // Move result into 'result'
    : [res] "=r" (result)     // Output
    : [valA] "r" (a)          // Input
    : "r16"                   // Clobbered
  );

  Serial.print("\nProgram 7: Two's Complement (using INC)\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }

  Serial.print(" | Decimal: ");
  Serial.println(result);

  a = 0b00001100;

  asm volatile (
    "mov r16, %[valA]     \n\t"  // Move the value of A

    // SBR sets bits specified in the immediate value (bitmask)
    // 0b00110000 = 0x30 (bit 5 and 4 are 1)
    "sbr r16, 0x30       \n\t"

    // Step 3: Move result from r16 back into result variable
    "mov %[res], r16     \n\t"

    : [res] "=r" (result)         // Output operand
    : [valA] "r" (a)           // Input operand
    : "r16"                       // Clobbered register
  );

  Serial.print("\nProgram 8: SBR\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }
  Serial.print("\n");


  a = 0b11111111;

  asm volatile (
    "mov r16, %[valA]     \n\t"    // Copy value into r16
    "cbr r16, 0x0F       \n\t"    // Clear bits 0 to 3 (0b00001111)
    "mov %[res], r16     \n\t"    // Move result back to variable
    : [res] "=r" (result)
    : [valA] "r" (a)
    : "r16"
  );

  Serial.print("\nProgram 9: CBR\nResult (binary): ");
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(result, i));
  }
  Serial.print("\n");

  a = 10;
  b = 20;

  asm volatile (
    "mov r16, %[valA]    \n\t"   // Load a into r16
    "mov r17, %[valB]    \n\t"   // Load b into r17
    "mul r16, r17        \n\t"   // r0:r1 = r16 * r17
    "movw %A[result], r0 \n\t"   // Store r0 (low) and r1 (high) into result
    : [result] "=r" (result2)
    : [valA] "r" (a), [valB] "r" (b)
    : "r0", "r1", "r16", "r17"
  );

  Serial.print("\nProgram 10: Unsigned MUL\nResult: ");
  Serial.println(result2);

  delay(1000);

  asm volatile (
    "mov r16, %[a]     \n\t"
    "mov r17, %[b]     \n\t"
    "muls r16, r17     \n\t"
    "mov %A[result], r0 \n\t"
    "mov %B[result], r1 \n\t"
    : [result] "=r" (result3)
    : [a] "r" ((int8_t)a1), [b] "r" ((int8_t)b1)
    : "r0", "r1", "r16", "r17"
  );

  Serial.print("\nProgram 11: Signed MULS\nResult: ");
  Serial.println(result3);
}

void loop() {
  // nothing here
}


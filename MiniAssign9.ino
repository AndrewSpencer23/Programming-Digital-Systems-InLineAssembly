void setup() {
  Serial.begin(9600);

  uint8_t resultASRPOS = 0b00101011;   // Initial positive value for ASR
  int8_t  resultASRNEG = 0b11010101;   // Initial negative value for ASR
  uint8_t resultLSL = 0b01010101;   // Variable for LSL result
  uint8_t carry = 0;            // Variable to hold carry flag

  // ---------- Program 1: ASR ----------
  asm volatile(
    "mov  r16, %[input1]    \n\t"   // Copy input1 into r16
    "mov  r17, %[input2]    \n\t"   // Copy input2 into r17
    "asr  r16               \n\t"   // Arithmetic shift right on input1
    "asr  r17               \n\t"   // Arithmetic shift right on input2
    "mov  %[output1], r16   \n\t"   // Store result from r16 into output1
    "mov  %[output2], r17   \n\t"   // Store result from r17 into output2
    : [output1] "=r" (resultASRPOS), [output2] "=r" (resultASRNEG)   // Outputs
    : [input1]  "r" (resultASRPOS), [input2]  "r" (resultASRNEG)    // Inputs
    : "r16", "r17"
  );

  Serial.print("\nProgram 1: ASR");
  Serial.print("\nResult 1 (decimal): ");
  Serial.println(resultASRPOS, DEC);
  Serial.print("Result 1 (binary):  ");
  printByteAsBinary(resultASRPOS);
  Serial.println();

  Serial.print("\nResult 2 (decimal): ");
  Serial.println(resultASRNEG, DEC);
  Serial.print("Result 2 (binary):  ");
  printByteAsBinary(resultASRNEG);
  Serial.println();

  // ---------- Program 2: LSL ----------
  asm volatile(
    "mov  r16, %[input]     \n\t"   // Copy resultLSL into r16
    "lsl  r16               \n\t"   // Logical shift left on r16
    "mov  %[output], r16    \n\t"   // Store result back into resultLSL
    : [output] "=r" (resultLSL)     // Outputs
    : [input]  "r" (resultLSL)      // Inputs
    : "r16"                         // Clobbered register
  );

  Serial.print("\nProgram 2: LSL");
  Serial.print("\nResult LSL (decimal): ");
  Serial.println(resultLSL, DEC);
  Serial.print("Result LSL (binary):  ");
  printByteAsBinary(resultLSL);
  Serial.println();

  // ---------- Program 3: LSR ----------
  asm volatile(
    "mov  r16, %[resultLSR] \n\t"   // Copy input into r16
    "lsr  r16               \n\t"   // Logical shift right
    "mov  %[outputLSR], r16 \n\t"   // Store result
    "in   r17, __SREG__     \n\t"   // Copy SREG into r17
    "andi r17, 0x01         \n\t"   // Mask out carry flag (bit 0)
    "mov  %[carry], r17     \n\t"   // Store carry into variable
    : [outputLSR] "=r" (resultLSL), [carry] "=r" (carry)   // Outputs
    : [resultLSR] "r" (resultLSL)                         // Inputs
    : "r16", "r17"
  );

  Serial.print("\nProgram 3: LSR");

  Serial.print("\nResult LSR (decimal): ");
  Serial.println(resultLSL, DEC);
  Serial.print("Result LSR (binary):  ");
  printByteAsBinary(resultLSL);
  Serial.println();
  Serial.print("Carry bit: ");
  Serial.println(carry, DEC);

  // ---------- Program 4: ROL ----------
  uint8_t inputROL  = 0b01010101;   // Initial value (85 decimal)
  uint8_t resultROL = 0;            // Variable for ROL result

  asm volatile(
    "mov r16, %[input]      \n\t"   // Copy input into r16
    "sec                    \n\t"   // Set carry flag (C = 1)
    "rol r16                \n\t"   // Rotate left through carry
    "mov %[output], r16     \n\t"   // Store result
    "in r17, __SREG__       \n\t"   // Copy SREG into r17
    "andi r17, 0x01         \n\t"   // Mask out carry flag
    "mov %[carry], r17      \n\t"   // Store carry
    : [output] "=r" (resultROL), [carry] "=r" (carry)   // Outputs
    : [input] "r" (inputROL)                               // Inputs
    : "r16", "r17"
  );

  Serial.print("\nProgram 4: ROL (85 with Carry=1)");
  Serial.print("\nBefore (decimal): 85");
  Serial.print("\nBefore (binary):  ");
  printByteAsBinary(inputROL);
  Serial.print("\nAfter  (decimal): ");
  Serial.println(resultROL, DEC);
  Serial.print("After  (binary):   ");
  printByteAsBinary(resultROL);
  Serial.print("\nUpdated Carry: ");
  Serial.println(carry, DEC);

  // ---------- Program 5: ROR ----------
  asm volatile(
    "mov  r16, %[input]     \n\t"   // Copy input into r16
    "sec                    \n\t"   // Set carry flag (C = 1)
    "ror  r16               \n\t"   // Rotate right through carry
    "mov  %[output], r16    \n\t"   // Store result
    "in   r17, __SREG__     \n\t"   // Copy SREG into r17
    "andi r17, 0x01         \n\t"   // Mask out carry flag
    "mov  %[carry], r17     \n\t"   // Store carry
    : [output] "=r" (resultROL), [carry] "=r" (carry)   // Outputs
    : [input]  "r" (inputROL)                             // Inputs
    : "r16", "r17"
  );

  Serial.print("\nProgram 5: ROR (85 with Carry=1)");
  Serial.print("\nBefore (decimal): 85");
  Serial.print("\nBefore (binary):  ");
  printByteAsBinary(inputROL);
  Serial.print("\nAfter  (decimal): ");
  Serial.println(resultROL, DEC);
  Serial.print("After  (binary):   ");
  printByteAsBinary(resultROL);
  Serial.print("\nUpdated Carry: ");
  Serial.println(carry, DEC);
  Serial.println();
}

void printByteAsBinary(uint8_t val) {
  for (int i = 7; i >= 0; i--) {
    Serial.print((val >> i) & 1);
  }
}

void loop() {
  // Empty loop (not used)
}

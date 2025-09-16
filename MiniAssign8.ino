void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  uint8_t resultMOV = 0;

  asm volatile(
    "LDI r20, 0x7F \n\t" // Load Immediate (0x7F into r20)
    "mov r21, r20 \n\t" // Move contents of r20 into r21
    "mov %[output], r21 \n\t" // Move the contents of r21 into the output
    : [output] "=r" (resultMOV) // Output constraint
    :
    : "r20", "r21" // Clobbers
  );

  Serial.print("\nProgram 1: LDI result after mov command (HEX)\n");
  Serial.println(resultMOV, HEX);

  uint16_t output1 = 0;

  asm volatile (
    "ldi r18, 0x9A       \n\t"   // put 0x9A into r18
    "sts 0x0100, r18     \n\t"   // store r18 into SRAM at 0x0100
    "ldi r26, lo8(0x0100)\n\t"   // load low byte of 0x0100 into R26
    "ldi r27, hi8(0x0100)\n\t"   // load high byte of 0x0100 into R27
    "ld  r16, X+         \n\t"   // load [X] into R16, increment X
    "mov %[output1], r16         \n\t"   // move R16 into C variable
    : [output1] "=r" (output1)              // Single output constraint
    :                            // No inputs
    : "r16", "r18", "r26", "r27" // clobbered registers
  );

  Serial.print("\nProgram 2: LDX+:\nR16 = 0x");
  Serial.println(output1, HEX);   // should print 9A

  uint8_t value;
  uint8_t data[] = {0x11, 0x22, 0x33, 0x44};

  asm volatile(
    "ldd r17, Z+2        \n\t"   // load with offset 2 → data[2] = 0x33
    "mov %[value], r17   \n\t"   // copy into C variable
    : [value] "=r" (value)        // output constraint
    : "z" (data)                  // input: base address goes into Z (r30:r31)
    : "r17"                       // clobbered
  );

  Serial.print("\nProgram 3: LD with offset:\nR17 = 0x");
  Serial.println(value, HEX);   // should print 33

  uint8_t arr[4] = {0};   // 4-byte memory array initialized to 0
  
  asm volatile(
    "ldi r18, 0xFF          \n\t"   // r18 = 0xFF
    "st -X, r18             \n\t"   // store 0xFF at --X (arr[3])
    "ldi r18, 0xEE          \n\t"   // r18 = 0xEE
    "st -X, r18             \n\t"   // store 0xEE at --X (arr[2])
    :
    : "x" (&arr[4])                   // input: address just past last element
    : "r18"                           // clobbers
  );

  // Verify results
  Serial.print("\nProgram 4: St X\narr[0] = 0x"); Serial.println(arr[0], HEX);
  Serial.print("arr[1] = 0x"); Serial.println(arr[1], HEX);
  Serial.print("arr[2] = 0x"); Serial.println(arr[2], HEX);
  Serial.print("arr[3] = 0x"); Serial.println(arr[3], HEX);
}

void loop() {
  // put your main code here, to run repeatedly:

}

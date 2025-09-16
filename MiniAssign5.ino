uint8_t a = 15; // First number
uint8_t b = 25; // Second number
uint8_t c = 40; // Third number
uint16_t wordValue = 1000; // 16-bit variable for word operations
uint16_t wordResult; // Variable to store the result for the 16 bit arithmetic
uint8_t result; // To store the result of operations
uint8_t result1; // Temporary result value
uint8_t carryFlag; // To store the carry flag

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Initialize the serial monitor

  asm volatile (
    "mov r16, %[valA] \n\t"   // Move a into r16
    "mov r17, %[valB] \n\t"   // Move b into r17
    "add r16, r17 \n\t"       // r16 = a + b
    "mov r18, %[valC] \n\t"   // Move c into r18
    "sub r16, r18 \n\t"       // r16 = (a + b) - c
    "mov %[sum], r16"         // Store result in 'result'
    :[sum] "=r" (result)     // Output
    :[valA] "r" (a), [valB] "r" (b), [valC] "r" (c) // Inputs
    :"r16", "r17", "r18"     // Clobbers
  );
  delay(1000);
  Serial.print("\nAddition and Subtraction");
  Serial.print("\nThe value of 'a' is: ");
  Serial.println(a);
  Serial.print("The value of 'b' is: ");
  Serial.println(b);
  Serial.print("The value of 'c' is: ");
  Serial.println(c);
  Serial.print("The final result is: ");
  Serial.println(result);

  asm volatile(
    "mov r16, %[valA] \n\t"   // Move a into r16
    "mov r17, %[valB] \n\t"   // Move b into r17
    "sec \n\t" // Setting the carry bit to high
    "adc r16, r17 \n\t" // Adding r16 and r17 with a carry bit
    "mov %[resultVal], r16 \n\t" // Moving the result register into r16
    "in r18, __SREG__ \n\t" // Move the status reguster into r18
    "andi r18, 0x01 \n\t" // Perform an immediate and with r18 and the hex number 0x01
    "mov %[carry], r18" // Move the carry bit into r18
    :[resultVal] "=r" (result), [carry] "=r" (carryFlag) // Output Constraints
    :[valA] "r" (a), [valB] "r" (b) // Input Constraints
    :"r16", "r17", "r18"     // Clobbers
  );
  delay(1000);
  Serial.print("\nAddition with carry");
  Serial.print("\nThe value of 'a' is: ");
  Serial.println(a);
  Serial.print("The value of 'b' is: ");
  Serial.println(b);
  Serial.print("The value of add with carry is: ");
  Serial.println(result);
  Serial.print("The carry flag is: ");
  Serial.println(carryFlag);

  asm volatile (
    "mov r16, %[valC] \n\t" // Move the value of c into r16
    "subi r16, 10 \n\t" // Immediate subtract 10 from r16
    "mov %[result1], r16 \n\t" // Move the intermediate result into r16
    "mov %[valB], r17 \n\t" // Move the value of B into r17
    "sec \n\t" // Setting the carry bit to high
    "sbc r16, r17 \n\t" // Adding r16 and r17 with a carry bit
    "mov %[resultVal], r16 \n\t" // Moving the result register into r16
    "in r18, __SREG__ \n\t" // Move the status reguster into r18
    "andi r18, 0x01 \n\t" // Perform an immediate and with r18 and the hex number 0x01
    "mov %[carry], r18" // Move the carry bit into r18
    :[result1] "=r" (result1), [resultVal] "=r" (result), [carry] "=r" (carryFlag) // Output Constraints
    :[valC] "r" (c), [valB] "r" (b) // Input Constraints
    :"r16", "r17", "r18"     // Clobbers
  );
  delay(1000);
  Serial.print("\nSub with carry after SUBI");
  Serial.print("\nThe value of 'c' is: ");
  Serial.println(c);
  Serial.print("The value of 'b' is: ");
  Serial.println(b);
  Serial.print("The value of 'result1' is: ");
  Serial.println(result1);
  Serial.print("The value of sub with carry is: ");
  Serial.println(result);
  Serial.print("The carry flag is: ");
  Serial.println(carryFlag);

  asm volatile (
    "mov r26, %A[val] \n\t"
    "mov r27, %B[val] \n\t"
    "adiw r26, 53 \n\t"
    "movw %A[res], r26"
    :[res] "=r" (wordResult)
    :[val] "r" (wordValue)
    :"r26", "r27"
  );
  delay(1000);
  Serial.print("\naddiw operand");
  Serial.print("\nThe value of 'wordValue' is: ");
  Serial.println(wordValue);
  Serial.print("The value of 'wordResult' is: ");
  Serial.println(wordResult);

  asm volatile (
    "mov r26, %A[val] \n\t"
    "mov r27, %B[val] \n\t"
    "sbiw r26, 24 \n\t"
    "movw %A[res], r26"
    :[res] "=r" (wordResult)
    :[val] "r" (wordValue)
    :"r26", "r27"
  );
  delay(1000);
  Serial.print("\nsbiw operand");
  Serial.print("\nThe value of 'wordValue' is: ");
  Serial.println(wordValue);
  Serial.print("The value of 'wordResult' is: ");
  Serial.println(wordResult);
}

void loop() {
  // put your main code here, to run repeatedly:

}

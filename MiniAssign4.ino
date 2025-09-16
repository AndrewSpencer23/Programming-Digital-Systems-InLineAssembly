void setup() {
  // Set pin 13 as an output using in-line assembly
  asm volatile(
    "sbi %[ddr], %[bit] \n" // Set bit 0 in DDRB to configure PB0 as an output
    :
    : [ddr] "I" (0x04), // DDRB Register
      [bit] "I" (0)
  );

  asm volatile(
    "sbi %[ddr], %[bit] \n" // Set bit 7 in DDRD to configure PD7 as an output
    :
    : [ddr] "I" (0x0A), // DDRD Register
      [bit] "I" (7)
  );

  asm volatile(
    "sbi %[ddr], %[bit] \n" // Set bit 4 in DDRD to configure PD4 as an output
    :
    : [ddr] "I" (0x0A), // DDRD Register
      [bit] "I" (4)
  );
}

void loop() {
  asm volatile(
    "sbi %[port], %[bit] \n"
    :
    : [port] "I" (0x05),
      [bit] "I" (0)
  );

  delay(1000);

  asm volatile(
    "cbi %[port], %[bit] \n" // Fixed: /n → \n
    :
    : [port] "I" (0x05),
      [bit] "I" (0)
  );

  asm volatile(
    "sbi %[port], %[bit] \n" // Fixed: /n → \n
    :
    : [port] "I" (0x0B),
      [bit] "I" (7)
  );

  delay(1000);

  asm volatile(
    "cbi %[port], %[bit] \n" // Fixed: /n → \n
    :
    : [port] "I" (0x0B),
      [bit] "I" (7)
  );

  delay(1000);

  asm volatile(
    "sbi %[port], %[bit] \n" // Fixed: /n → \n
    :
    : [port] "I" (0x0B),
      [bit] "I" (4)
  );

  delay(1000);

  asm volatile(
    "cbi %[port], %[bit] \n" // Fixed: /n → \n
    :
    : [port] "I" (0x0B),
      [bit] "I" (4)
  );
}

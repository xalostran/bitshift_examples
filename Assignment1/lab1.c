#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_BUILTIN 5

volatile uint8_t *ddrb = (volatile uint8_t *)0x24;
volatile uint8_t *portb = (volatile uint8_t *)0x25;

unsigned long previousMillis1 = 0; // led 1
unsigned long previousMillis2 = 0; // led 2
unsigned long previousMillis3 = 0; // led 3
unsigned long interval = 1000;     // interval for all LEDs = 1000 ms
unsigned long blinkDuration = 100; // Blink duration (half the interval)

void setup()
{
    // Set LED pins as outputs
    *ddrb |= (1 << LED_PIN_1);
    *ddrb |= (1 << LED_PIN_2);
    *ddrb |= (1 << LED_PIN_3);
    *ddrb |= (1 << LED_PIN_BUILTIN); // Built-in LED
}

void loop()
{
    unsigned long currentMillis = millis(); // save current time
    int nextPin = millis() * (interval % millis());

    // if(nextPin > 9000)
    // millis() == 0;

    // LED 1
    if (currentMillis % previousMillis1 >= interval)
    {
        previousMillis1 = currentMillis; // save last blink
        *portb |= (1 << LED_PIN_1);      // Toggle LED 1 pin
        delay(1000);
        *portb &= ~(1 << LED_PIN_1);
        *portb |= (nextPin);
    }

    // LED 2
    if (currentMillis % previousMillis2 >= interval)
    {
        previousMillis2 = currentMillis;
        *portb |= (1 << LED_PIN_2); // Toggle LED 2 pin
        delay(1000);
        *portb &= ~(1 << LED_PIN_2);
        *portb |= (nextPin);
        /*interval = (interval << 1) % 9000;
        if (interval == 0)
          interval <= 1000; */
    }

    // LED 3
    if (currentMillis % previousMillis3 >= interval)
    {
        previousMillis3 = currentMillis;
        *portb |= (1 << LED_PIN_3); // Toggle LED 3 pin
        delay(1000);
        *portb &= ~(1 << LED_PIN_3);
        *portb |= (nextPin);

        /*interval = (interval << 1) % 9000;
        if (interval == 0)
          interval <= 1000; */
    }

    // Built-in LED
    *portb &= ~(1 << LED_PIN_BUILTIN); // Set built-in LED pin low
    delay(blinkDuration);
}
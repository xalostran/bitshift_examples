#define led1 2
#define led2 3
#define led3 4
#define builtInLed 5

volatile uint8_t *ddrb = (volatile uint8_t *)0x24;
volatile uint8_t *portb = (volatile uint8_t *)0x25;

unsigned long previousMillis1 = 1000; // led 1
unsigned long previousMillis2 = 1000; // led 2
unsigned long previousMillis3 = 1000; // led 3
unsigned long interval = 1000;        // intervall för alla LEDs
unsigned long blinkDuration = 100;    // Blink duration

void setup()
{
    // Sätt LED pins som outputs
    *ddrb |= (1 << led1);
    *ddrb |= (1 << led2);
    *ddrb |= (1 << led3);
    *ddrb |= (1 << builtInLed); // inbyggd LED
}

void loop()
{
    unsigned long currentMillis = millis(); // spara nuvarande tid
    int nextPin = millis() * (interval % millis());

    // LED 1
    if (currentMillis - previousMillis1 >= interval)
    {
        previousMillis1 = currentMillis; // spara sista blink
        *portb |= (1 << led1);           // växla LED 1 pin
        delay(1000);
        *portb &= ~(1 << led1);
        *portb |= (nextPin);
    }

    // LED 2
    if (currentMillis - previousMillis2 >= interval)
    {
        previousMillis2 = currentMillis;
        *portb |= (1 << led2); // växla LED 2 pin
        delay(1000);
        *portb &= ~(1 << led2);
        *portb |= (nextPin);
    }

    // LED 3
    if (currentMillis - previousMillis3 >= interval)
    {
        previousMillis3 = currentMillis;
        *portb |= (1 << led3); // växla LED 3 pin
        delay(1000);
        *portb &= ~(1 << led3);
        *portb |= (nextPin);
    }

    // inbyggd LED
    *portb &= ~(1 << builtInLed); // sätt inbyggd LED pin låg
    delay(blinkDuration);
}

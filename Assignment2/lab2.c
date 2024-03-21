#define led1 2
#define led2 3
#define led3 4
#define ledBuiltIn 5

#define button1 2
#define button2 3
#define button3 4
#define button4 5

volatile uint8_t *ddrb = (volatile uint8_t *)0x24;  // DDR för portb
volatile uint8_t *portb = (volatile uint8_t *)0x25; // portb register för kontroll av utgång

volatile uint8_t *ddrd = (volatile uint8_t *)0x2A;
volatile uint8_t *portd = (volatile uint8_t *)0x2B;
volatile uint8_t *pind = (volatile uint8_t *)0x29; // register för att läsa in data

void setup()
{
    // sätt LED pins som outputs
    *ddrb |= (1 << led1);
    *ddrb |= (1 << led2);
    *ddrb |= (1 << led3);
    *ddrb |= (1 << ledBuiltIn); // inbyggd LED

    *portd |= (1 << button1); // aktivera pull-up resistor
    *ddrd &= ~(1 << button1); // sätt utgång för knapp till inbyggd led

    *portd |= (1 << button2);
    *ddrd &= ~(1 << button2);

    *portd |= (1 << button3);
    *ddrd &= ~(1 << button3);

    *portd |= (1 << button4);
    *ddrd &= ~(1 << button4);

    // sätt knapp pins som inputs
}

void loop()
{
    // läs knapp status
    int isButton1 = !(*pind & (1 << button1)); // kontrollera knapp för led på portb
    int isButton2 = !(*pind & (1 << button2));
    int isButton3 = !(*pind & (1 << button3));
    int isButton4 = !(*pind & (1 << button4));

    // kontrollera LED status baserat på knapp tryck
    if (isButton1)
    {
        *portb |= (1 << led1);
    }
    else
    {
        *portb &= ~(1 << led1);
    }

    if (isButton2)
    {
        *portb |= (1 << led2);
    }
    else
    {
        *portb &= ~(1 << led2);
    }

    if (isButton3)
    {
        *portb |= (1 << led3);
    }
    else
    {
        *portb &= ~(1 << led3);
    }

    if (isButton4)
    {
        *portb |= (1 << ledBuiltIn);
    }
    else
    {
        *portb &= ~(1 << ledBuiltIn);
    }
}

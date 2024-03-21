#define led1 2
#define led2 3
#define led3 4
#define led4 5

#define button1 2
#define button2 3
#define button3 4
#define button4 5

volatile uint8_t *ddrb = (volatile uint8_t *)0x24;
volatile uint8_t *portb = (volatile uint8_t *)0x25;

volatile uint8_t *ddrd = (volatile uint8_t *)0x2A;
volatile uint8_t *portd = (volatile uint8_t *)0x2B;
volatile uint8_t *pind = (volatile uint8_t *)0x29;

int buttonCount = 0;

void setup()
{
    // Sätt LED pins som outputs
    *ddrb |= (1 << led1);
    *ddrb |= (1 << led2);
    *ddrb |= (1 << led3);
    *ddrb |= (1 << led4); // inbyggd LED

    *portd |= (1 << button1);
    *ddrd &= ~(1 << button1);

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
    int isButton1 = !(*pind & (1 << button1));
    int isButton2 = !(*pind & (1 << button2));
    int isButton3 = !(*pind & (1 << button3));
    int isButton4 = !(*pind & (1 << button4));

    if (isButton1 || isButton2 || isButton3)
        buttonCount++;

    // kontrollera LED status baserat på knapp tryck
    if (buttonCount >= 10 && isButton4)
    {
        *portb |= (1 << led4);
        buttonCount == 0;
    }
    else
    {
        *portb &= ~(1 << led4);
    }
    if ((isButton1 && isButton2) || (isButton2 && isButton3) || (isButton1 && isButton3))
        *portb |= (1 << led4);
    else
        *portb &= ~(1 << led4);

    if (isButton1)
        *portb |= (1 << led1);
    else
        *portb &= ~(1 << led1);

    if (isButton2)
        *portb |= (1 << led2);
    else
        *portb &= ~(1 << led2);

    if (isButton3)
        *portb |= (1 << led3);
    else
        *portb &= ~(1 << led3);
}
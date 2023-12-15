/*
 * Digital_Voltimeter.c
 *
 * Created: 13/12/2023 17:11:03
 * Author : Dell
 */ 

/*

* C code for Digital Voltmeter using ATmega32 Microcontroller

 */ 

#include <avr/io.h>

#define F_CPU 1000000

#include <util/delay.h>

#include <stdlib.h>


#define enable            5

#define registerselection 6


void send_a_command(unsigned char command);

void send_a_character(unsigned char character);

void send_a_string(const char *string_of_characters);


int main(void)

{

    DDRB = 0xFF;

    DDRA = 0;

    DDRD = 0xFF;

    _delay_ms(50);

    

    ADMUX |=(1<<REFS0);

    ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

    


    

    float voltage = 0;

    char voltageshow [7];

    


    send_a_command(0x01); //Clear Screen 0x01 = 00000001

    _delay_ms(50);

    send_a_command(0x38);

    _delay_ms(50);

    send_a_command(0b00001111);

    _delay_ms(50);

    

    ADCSRA |=(1<<ADSC);

    while(1)

    {

        //voltage = ADC/204.8*18;//ADC/18.618;
		
		//voltage = ADC/204.8*17.7;
		
		voltage = ADC/204.8*17.62;

        send_a_string ("CIRCUIT DIGEST  ");

        send_a_command(0x80 + 0x40 + 0);

        send_a_string ("VOLTAGE=");

        send_a_command(0x80 + 0x40 + 8);

        dtostrf(voltage, 5, 2, voltageshow);

        send_a_string(voltageshow);

        send_a_string("V   ");

        //dtostr(double precision value, width, precision, string that will store the numbers);

        // Value is either a direct value plugged into this place, or a variable to contains a value.

        //Width that is used with dtostrf is the number of characters in the number that includes the negative sign (-). For instance, if the number is -532.87, the width would be 7 including the negative sign and the decimal point.

        //Precision is how many numbers would be after the decimal point in the dtostrf usage.

        //Base is the maximum number of values per digit. For instance, 2 is for binary representation (2 possible values for each digit - 0 or 1); 10 is for the common human number system (10 possible values for each digit - 0, 1, 2, 3, 4, 5, 6, 7, 8, or 9); 16 is for hexadecimal where there are 16 possible values for each digit - 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, or F. It should be understood that if the base is larger, then the alphabet will just get larger.

        //String is the variable that accepts alphanumeric characters such as a char array. After the function is executed, the string will have the number stored within the array. For instance, if an integer variable contains the number 643, then the string variable will contain "634".

        send_a_command(0x80 + 0);

        

    }

}


void send_a_command(unsigned char command)

{

    PORTB = command;

    PORTD &= ~ (1<<registerselection);

    PORTD |= 1<<enable;

    _delay_ms(2);

    PORTD &= ~1<<enable;

    PORTB = 0;

}


void send_a_character(unsigned char character)

{

    PORTB = character;

    PORTD |= 1<<registerselection;

    PORTD |= 1<<enable;

    _delay_ms(2);

    PORTD &= ~1<<enable;

    PORTB = 0;

}

void send_a_string(const char *string_of_characters)

{

    while(*string_of_characters > 0)

    {

        send_a_character(*string_of_characters++);

    }

}


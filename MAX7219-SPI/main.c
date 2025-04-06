

/**
 * main.c
 */
#include <stdint.h>
#include "tm4c123gh6pm.h"

void init_port(void);
void display_write(char * str);
void display_init(void);
void SSI3_write(uint16_t);
void SSI3_init(void);

// PD0- clk, PD1 - CS, PD3 - Tx

uint8_t font[36][8] = {
                       {0x0, 0x3c, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x66},//A
                       {0x0, 0x7c, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x7c},//B
                       {0x0, 0x3c, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3c},//C
                       {0x0, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7c},//D
                       {0x0, 0x7e, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x7e},//E
                       {0x0, 0x7e, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x60},//F
                       {0x0, 0x3c, 0x66, 0x60, 0x60, 0x7e, 0x66, 0x3c},//G
                       {0x0, 0x66, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x66},//H
                       {0x0, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},//I
                       {0x0, 0x7e, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3c},//J
                       {0x0, 0x63, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0x63},//K
                       {0x0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e},//L
                       {0x0, 0xc6, 0xee, 0xfe, 0xd6, 0xc6, 0xc6, 0xc6},//M
                       {0x0, 0xc3, 0xe3, 0xd3, 0xcb, 0xc7, 0xc3, 0xc3},//N
                       {0x0, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c},//O
                       {0x0, 0x3c, 0x66, 0x66, 0x66, 0x7e, 0x60, 0x60},//P
                       {0x0, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x06},//Q
                       {0x0, 0x3c, 0x66, 0x66, 0x7e, 0x7c, 0x66, 0x66},//R
                       {0x0, 0x3c, 0x66, 0x60, 0x3c, 0x06, 0x66, 0x3c},//S
                       {0x0, 0x7e, 0x5a, 0x18, 0x18, 0x18, 0x18, 0x18},//T
                       {0x0, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c},//U
                       {0x0, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18},//V
                       {0x0, 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6},//W
                       {0x0, 0xc6, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0xc6},//X
                       {0x0, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18},//Y
                       {0x0, 0x7e, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x7e},//Z
                       {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Space
                       {0x0, 0x6C, 0x92, 0x82, 0x44, 0x28, 0x10, 0x00},//unfilled heart
                       {0x0, 0x6C, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00}// filled heart

};

int main(void)
{
      init_port();
       SSI3_init();
       display_init();
       int i;
       char str[4][100] = {"ABCDEF","GHIJKL","MNOPQR","STUVWXYZ"};
       while(1) {
           for (i=0;i<5;i++){
               display_write(str[i]);
           }
       }
	return 0;
}

void display_init(){
        uint16_t data;
        int i;
        for (i = 0; i < 16; i++)
        {
            data = i << 8;          //On initial power-up, all control registers are reset, the display is blanked
            SSI3_write(data);
        }

        data = 0x0b07;              //scan limit to make both equal brightness
        SSI3_write(data);
        data = 0x0c01;              //setting matrix to normal operation
        SSI3_write(data);
        data = 0x0a00 | 0x01;       //setting the intensity register to maximum value
        SSI3_write(data);
}

void display_write(char * str){
    int i = 0,j,a;
    uint16_t data;
    while (str[i] != '\0') {
        char c = str[i];
        if (c >= 'A' && c <= 'Z') {
            for (j = 0; j < 8; j++) {
                //MAX7219_sendCommand(j + 1, font[c - 'A'][j]);
                data = (j+1) << 8 | font[c - 'A'][j];
                SSI3_write(data);
                //for (a = 0; a < 500000; a++);
            }
            for (a = 0; a < 1000000; a++);
        }
        i++;
    }
}

void SSI3_write(uint16_t data){
    /* If the SSI is enabled and valid data is in the transmit FIFO, the start of transmission is signified by
        the SSInFss master signal being driven Low,*/

        GPIO_PORTD_DATA_R &= ~0x02; /* assert SS low */ //0000 1000 //choosing SSI0

        while ((SSI3_SR_R & 2) == 0); /* wait until FIFO not full */

        SSI3_DR_R = data; /* transmit high byte */

        while (SSI3_SR_R & 0x10); /* wait until transmit complete */

        /*In the case of a single word transmission, after all bits of the data word have been transferred, the
    SSInFss line is returned to its idle High state*/

        GPIO_PORTD_DATA_R |= 0x02; /* keep SS idle high */
}

void SSI3_init(void)
{
    SYSCTL_RCGCSSI_R |= 0x08;  // activate SSI0
    SYSCTL_RCGCGPIO_R |= 0x08; // activate port D

    SSI3_CR1_R &= ~SSI_CR1_SSE;           // disable SSI//This bit must be cleared before any control registers are reprogrammed
    SSI3_CR1_R &= ~SSI_CR1_MS;            // master mode//The SSI is configured as a master

    SSI3_CR0_R &= ~(SSI_CR0_SCR_M |       // SCR = 0 (1.6 Mbps data rate)
                    SSI_CR0_SPH |         // SPH = 0
                    SSI_CR0_SPO);         // SPO = 0 ; FRF = Freescale format ; DSS = 16-bit data//0xffff003f

    SSI3_CR0_R = (SSI3_CR0_R & ~SSI_CR0_FRF_M) + SSI_CR0_FRF_MOTO;//0xffff000f//selecting free scale format
    SSI3_CR0_R = (SSI3_CR0_R & ~SSI_CR0_DSS_M) + SSI_CR0_DSS_16;// 0xffff000f//selecting data width
    SSI3_CPSR_R = (SSI3_CPSR_R & ~SSI_CPSR_CPSDVSR_M) + 10;// clock divider for 1.6 MHz SSIClk (assumes 16 MHz PLL)
    SSI3_CR1_R |= SSI_CR1_SSE;            // enable SSI
    //programmed SSI0 to Free scale format, 16bit transfer, 0 polarity and 0 phase, clock speed 1.6MHz
}

void init_port(){
    //SYSCTL_RCGC2_R |= 0x3F;
    SYSCTL_RCGCGPIO_R |= 0x08;
    GPIO_PORTD_AFSEL_R |= 0x0B;                                             // enable alt funct on PD 0,1,3//clk cs tx
    GPIO_PORTD_DEN_R |= 0x0B;                                               // enable digital I/O on PD 0,1,3 ;
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0xFFFF0F00) + 0x00001011;
    GPIO_PORTD_AMSEL_R = 0;
}

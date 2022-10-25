#include "TFT.hpp"

// Pins de control
#define RES 17 
#define DC 25 

// Moduls SPI de la raspberry
#define SPI00 0
#define SPI01 1
#define SPI1_ 2

// Característiques del TFT
#define HEIGHT 240
#define WIDTH  320

void init_gpio() {
	int err;
	if ((err = gpioInitialise()) < 0) {
		std::string err_msg = "PI_INIT_FAILED";
		perror(err_msg.c_str());
		exit(err);
	}
}

int main () {
	//Inicialitzem la llibreria pigpio
	init_gpio();
	//Inicialitzem TFT
	TFT tft(DC,RES,HEIGHT,WIDTH);
	tft.init(SPI00,1000000);
	// omple la pantalla de blanc
	tft.fill(0xFFFF);
	// dibuixa una V
	tft.line(0,0, 160,200, 0x0000);
	tft.line(160,200, 319,0, 0x0000);
	return 0;
}
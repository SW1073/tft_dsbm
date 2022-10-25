#ifndef _TFT_CPP_
#define _TFT_CPP_

#include "TFT.hpp"

void TFT::write_cmd (Command c) {
    gpioWrite(DC, 0);
    this->spi.write_byte(c.get_com());
    gpioWrite(DC, 1);
    this->spi.write_byte_s(c.get_args(), c.get_args_size());
}

void TFT::input_init_commands() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        Command a;
        a.input_command();
        commands.push_back(a);
    }
}

void TFT::__delay_ms(int ms) {
	// Storing start time
	clock_t start_time = clock();
    // looping till required time is not achieved
	while (clock() < start_time + ms);
}


TFT::TFT (int dc, int res, int h, int w) {
    this->DC = dc;
    this->RES = res;
    this->HEIGHT = h;
    this->WIDTH = w;
}

void TFT::init (unsigned int spi_chan, unsigned int baud) {
    SPI s(spi_chan, baud);
    this->spi = s;
    spi.init();
    reset();
}

void TFT::reset () {
    input_init_commands();

    gpioWrite(DC, 1);
	gpioWrite(RES, 0);
	__delay_ms(250);
	gpioWrite(RES, 1);
	__delay_ms(6);

	write_cmd(commands[0]);
	__delay_ms(5);
	write_cmd(commands[1]);
	__delay_ms(5);

    int s = commands.size();

    for (int i = 2; i < (s-2); ++i) {
        write_cmd(commands[i]);
    }

	write_cmd(commands[s-2]);
	__delay_ms(100);
	write_cmd(commands[s-1]);
	__delay_ms(100);
}

void TFT::pixel (int x, int y, int color) {
    if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0) return; //no pintarem pixels fora de la pantalla

    std::vector<unsigned char> x_c {
        0x2B,
        (unsigned char)((x>>8)&0xFF),
        (unsigned char)(x&0xFF)
    };
    
    std::vector<unsigned char> y_c {
        0x2A,
        (unsigned char)((y>>8)&0xFF),
        (unsigned char)(y&0xFF)
    };

    std::vector<unsigned char> c_c {
        0x2C,
        (unsigned char)((color>>8)&0xFF),
        (unsigned char)(color&0xFF)
    };

    Command xx(x_c);
    Command yy(y_c);
    Command cc(c_c);

    write_cmd(xx);
    write_cmd(yy);
    write_cmd(cc);
    
	return;
}

void TFT::fill (int color) {
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x){
            this.pixel(x,y,color);
        }
}

void TFT::line (int x0, int y0, int x1, int y1, int color) {
    // Algoritme de línies de Bresenham (https://es.wikipedia.org/wiki/Algoritmo_de_Bresenham)
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;

    int dir_x = dx < 0 ? -1 : 1;
    int dir_y = dy < 0 ? -1 : 1;

    if(abs(dx) > abs(dy)) { // cas on la pendent és menor que 1 (m < 1)
        pixel(x,y,color);
        int pk = (2*abs(dy)) - abs(dx);
        for(int i = 0; i < abs(dx) ; i++) {
            x += dir_x;
            if(pk < 0)
                pk = pk + (2*abs(dy));
            else {
                y += dir_y;
                pk = pk + (2*abs(dy)) - (2*abs(dx));
            }
            pixel(x,y,color);
        }
    }
    else { // cas on la pendent és major o igual 1 (m >= 1)
        pixel(x,y,color);
        int pk = (2*abs(dx)) - abs(dy);
        for(int i = 0; i < abs(dy) ; i++) {
            y += dir_y;
            if(pk < 0)
                pk = pk + (2*abs(dx));
            else {
                x += dir_x;
                pk = pk + (2*abs(dx)) - (2*abs(dy));
            }
            pixel(x,y,color);
        }
    }
}


#endif

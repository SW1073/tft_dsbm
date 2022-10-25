#ifndef _SPI_HPP_
#define _SPI_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pigpio.h>
#include <string>

class SPI {
    private:
        int handle;
        unsigned int baud;
        unsigned int spi_chan;
        unsigned int spi_flags;
        
    public:
        SPI();
        SPI(unsigned int spi_chan, unsigned int baud);

        /* incialitza la connexió SPI (configura el módul HW)
         */
        void init ();

        /* tanca la connexió SPI
        */
        void terminate();

        /* escriu 1 byte per la connexió previament inicialitzada
         */
        void write_byte(unsigned char d);

        /* escriu count bytes (continguts a data) per la connexió
         * previament inicialitzada
         */
        void write_byte_s(char* data, int count);
};

#endif

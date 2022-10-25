#ifndef _TFT_HPP_
#define _TFT_HPP_

#include <time.h>
#include <math.h>
#include "SPI.hpp"
#include "Command.hpp"

class TFT {
    private:
        int DC;
        int RES;
		int HEIGHT;
		int WIDTH;
        SPI spi;
        std::vector<Command> commands;

        void write_cmd(Command c);
        void input_init_commands();
		void __delay_ms(int ms);

    public:
        /* Crea un objecte TFT i defineix les línies de control RES i DC,
         * que són pins GPIO en format BCM.
		 * h i w son alçada i amplada de la pantalla (240x320)
         */
        TFT (int DC, int RES, int h, int w);

        /* Estableix la connexió SPI amb la pantalla i envia la seqüència
         * de bytes d'inicialització (fa input d'aquestes comandes amb
         * std::cin. Les dades estan a input.txt).
         * spi_chan = 0, 1 o 2, depen de quin modul HW es vulgui usar:
         *      - 0 -> SPI module 0, Chip Select CS0
		 * 		- 1 -> SPI module 0, Chip Select CS1
         * 		- 2 -> SPI module 1, Chip Select CS0
         * 
         * baud rate entre [32_000 i 30_000_000], experimentalment s'ha trobat
         * que accepta com a màxim 1_000_000.
         */
        void init (unsigned int spi_chan, unsigned int baud);


		/* Reseteja la pantalla i torna a realitzar la seqüència d'inicialització
         */
        void reset ();

		/* Dibuixa un pixel a les coordenades donades i del color donat
		 */
        void pixel (int x, int y, int color);

        /* Omple la pantalla del color donat
         */
        void fill (int color);

		/* Dibuixa una linia entre els punts {x0,y0} i {x1,y1} del color donat.
		 */
        void line (int x0, int y0, int x1, int y1, int color);
};

#endif

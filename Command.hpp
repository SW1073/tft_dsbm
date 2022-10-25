#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <iostream>
#include <vector>

class Command{
	private:
		std::vector<unsigned char> dat;
		
	public:
		/* Construeix una comanda amb els continguts donats
		 */
		Command(std::vector<unsigned char>& dat);

		/* Construeix una comanda buida
		 */
		Command();

		/* Input dades d'una comanda usant std::cin
		 */
		void input_command();

		/* retorna el primer argument de la seqüencia
		 */
		char get_com();

		/* retorna un array d'arguments a partir del segon
		 * argument de la seqüència.
		 */
		char* get_args();
		
		/* retorna la mida total de la comanda (size)
		 */
		int get_total_size();

		/* retorna la mida de tots els arguments menys el primer (size-1)
		 */
		int get_args_size();
};

#endif

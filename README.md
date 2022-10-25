# TFT_DSBM
## Usage

 1. Instal·lar la llibreria **pigpio** a la raspberry. Instruccions de com fer-ho [aquí.](https://abyz.me.uk/rpi/pigpio/download.html)
 ```
 sudo apt install python-setuptools python3-setuptools
 wget https://github.com/joan2937/pigpio/archive/master.zip
 unzip master.zip
 cd pigpio-master
 make
 sudo make install
 ```

 2. Copiar repositori:
 ```
 git clone https://github.com/SW1073/tft_dsbm
 cd tft_dsbm
 ```
 
 3. Compilar:
 ```
 make
 ```

 4. Executar el codi del main (al fitxer `test.cpp`):
 ```
 sudo ./testCpp < input.txt
 ```

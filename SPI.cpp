#include "SPI.hpp"

#ifndef _SPI_CPP_
#define _SPI_CPP_


SPI::SPI() {
	this->handle = 0;
	this->baud = 32000;
	this->spi_chan = 0;
	this->spi_flags = 0b0000000000000000000011;
}

SPI::SPI(unsigned int spi_chan, unsigned int baud) {
    this->handle = 0;
    this->baud = baud;
    this->spi_chan = spi_chan;
    this->spi_flags = 0b0000000000000000000011;
}

void SPI::init () {
    if ((spi_chan != 0 && spi_chan != 1 && spi_chan != 2) || (baud < 32000 || baud > 125000000 ))
	{
		std::string err_msg = "Bad SPI_Connect parameters\n";
		perror(err_msg.c_str());
		exit(1);
	}

	int err = 0;
	if ((err = spiOpen(spi_chan, baud, spi_flags)) < 0)
	{
		std::string err_msg;
		switch (err) {
			case PI_BAD_SPI_CHANNEL:
					err_msg = "PI_BAD_SPI_CHANNEL";
					break;
			case PI_BAD_SPI_SPEED:
					err_msg = "PI_BAD_SPI_SPEED";
					break;
			case PI_BAD_FLAGS:
					err_msg = "PI_BAD_FLAGS";
					break;
			case PI_NO_AUX_SPI:
					err_msg = "PI_NO_AUX_SPI";
					break;
			case PI_SPI_OPEN_FAILED:
					err_msg = "PI_SPI_OPEN_FAILED";
					break;
			}
			perror(err_msg.c_str());
			exit(err);
	}
	handle = err; //this is the handle if everything went flawless
}

void SPI::terminate() {
    int err = 0;
	if ((err = spiClose(handle)) != 0)
	{
		std::string err_msg = "PI_BAD_HANDLE";
		perror(err_msg.c_str());
		exit(err);
	}
	gpioTerminate();
}

void SPI::write_byte(unsigned char d) {
	int err = 0;
	if ((err = spiWrite(handle, (char*)&d, 1)) < 0)
	{
		std::string err_msg;
		switch (err)
		{
		case PI_BAD_HANDLE:
			err_msg = "PI_BAD_HANDLE";
			break;
		case PI_BAD_SPI_COUNT:
			err_msg = "PI_BAD_SPI_COUNT";
			break;
		case PI_SPI_XFER_FAILED:
			err_msg = "PI_SPI_XFER_FAILED";
			break;
		default:
			err_msg = "UNKNOWN_ERROR";
			break;
		}
		perror(err_msg.c_str());
		exit(err);
	}
}

void SPI::write_byte_s(char* data, int count) {
	int err = 0;
	if ((err = spiWrite(handle, data, count)) < 0)
	{
		std::string err_msg;
		switch (err)
		{
		case PI_BAD_HANDLE:
			err_msg = "PI_BAD_HANDLE";
			break;
		case PI_BAD_SPI_COUNT:
			err_msg = "PI_BAD_SPI_COUNT";
			break;
		case PI_SPI_XFER_FAILED:
			err_msg = "PI_SPI_XFER_FAILED";
			break;
		default:
			err_msg = "UNKNOWN_ERROR";
			break;
		}
		perror(err_msg.c_str());
		exit(err);
	}
}

#endif

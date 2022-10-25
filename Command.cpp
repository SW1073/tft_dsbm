#include "Command.hpp"

#ifndef _COMMAND_CPP_
#define _COMMAND_CPP_

Command::Command(std::vector<unsigned char>& dat) {
	this->dat = dat;
}

Command::Command() {
	this->dat = std::vector<unsigned char>(0x00);
}

void Command::input_command() {
	int l;
	std::cin >> std::dec >> l;
	int a;
	while (l) {
		std::cin >> std::hex >> a;
		dat.push_back((unsigned char)a);
		--l;
	}
}

char Command::get_com() {
	return dat[0];
}

char* Command::get_args() {
	return (char*)&dat[1];
}

int Command::get_total_size() {
	return dat.size();
}

int Command::get_args_size() {
	return dat.size() - 1;
}

#endif

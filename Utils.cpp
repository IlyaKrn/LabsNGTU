#include "Utils.h"
#include<string>

namespace utils {

	int getIntFromString(std::string str) {
		for (int i = 0; i < str.size(); i++) {
			if (!(
				str[i] == '0' ||
				str[i] == '1' ||
				str[i] == '2' ||
				str[i] == '3' ||
				str[i] == '4' ||
				str[i] == '5' ||
				str[i] == '6' ||
				str[i] == '7' ||
				str[i] == '8' ||
				str[i] == '9'
				)) {
				//если не int
				throw std::string("string can not be converted to int");
			}
		}
		return stoi(str);
	}

}
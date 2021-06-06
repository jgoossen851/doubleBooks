#include "ansi.h"

namespace ansi{

	// void format(const char * local_format, const char * str, char * out, int max_size) {
		// snprintf(out, max_size, "%s%s%s%s", ansi::SAVE, local_format, str, ansi::RESTORE);
		// return;
	// }
	
	std::string CSI_(const char &fin){
		return (std::string)"\033[" + fin;
	}
	
	std::string CSI_(const char &fin, const int &n){
		return "\033[" + Code(n).str + fin;
	}
	
	std::string CSI_(const char &fin, const int &n, const int &m){
		return "\033[" + (Code(n) + Code(m)).str + fin;
	}
	
	std::string CSI_(const char &fin, const Code &code){
		return "\033[" + code.str + fin;
	}
	
	std::string CSI_(const char &fin, const std::string &code){
		return "\033[" + code + fin;
	}
	
	// template<typename T>
	// std::string SGR_(const T &code){
		// return CSI_('m', code);
	// }
	
	// std::string SGR_(const std::string &code){
		// // return "\033[" + code + "m";
		// return CSI_('m', code);
	// }
	
	// std::string SGR_(const Code &code){
		// // return "\033[" + code.str + "m";
		// return CSI_('m', code);
	// }
	
	// std::string SGR_(const int &code){
		// // return "\033[" + Code(code).str + "m";
		// return CSI_('m', code);
	// }

}
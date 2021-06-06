#ifndef ANSI_H_
#define ANSI_H_

/// Control Sequences
namespace ansi{
	
	/// Single-digit Select Graphic Rendition (SGR) codes
	#define _ANSI_FORMAT_SINGLE(Attribute, code) \
		constexpr char Attribute[] = {'\033', '[', code, 'm', '\0'}
	/// Double-digit Select Graphic Rendition (SGR) codes
	#define _ANSI_FORMAT_DOUBLE(Attribute, first, second) \
		constexpr char Attribute[] = {'\033', '[', first, second, 'm', '\0'}
		
	// Define codes
	constexpr char ESC_ 		= '\033';
	constexpr char FOREGROUND_ 	= '3';
	constexpr char BACKGROUND_ 	= '4';
	_ANSI_FORMAT_DOUBLE(BLACK, 		FOREGROUND_, '0');
	_ANSI_FORMAT_DOUBLE(RED,   		FOREGROUND_, '1');
	_ANSI_FORMAT_DOUBLE(GREEN, 		FOREGROUND_, '2');
	_ANSI_FORMAT_DOUBLE(YELLOW,		FOREGROUND_, '3');
	_ANSI_FORMAT_DOUBLE(BLUE, 		FOREGROUND_, '4');
	_ANSI_FORMAT_DOUBLE(CYAN, 		FOREGROUND_, '5');
	_ANSI_FORMAT_DOUBLE(MAGENTA,	FOREGROUND_, '6');
	_ANSI_FORMAT_DOUBLE(WHITE,		FOREGROUND_, '7');
	
	_ANSI_FORMAT_DOUBLE(BLACK_BG,	BACKGROUND_, '0');
	_ANSI_FORMAT_DOUBLE(RED_BG,		BACKGROUND_, '1');
	_ANSI_FORMAT_DOUBLE(GREEN_BG, 	BACKGROUND_, '2');
	_ANSI_FORMAT_DOUBLE(YELLOW_BG,	BACKGROUND_, '3');
	_ANSI_FORMAT_DOUBLE(BLUE_BG,	BACKGROUND_, '4');
	_ANSI_FORMAT_DOUBLE(CYAN_BG,	BACKGROUND_, '5');
	_ANSI_FORMAT_DOUBLE(MAGENTA_BG,	BACKGROUND_, '6');
	_ANSI_FORMAT_DOUBLE(WHITE_BG,	BACKGROUND_, '7');
	
	_ANSI_FORMAT_SINGLE(RESET, 		'0');
	
	// Intensity
	_ANSI_FORMAT_SINGLE(BOLD, 		'1');
	_ANSI_FORMAT_SINGLE(DIM, 		'2');
	_ANSI_FORMAT_DOUBLE(NORMAL, 	'2', '2');
	
	_ANSI_FORMAT_SINGLE(ITALIC, 	'3');
	_ANSI_FORMAT_DOUBLE(UPRIGHT, 	'2', '3');
	
	_ANSI_FORMAT_SINGLE(UNDERLINE,	'4');
	_ANSI_FORMAT_DOUBLE(NO_UNDERLINE, '2', '4');
	
	_ANSI_FORMAT_SINGLE(BLINK, 		'5');
	_ANSI_FORMAT_DOUBLE(NO_BLINK, 	'2', '5');
	
	_ANSI_FORMAT_SINGLE(REVERSE, 	'7');
	_ANSI_FORMAT_DOUBLE(PRIMARY,	'2', '7');
	
	_ANSI_FORMAT_SINGLE(STRIKE, 	'9');
	_ANSI_FORMAT_DOUBLE(NO_STRIKE,  '2', '9');

}

#endif

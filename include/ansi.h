#ifndef ANSI_H_
#define ANSI_H_

#include <string>

/// Control Sequences
namespace ansi{
  
  class Code {
    public:
    Code(){};
    Code(int code)
      : str(std::to_string(code)) {};
    Code(std::string code)
      : str(code) {};
    
    const std::string str;
    
    Code operator+(const Code& c) {
      return Code(this->str + ";" + c.str);
    };
  };
  
  /// Control Sequence Indicators
  std::string CSI_(const char &fin);
  std::string CSI_(const char &fin, const int &n);
  std::string CSI_(const char &fin, const int &n, const int &m);
  std::string CSI_(const char &fin, const Code &code);
  std::string CSI_(const char &fin, const std::string &code);
  
  /// Select Graphic Rendition
  template<typename T>
  std::string SGR_(const T &code);
  
  // ESCAPE SEQUENCES
  const std::string SAVE_ATTRIBUTES    = "\033" "7";
  const std::string RESTORE_ATTRIBUTES  = "\033" "8";
  
  // CONTROL SEQUENCES
  const std::string RESET_CURSOR    = CSI_('H', 1, 1);
  const std::string ERASE       = CSI_('J', 2);
  const std::string DELETE_SCROLLBACK = CSI_('J', 3);
  const std::string SAVE_CURSOR     = CSI_('s');
  const std::string RESTORE_CURSOR   = CSI_('u');

  /// @todo Figure out a way to scoll up the terminal to save the entire scrollback with CLEAR
  const std::string CLEAR     = ERASE + RESET_CURSOR;
  const std::string CLEAR_ALL   = CLEAR + DELETE_SCROLLBACK;
  
  // SELECT GRAPHIC RENDITION
  
  // Reset all formats
  const std::string RESET      = SGR_(0);
  
  // Apply basic attributes
  const std::string BOLD      = SGR_(1);
  const std::string DIM      = SGR_(2);
  const std::string ITALIC    = SGR_(3);
  const std::string UNDERLINE    = SGR_(4);
  const std::string BLINK      = SGR_(5);
  const std::string REVERSE    = SGR_(7);
  const std::string STRIKE    = SGR_(9);
                       
  // Remove basic attributes               
  const std::string NORMAL    = SGR_(22);
  const std::string UPRIGHT    = SGR_(23);
  const std::string NO_UNDERLINE  = SGR_(24);
  const std::string NO_BLINK    = SGR_(25);
  const std::string PRIMARY    = SGR_(27);
  const std::string NO_STRIKE    = SGR_(29);
                       
  // Define foreground colors              
  const std::string BLACK      = SGR_(30);
  const std::string RED       = SGR_(31);
  const std::string GREEN     = SGR_(32);
  const std::string YELLOW    = SGR_(33);
  const std::string BLUE       = SGR_(34);
  const std::string CYAN       = SGR_(35);
  const std::string MAGENTA    = SGR_(36);
  const std::string WHITE      = SGR_(37);
  const std::string DEFAULT    = SGR_(39);
                       
  // Define background colors              
  const std::string BLACK_BG    = SGR_(40);
  const std::string RED_BG    = SGR_(41);
  const std::string GREEN_BG     = SGR_(42);
  const std::string YELLOW_BG    = SGR_(43);
  const std::string BLUE_BG    = SGR_(44);
  const std::string CYAN_BG    = SGR_(45);
  const std::string MAGENTA_BG  = SGR_(46);
  const std::string WHITE_BG    = SGR_(47);
  const std::string DEFAULT_BG  = SGR_(49);
                       
  // Define other attributes               
  const std::string OVERLINE    = SGR_(53);
  const std::string NO_OVERLINE  = SGR_(55);
  
}
  
#include "ansi.tcc"
  
  // template<typename T>
  // std::string format(const char * local_format, T str) {
    // std::string output(ansi::SAVE);
    // output.append(local_format);
    // output.append(str);
    // output.append(ansi::RESTORE);
    // return output;
  // }
  
  // void format(const char * local_format, const char * str, char * out, int max_size);

#endif

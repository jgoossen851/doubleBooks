template<typename T>
std::string ansi::SGR_(const T &code){
  return ansi::CSI_('m', code);
}

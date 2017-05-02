#ifndef FILE_FUNC_HPP
#define FILE_FUNC_HPP

#include <fstream>
#include <string>

void copy_file(std::ifstream& in, std::ofstream& out);
void rewind_file(std::ifstream& in);

#endif // FILE_FUNC_HPP

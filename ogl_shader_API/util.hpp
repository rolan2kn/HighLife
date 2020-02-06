#pragma once

#include <string>
#include <vector>
#include <exception>


std::vector<std::string> get_args_vector(int argc, char** argv);

int parse_int(const std::string &string);

double parse_double(const std::string &string);

bool existe_archivo(const std::string &filename);

std::string basename(const std::string &filename);

std::vector<std::string> leer_lineas_archivo(const std::string &filename);

std::vector<std::string> listar_archivos(const std::string &dirname);

std::vector<std::string> listar_directorios(const std::string &dirname);

std::string directorio_actual();

std::string generar_nombre_archivo(const std::string path, const std::string& prefijo);

bool crear_directorio(std::string& dir);

bool existe_directorio(const std::string &dir);

std::vector<std::string> dividir_cadena(const std::string& target, const std::string& split_sequence);

void checkCompileErrors(uint shader, std::string type);

class NewException: public std::exception
{
private:
    std::string error_msg;
public:
    NewException(const std::string& mesg): error_msg(mesg) {}
    const std::string& what() {return error_msg;}
};




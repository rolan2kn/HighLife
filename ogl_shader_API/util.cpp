#include "util.hpp"

#include <dirent.h>

#include <sys/stat.h>
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <glad/glad.h>


#if defined(WIN32) || defined(_WIN32)
#define __getcwd _getcwd
#else
#include <unistd.h>
#define __getcwd getcwd
#endif

std::vector<std::string> get_args_vector(int argc, char** argv) {
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i) {
		args.push_back(std::string(argv[i]));
	}
	return args;
}

int parse_int(const std::string &string) {
	std::size_t next_position = 0;
	int n;
	try {
		n = std::stoi(string, &next_position, 10);
	} catch (...) {
		throw std::logic_error("invalid number \"" + string + "\"");
	}
	if (next_position != string.length())
		throw std::logic_error("invalid number \"" + string + "\"");
	return n;
}

double parse_double(const std::string &string) {
	std::size_t next_position = 0;
	double n;
	try {
		n = std::stod(string, &next_position);
	} catch (...) {
		throw std::logic_error("invalid number \"" + string + "\"");
	}
	if (next_position != string.length())
		throw std::logic_error("invalid number \"" + string + "\"");
	return n;
}

bool existe_archivo(const std::string &filename) {
	struct stat st;
	if (stat(filename.c_str(), &st) == 0)
		return S_ISREG(st.st_mode) ? true : false;
	return false;
}

bool existe_directorio(const std::string &dir) {
    if (opendir(dir.c_str()) == 0)
        return false;
    return true;
}


std::string basename(const std::string &filename) {
	std::size_t pos1 = filename.find_last_of("/\\");
	std::string name = (pos1 == std::string::npos) ? filename : filename.substr(pos1 + 1);
	std::size_t pos2 = name.find_last_of(".");
	return (pos2 == std::string::npos) ? name : name.substr(0, pos2);

}

std::vector<std::string> leer_lineas_archivo(const std::string &filename) {
	std::vector<std::string> lines;
	std::ifstream infile;
	infile.open(filename);
	if (!infile.is_open()) {
		std::cout << "no puedo abrir " << filename << std::endl;
		return lines;
	}
	while (!infile.eof()) {
		std::string line;
		std::getline(infile, line, '\n');
		lines.push_back(line);
	}
	return lines;
}

void agregar_archivo(const std::string &dirname, const std::string &name, std::vector<std::string> &list) {
	std::string fullpath = dirname + "/" + name;
#if defined WIN32 || defined _WIN32
	struct stat64 st;
	int status = stat64(fullpath.c_str(), &st);
#elif defined __linux || defined __linux__
	struct stat st;
	int status = stat(fullpath.c_str(), &st);
#endif
	if (status == 0 && S_ISREG(st.st_mode)) {
		list.push_back(fullpath);
	}
}

void agregar_directorio(const std::string &dirname, const std::string &name, std::vector<std::string> &list) {
    std::string fullpath = dirname + "/" + name;
#if defined WIN32 || defined _WIN32
    struct stat64 st;
	int status = stat64(fullpath.c_str(), &st);
#elif defined __linux || defined __linux__
    struct stat st;
    int status = stat(fullpath.c_str(), &st);
#endif

    if (status == 0 && S_ISDIR(st.st_mode) && name != "." && name != "..") {
        list.push_back(fullpath);
    }
}

std::vector<std::string> listar_archivos(const std::string &dirname) {
	std::vector<std::string> list;
#if defined WIN32 || defined _WIN32
	DIR *dp = opendir(dirname.c_str());
	if (dp == NULL) {
		std::cout << "error abriendo " << dirname << std::endl;
		return list;
	}
	struct dirent *dir_entry;
	while ((dir_entry = readdir(dp)) != NULL) {
		std::string name(dir_entry->d_name);
		agregar_archivo(dirname, name, list);
	}
	if (closedir(dp) != 0) {
		std::cout << "error cerrando " << dirname << std::endl;
	}
#elif defined __linux || defined __linux__
	struct dirent **namelist = NULL;
	int len = scandir(dirname.c_str(), &namelist, NULL, NULL);
	if (len < 0) {
		std::cout << "error abriendo " << dirname << std::endl;
		return list;
	}
	for (int i = 0; i < len; ++i) {
		std::string name(namelist[i]->d_name);
		agregar_archivo(dirname, name, list);
		free(namelist[i]);
	}
	free(namelist);
#endif
	std::sort(list.begin(), list.end());
	return list;
}

std::vector<std::string> listar_directorios(const std::string &dirname) {
    std::vector<std::string> list;
#if defined WIN32 || defined _WIN32
    DIR *dp = opendir(dirname.c_str());
	if (dp == NULL) {
		std::cout << "error abriendo " << dirname << std::endl;
		return list;
	}
	struct dirent *dir_entry;
	while ((dir_entry = readdir(dp)) != NULL) {
		std::string name(dir_entry->d_name);
		agregar_archivo(dirname, name, list);
	}
	if (closedir(dp) != 0) {
		std::cout << "error cerrando " << dirname << std::endl;
	}
#elif defined __linux || defined __linux__
    struct dirent **namelist = NULL;
    int len = scandir(dirname.c_str(), &namelist, NULL, NULL);
    if (len < 0) {
        std::cout << "error abriendo " << dirname << std::endl;
        return list;
    }
    for (int i = 0; i < len; ++i) {
        std::string name(namelist[i]->d_name);
        agregar_directorio(dirname, name, list);
        free(namelist[i]);
    }
    free(namelist);
#endif
    std::sort(list.begin(), list.end());
    return list;
}

std::string directorio_actual()
{
    char cwd[1024];
    if (__getcwd(cwd, sizeof(cwd)) == nullptr)
        return "";

    std::string currentDir (cwd);
    int idx = currentDir.rfind("/");

    if (idx == -1)
        return "";

    int pos = currentDir.find("cmake");
    if (pos != -1)
    {
        currentDir = currentDir.substr(0, pos);
    }

    return currentDir;
}

bool crear_directorio(std::string& dir)
{
    std::string command("mkdir -p \'" + dir +"\'" );
    const int dir_err = system(command.c_str());

    if (-1 == dir_err)
    {
        std::cout <<std::endl<<"Error creating directory!n";
        return false;
    }
    return true;
}

std::vector<std::string> dividir_cadena(const std::string& target, const std::string& split_sequence)
{
    std::vector<std::string> parts;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = target.find(split_sequence, pos)) != std::string::npos)
    {
        parts.push_back(target.substr(prev_pos, pos-prev_pos));
        pos += split_sequence.size();
        prev_pos = pos;
    }
    if(prev_pos > 0)
        parts.push_back(target.substr(prev_pos, target.size()-prev_pos));

    return parts;
};

std::string generar_nombre_archivo(const std::string path, const std::string& prefijo)
{
    std::string ppref = basename(prefijo);
    return path + prefijo + "_" + std::to_string(clock());
}

void checkCompileErrors(uint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
#include "webserv.hpp"

std::string extractBoundary(const std::string& formData) 
{
    std::istringstream iss(formData);
    std::string line;
    std::string boundary;

    // Trouver la ligne contenant le boundary
    while (std::getline(iss, line)) {
        if (line.find("boundary=") != std::string::npos) {
            // Extraire le boundary de la ligne
            size_t pos = line.find("boundary=");
            boundary = line.substr(pos + 9); // 9 est la longueur de "boundary="
            // Supprimer les guillemets s'il y en a
            if (boundary.front() == '"') {
                boundary = boundary.substr(1, boundary.size() - 2);
            }
             // Supprimer les caractères de fin de ligne (espaces, retours chariot, sauts de ligne, etc.)
            size_t end = boundary.size();
            while (end > 0 && std::isspace(boundary[end - 1])) {
                --end;
            }
            boundary.resize(end);
            break;
        }
    }

    return boundary;
}

std::string parseMultipartFormData(const std::string& formData) {
    std::string boundary = extractBoundary(formData);
    if (boundary.empty()) {
        return NULL;
    }

    std::istringstream iss(formData);
    std::string line;
    std::string boundaryHeader = "--" + boundary;

    while (std::getline(iss, line)) {
        // Trouver le début de la partie
        if (line.find(boundaryHeader) == 0) {
            std::string partData;
            // Récupérer les données de la partie
            while (std::getline(iss, line)) {
                if (line.find(boundaryHeader) == 0)
                    break; 
                partData += line + "\n";
            }
            return partData;
        }
    }
    return NULL;
}

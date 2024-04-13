#include "webserv.hpp"


void parseMultipartFormData(const std::string& formData, std::map<std::string, std::string>& parsedData) {
    // Trouver le délimiteur à partir de l'en-tête Content-Type
    std::string boundary;
    size_t contentTypePos = formData.find("Content-Type:");
    if (contentTypePos != std::string::npos) {
        size_t boundaryPos = formData.find("boundary=", contentTypePos);
        if (boundaryPos != std::string::npos) {
            size_t boundaryEndPos = formData.find("\r\n", boundaryPos);
            boundary = formData.substr(boundaryPos + 9, boundaryEndPos - (boundaryPos + 9)); // +9 pour passer "boundary="
        } else {
            std::cerr << "Boundary not found in Content-Type header!" << std::endl;
            return;
        }
    } else {
        std::cerr << "Content-Type header not found!" << std::endl;
        return;
    }

    // Construire la chaîne complète du délimiteur
    boundary = "--" + boundary;

    // Trouver les délimiteurs de sections
    size_t pos = formData.find(boundary);
    while (pos != std::string::npos) {
        // Trouver le début des données
        size_t start = formData.find("\r\n\r\n", pos);
        if (start == std::string::npos) {
            break; // Pas de données, fin de la requête
        }
        start += 4; // Passer les caractères de délimitation

        // Trouver la fin des données
        size_t end = formData.find(boundary, start);
        if (end == std::string::npos) {
            end = formData.size(); // Fin de la requête
        } else {
            end -= 2; // Reculer avant les caractères de délimitation
        }

        // Extraire les données de la section
        std::string sectionData = formData.substr(start, end - start);

        // Extraire le nom du champ
        size_t nameStart = formData.find("name=\"", pos) + 6;
        size_t nameEnd = formData.find("\"", nameStart);
        std::string fieldName = formData.substr(nameStart, nameEnd - nameStart);

        // Stocker les données extraites
        parsedData[fieldName] = sectionData;

        // Trouver le prochain délimiteur de section
        pos = formData.find(boundary, end);
    }
}

int parse_upload(const std::string& formData, int client_fd) 
{
    std::map<std::string, std::string> parsedData;
    client_fd += 0;
    parseMultipartFormData(formData, parsedData);

    // Affichage des données analysées
    for (std::map<std::string, std::string>::iterator it = parsedData.begin(); it != parsedData.end(); ++it) {
        std::cout << "Field: " << it->first << ", Value: " << it->second << std::endl;
    }

    return 0;
}



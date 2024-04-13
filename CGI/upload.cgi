import sys

def create_file(data):
    # Supprimer les espaces en début et fin de la chaîne de données
    data = data.strip()

    # Trouver l'index du début du contenu du fichier
    file_content_start_index = data.find('\n\n') + 2

    # Extraire le nom du fichier
    filename_start_index = data.find('filename="') + len('filename="')
    filename_end_index = data.find('"', filename_start_index)
    filename = data[filename_start_index:filename_end_index]

    # Trouver l'index de fin du contenu du fichier
    file_content_end_index = data.rfind('\n')

    # Extraire le contenu du fichier
    file_content = data[file_content_start_index:file_content_end_index]

    # Écrire le contenu dans le fichier
    with open(filename, 'w') as file:
        file.write(file_content)

    print(f"Fichier {filename} créé avec succès.")

# Vérifier si les données du formulaire sont fournies en argument
if len(sys.argv) != 2:
    print("Veuillez fournir les données du formulaire en argument.")
    sys.exit(1)

# Récupérer les données du formulaire à partir des arguments
form_data = sys.argv[1]

# Créer le fichier en utilisant les données du formulaire
create_file(form_data)


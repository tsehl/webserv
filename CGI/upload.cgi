import sys
import os

def process_form_data(temp_file_path):
    with open(temp_file_path, 'rb') as temp_file:
        # Lire les données du fichier temporaire en mode binaire
        form_data = temp_file.read()

        # Séparer les en-têtes et le contenu du formulaire
        headers, form_content = form_data.split(b'\r\n\r\n', 1)

        # Extraire le nom du fichier du header Content-Disposition
        filename_start_index = headers.find(b'filename="') + len(b'filename="')
        filename_end_index = headers.find(b'"', filename_start_index)
        filename = headers[filename_start_index:filename_end_index]

        # Écrire le contenu du formulaire dans le fichier correspondant au nom du fichier
        with open(filename, 'wb') as file_from_form:
            file_from_form.write(form_content)

        print(f"Fichier {filename} créé avec succès.")

def main():
    # Assurez-vous qu'un seul argument est passé au script, le chemin du fichier temporaire
    if len(sys.argv) != 2:
        print("Usage: python script.py [temp_file_path]")
        sys.exit(1)

    # Récupérer le chemin du fichier temporaire à partir des arguments
    temp_file_path = sys.argv[1]

    # Traiter les données du formulaire
    process_form_data(temp_file_path)

    # Supprimer le fichier temporaire une fois le traitement terminé
    os.remove(temp_file_path)

if __name__ == "__main__":
    main()


#!/usr/bin/env python3

import cgi
import os

# Définit le répertoire de destination des fichiers uploadés
upload_dir = "/chemin/vers/le/repertoire/upload"

# Crée un objet FieldStorage pour obtenir les données du formulaire
form = cgi.FieldStorage()

# Vérifie si un fichier a été envoyé
if "file" in form:
    # Obtient les détails du fichier
    file_item = form["file"]
    
    # Vérifie si le fichier a été téléchargé avec succès
    if file_item.file:
        # Construit le chemin complet du fichier de destination
        filename = os.path.join(upload_dir, os.path.basename(file_item.filename))
        
        # Ouvre le fichier de destination en écriture binaire
        with open(filename, 'wb') as f:
            # Lit le fichier téléchargé par morceaux et écrit dans le fichier de destination
            while True:
                chunk = file_item.file.read(8192)
                if not chunk:
                    break
                f.write(chunk)
        
        # Affiche un message de succès
        print("Content-type:text/html\r\n\r\n")
        print("<html>")
        print("<head>")
        print("<title>Upload réussi</title>")
        print("</head>")
        print("<body>")
        print("<h2>Upload réussi</h2>")
        print("<p>Le fichier {} a été téléchargé avec succès.</p>".format(file_item.filename))
        print("</body>")
        print("</html>")
    else:
        # Affiche un message d'erreur si le fichier n'a pas été téléchargé avec succès
        print("Content-type:text/html\r\n\r\n")
        print("<html>")
        print("<head>")
        print("<title>Erreur lors de l'upload</title>")
        print("</head>")
        print("<body>")
        print("<h2>Erreur lors de l'upload</h2>")
        print("<p>Le fichier n'a pas été téléchargé correctement.</p>")
        print("</body>")
        print("</html>")
else:
    # Affiche un message d'erreur si aucun fichier n'a été envoyé
    print("Content-type:text/html\r\n\r\n")
    print("<html>")
    print("<head>")
    print("<title>Erreur</title>")
    print("</head>")
    print("<body>")
    print("<h2>Aucun fichier n'a été envoyé</h2>")
    print("<p>Veuillez sélectionner un fichier à télécharger.</p>")
    print("</body>")
    print("</html>")


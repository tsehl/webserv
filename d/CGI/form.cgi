#!/usr/bin/env python3

import cgi

# Entête de la réponse HTTP
print("Content-type: text/html\n")

# Analyser les données de l'URL (méthode GET)
form = cgi.FieldStorage()
if "nom" in form and "age" in form:
    nom = form["nom"].value
    age = form["age"].value
    print("<p>Bonjour, {}! Vous avez {} ans.</p>".format(nom, age))
else:
    # Début de la page HTML
    print("<html>")
    print("<head><title>Formulaire CGI</title></head>")
    print("<body>")
    print("<h1>Formulaire CGI</h1>")
    
    # Affichage du formulaire
    print("<form method='get' action='script.cgi'>")
    print("Nom: <input type='text' name='nom'><br>")
    print("Age: <input type='text' name='age'><br>")
    print("<input type='submit' value='Envoyer'>")
    print("</form>")
    
    # Fin de la page HTML
    print("</body>")
    print("</html>")

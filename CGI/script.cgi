#!/usr/bin/perl

use strict;
use warnings;

# En-tête HTTP avec le type de contenu text/plain

print"HTTP/1.1 200 OK\r\n";
print "Content-Type: text/html\r\n";
print "Connection: close\r\n";
print "\r\n";
# Corps de la réponse
print "Bonjour, ceci est un script CGI qui renvoie du texte brut.";

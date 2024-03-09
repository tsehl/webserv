#!/usr/bin/perl

use strict;
use warnings;
use CGI;

my $cgi = CGI->new;
my $file = $cgi->upload('file');

if ($file) {
    my $filename = $cgi->param('file');
    open my $fh, '>', "/chemin/vers/votre/repertoire/$filename" or die "Impossible d'ouvrir le fichier : $!";
    while (my $chunk = <$file>) {
        print $fh $chunk;
    }
    close $fh;
    print $cgi->header;
    print "Fichier '$filename' téléchargé avec succès.";
} else {
    print $cgi->header;
    print "Aucun fichier téléchargé.";
}

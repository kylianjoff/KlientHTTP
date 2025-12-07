#include "http_methods.h"
#include <stddef.h>

static const char* method_names[] = {
    "GET", "POST", "PUT", "DELETE", "HEAD", "OPTIONS", "PATCH", "TRACE", "CONNECT"
};

static const char* method_descriptions[] = {
    "Récupérer des données",
    "Envoyer des données (création)",
    "Mettre à jour des données",
    "Supprimer des données",
    "Récupérer les headers uniquement",
    "Obtenir les options de communication",
    "Modification partielle",
    "Test de boucle (echo)",
    "Etablir un tunnel"
};

const char* get_method_name(HttpMethod method) {
    return method_names[method];
}

const char* get_method_description(HttpMethod method) {
    return method_descriptions[method];
}

int get_method_count(void) {
    return sizeof(method_names) / sizeof(method_names[0]);
}
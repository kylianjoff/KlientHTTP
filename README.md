# KlientHTTP

> Un client HTTP moderne en C avec interface console interactive et support complet de toutes les méthodes HTTP.

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey?style=for-the-badge)

---

## Fonctionnalités

- **9 méthodes HTTP** : GET, POST, PUT, DELETE, HEAD, OPTIONS, PATCH, TRACE, CONNECT
- **Interface interactive** avec navigation par flèches
- **Résolution DNS** automatique
- **Headers personnalisés** optionnels
- **Support du body** pour POST/PUT/PATCH
- **Interface colorée** avec code ANSI
- **Architecture modulaire** et maintenable
- **Sockets TCP/IP** natifs en C

---

## Structure du projet

'''
'''

---

## Installation

### Prérequis

- **GCC** (GNU Compiler Collection)
- **Make**
- **Linux** ou **macOS** (Unix-like system)

'''bash
# Vérifier GCC
gcc --version
# Vérifier Make
make --version
'''

### Compilation

'''bash
# Cloner ou télécharger le projet
cd KlientHTTP

# Compiler
make

# Ou compiler et exécuter directement (pas encore fonctionnel)
make run
'''

---

## Utilisation

### Démarrage

'''bash
./bin/KlientHTTP
'''

### Navigation

- **↑/↓** : Naviguer dans les menus
- **ENTER** : Valider la sélection
- **O/n** : Confirmer les actions

### Exemple de session

'''
1. Sélectionnez une méthode HTTP (ex: GET)
2. Entrez le hostname (ex: www.google.com)
3. Entrez le path (ex: / ou /api/users)
4. Ajoutez des headers si nécessaire
5. Ajoutez un body pour POST/PUT/PATCH
6. Confirmez et envoyez !
'''

---

## Exemples d'utilisation

### GET simple

'''
Méthode: GET
Hostname: www.example.com
Path: /
'''

### POST avec body JSON

'''
Méthode: POST
Hostname: httpbin.org
Path: /post
Body: {"name":"John","age":30}
'''

### Avec headers personnalisés

'''
Méthode: GET
Hostname: api.github.com
Path: /users/github
Headers: Autorization: Bearer YOUR_TOKEN
'''

### Sites de test recommandés

- **httpbin.org** - Service de test HTTP
- **jsonplaceholder.typicode.com** - API REST fictive
- **reqres.in** - API de test

---

## Commandes Make

| Commande | Description |
|----------|-------------|
| 'make' | Compile le projet |
| 'make run' (Bientôt) | Compile et exécute |
| 'make clean' (Bientôt) | Nettoie les fichiers compilés |
| 'make  re' (Bientôt) | Recompile tout (clean + all) |
| 'make debug' (Bientôt) | Compile en mode debug |
| 'make info' (Bientôt) | Affiche les infos du projet |
| 'make help' (Bientôt) | Affiche l'aide complète |

---

## Architecture technique

### Modules

#### 'http_client.c/h'
- Gestion des sockets TCP/IP
- Résolution DNS avec 'gethostbyname()'
- Construction et envoi des requêtes HTTP
- Réception des réponses

#### 'http_method.c/h'
- Enumération des méthodes HTTP
- Descriptions des méthodes
- Utilitaires de gestion

#### 'ui.c/h'
- Interface console interactive
- Navigation par flèches
- Gestion des entrées utilisateur
- Affichage coloré

#### 'utils.c/h'
- Fonctions utilitaires
- Gestion des strings
- Codes couleurs ANSI
- Helpers divers

---

## Personnalisation

### Modifier le port

Dans 'http_client.h', changez :
'''c
#define HTTP_PORT 80 // Pour HTTP standard
#define HTTPS_PORT 443 // Pour HTTPS (non implémenté)
'''

### Ajouter une méthode HTTP

1. Ajoutez dans 'http_methods.h' :
'''c
typedef enum {
    // ... méthodes existantes
    METHOD_CUSTOM
} HttpMethod;
'''

2. Mettez à jour les tableaux dans 'http_methods.c'

---

## Dépannage

### Erreur de compilation

'''bash
# Nettoyer et recompiler
make clean
make
'''

### Erreur "gethostbyname failed"

- Vérifiez votre connexion internet
- Vérifiez le hostname saisi
- Testez avec 'ping hostname'

### Erreur "Connection refused"

- Le serveur peut être down
- Le port peut être bloqué
- Vérifiez votre firewall

### Navigation par flèches ne fonctionne pas

- Votre terminal doit supporter les séquences ANSI
- Essayez un autre terminal (xterm, gnome-terminal, iTerm2)

---

## Ressources

- [RFC 2616 - HTTP/1.1](https://www.ietf.org/rfc/rfc2616.txt)
- [Socket Programming in C](https://www.geeksforgeeks.org/socket-programming-cc/)
- [ANSI Escape Codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)

---

## Contribution

Le projet n'est pour le moment pas ouvert aux contributions.

---

## TODO

- [ ] Support HTTPS (SSL/TLS)
- [ ] Sauvegarde de l'historique des requêtes
- [ ] Export des réponses (fichier)
- [ ] Support des cookies
- [ ] Authentification basique/digest
- [ ] Mode batch (non-interactif)
- [ ] Coonfiguration via fichier
- [ ] Tests unitaires
- [ ] Support IPv6

---

## Auteur

Créé par Kylian JULIA (kylianjulia.fr).

---

## License

Ce projet est sous licence MIT. Voir le fichier 'LICENSE' pour plus de détails.

---

## Remerciements

- Inspiré par curl et httpie
- Documentation RFC pour les spécifications HTTP

---

<div align="center">

Made in C

</div>
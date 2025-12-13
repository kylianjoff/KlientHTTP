# KlientHTTP

> Un client HTTP moderne en C avec interface console interactive et support complet de toutes les méthodes HTTP.

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey?style=for-the-badge)

---

## Fonctionnalités

- **9 méthodes HTTP** : GET, POST, PUT, DELETE, HEAD, OPTIONS, PATCH, TRACE, CONNECT
- **Support HTTPS/SSL** avec OpenSSL
- **Interface interactive** avec navigation par flèches
- **Résolution DNS** automatique
- **Headers personnalisés** optionnels
- **Support du body** pour POST/PUT/PATCH
- **Interface colorée** avec code ANSI
- **Architecture modulaire** et maintenable
- **Sockets TCP/IP** natifs en C

---

## Structure du projet

```
KlientHTTP/
├─ Makefile # Compilation automatique
├─ README.md # Ce fichier
├─ include/ # Headers (.h)
│  ├─ http_client.h # Client HTTP
│  ├─ http_methods.h # Méthodes HTTP
│  ├─ ui.h # Interface utilisateur
│  └─ utils.h # Utilitaires
├─ src/ # Sources (.c)
│  ├─ main.c # Point d'entrée
│  ├─ http_client.c # Implémentation client
│  ├─ http_methods.c # Gestion des méthodes
│  ├─ ui.c # Interface console
│  └─ utils.c # Fonctions utilitaires
├─ obj/ # Fichiers objets (généré)
└─ bin/ # Exécutable (généré)
```

---

## Installation

### Prérequis

- **GCC** (GNU Compiler Collection)
- **Make**
- **OpenSSL** (pour le support HTTPS)
- **Linux** ou **macOS** (Unix-like system)

#### Installation des dépendances

**Ubuntu/Debian :**
```bash
sudo apt-get update
sudo apt-get install build-essential libssl-dev
```

**Fedora/RHEL/CentOS :**
```bash
sudo dnf install gcc make openssl-devel
```

**Arch Linux :**
```bash
sudo pacman -S base-devel openssl
```

**macOS :**
```bash
brew install openssl
# Si erreur de linkage, ajouter au PATH :
export PATH="/usr/local/opt/openssl/bin:$PATH"
```

#### Vérification de l'installation

```bash
# Vérifier GCC
gcc --version
# Vérifier Make
make --version
# Vérifier OpenSSL
openssl version
```

### Compilation

```bash
# Cloner ou télécharger le projet
cd KlientHTTP

# Compiler
make

# Ou compiler et exécuter directement (pas encore fonctionnel)
make run
```

---

## Utilisation

### Démarrage

```bash
./bin/KlientHTTP
```

### Navigation

- **↑/↓** : Naviguer dans les menus
- **ENTER** : Valider la sélection
- **O/n** : Confirmer les actions

### Exemple de session

```
1. Sélectionnez une méthode HTTP (ex: GET)
2. Entrez le hostname (ex: www.google.com)
3. Entrez le path (ex: / ou /api/users)
4. Ajoutez des headers si nécessaire
5. Ajoutez un body pour POST/PUT/PATCH
6. Confirmez et envoyez !
```

---

## Exemples d'utilisation

### GET simple

```
Méthode: GET
Hostname: www.example.com
HTTPS: Non
Path: /
```

### GET sécurisé (HTTPS)

```
Méthode: GET
Hostname: www.google.com
HTTPS: Oui
Path: /
```

### POST avec body JSON (HTTPS)

```
Méthode: POST
Hostname: httpbin.org
HTTPS: Oui
Path: /post
Body: {"name":"John","age":30}
```

### API GitHub (HTTPS avec headers)

```
Méthode: GET
Hostname: api.github.com
HTTPS: Oui
Path: /users/github
Headers: Authorization: Bearer YOUR_TOKEN
```

### Sites de test recommandés

- **https://httpbin.org** - Service de test HTTP
- **https://jsonplaceholder.typicode.com** - API REST fictive
- **https://reqres.in** - API de test
- **https://api.github.com** - API GitHub publique

---

## Commandes Make

| Commande | Description |
|----------|-------------|
| `make` | Compile le projet |
| `make run` | Compile et exécute |
| `make clean` | Nettoie les fichiers compilés |
| `make fclean` | Nettoyage complet (même les backup) |
| `make re` | Recompile tout (clean + all) |
| `make debug` | Compile en mode debug |
| `make info` | Affiche les infos du projet |
| `make help` | Affiche l'aide complète |

---

## Architecture technique

### Modules

#### `http_client.c/h`
- Gestion des sockets TCP/IP
- Résolution DNS avec `gethostbyname()`
- Construction et envoi des requêtes HTTP
- Réception des réponses

#### `http_methods.c/h`
- Enumération des méthodes HTTP
- Descriptions des méthodes
- Utilitaires de gestion

#### `ui.c/h`
- Interface console interactive
- Navigation par flèches
- Gestion des entrées utilisateur
- Affichage coloré

#### `utils.c/h`
- Fonctions utilitaires
- Gestion des strings
- Codes couleurs ANSI
- Helpers divers

---

## Personnalisation

### Modifier le port

Dans `http_client.h`, changez :
```c
#define HTTP_PORT 80 // Pour HTTP standard
#define HTTPS_PORT 443 // Pour HTTPS (non implémenté)
```

### Ajouter une méthode HTTP

1. Ajoutez dans `http_methods.h` :
```c
typedef enum {
    // ... méthodes existantes
    METHOD_CUSTOM
} HttpMethod;
```

2. Mettez à jour les tableaux dans `http_methods.c`

---

## Dépannage

### Erreur de compilation

```bash
# Nettoyer et recompiler
make clean
make
```

### Erreur "gethostbyname failed"

- Vérifiez votre connexion internet
- Vérifiez le hostname saisi
- Testez avec 'ping hostname'

### Erreur "SSL handshake failed"

- Le serveur ne supporte peut-être pas HTTPS
- Essayez en mode HTTP au lieu de HTTPS
- Vérifiez que le port 443 n'est pas bloqué

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

- [X] Support HTTPS (SSL/TLS)
- [ ] Sauvegarde de l'historique des requêtes
- [ ] Export des réponses (fichier)
- [ ] Support des cookies
- [ ] Authentification basique/digest
- [ ] Mode batch (non-interactif)
- [ ] Configuration via fichier
- [ ] Tests unitaires
- [ ] Support IPv6

---

## Auteur

Créé par Kylian JULIA ([kylianjulia.fr](https://kylianjulia.fr/)).

---

## License

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

---

## Remerciements

- Inspiré par curl et httpie
- Documentation RFC pour les spécifications HTTP

---

<div align="center">

Made in C

</div>
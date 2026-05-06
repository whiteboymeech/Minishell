*This project has been created as part of the 42 curriculum by mabenois, adarolla*

# 🐚 minishell

> *"Jean Moulin & De Gaulle 2000"*

Un shell UNIX minimaliste réalisé dans le cadre du cursus **42**, par [**mabenois**](https://github.com/mabenois) et [**adarolla**](https://github.com/adarolla).

---

## 📋 Description

`minishell` est une implémentation simplifiée d'un shell UNIX inspiré de **bash**. Le projet couvre l'ensemble du cycle de vie d'une commande : lecture du prompt, lexing, parsing, expansion des variables, gestion des redirections, des pipes, des heredocs, et l'exécution des builtins ou des binaires externes.

---

## ✨ Fonctionnalités

### Builtins implémentés
| Commande | Description |
|----------|-------------|
| `echo` | Affiche du texte, supporte le flag `-n` |
| `cd` | Change le répertoire courant |
| `pwd` | Affiche le répertoire courant |
| `export` | Déclare ou modifie une variable d'environnement |
| `unset` | Supprime une variable d'environnement |
| `env` | Affiche l'environnement courant |
| `exit` | Quitte le shell avec un code de retour |

### Fonctionnalités du shell
- **Prompt dynamique** affichant le répertoire courant
- **Historique** des commandes (flèches haut/bas via `readline`)
- **Pipes** `|` — chaînage de commandes
- **Redirections** `<`, `>`, `>>` — entrée/sortie
- **Heredoc** `<<` — entrée multiligne jusqu'au délimiteur
- **Expansion** des variables `$VAR` et `$?`
- **Gestion des signaux** `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- **Mode non-interactif** — lit depuis stdin si non-TTY
- **Validation syntaxique** — détecte les pipes/redirections mal formés

---

## 🏗️ Architecture

```
minishell/
├── srcs/
│   ├── main.c               # Point d'entrée
│   ├── loop.c               # Boucle principale + lecture du prompt
│   ├── parse.c              # Collecte des actions par segment
│   ├── actions.c            # Structure t_action
│   ├── search_and_launch.c  # Recherche et exécution des binaires
│   └── get_paths.c          # Résolution du PATH
├── lexer/
│   ├── lexer.c              # Tokenisation de la ligne
│   └── lexer_utils.c        # Utilitaires lexer
├── build/                   # Builtins (echo, cd, pwd, env, export, unset, exit, run)
├── expand/
│   └── expand_tokens.c      # Expansion des variables
├── redir/
│   └── redir.c              # Ouverture/application des redirections
├── pipes/
│   └── pipes.c              # Création et application des pipes
├── heredoc/
│   └── heredoc.c            # Gestion du heredoc
├── signal/
│   └── sig.c                # Gestion des signaux
├── prompt/
│   └── prompt_ascii_art.c   # ASCII art au lancement
├── libft/                   # Bibliothèque personnelle
└── minishell.h              # Header principal
```

---

## 🚀 Compilation & utilisation

### Prérequis

- `gcc` ou `cc`
- `readline` (`libreadline-dev` sur Debian/Ubuntu)
- `make`

### Compiler

```bash
make
```

### Lancer

```bash
./minishell
```

### Nettoyage

```bash
make clean    # supprime les .o
make fclean   # supprime les .o et le binaire
make re       # recompile from scratch
```

---

## 💡 Exemples d'utilisation

```bash
# Pipe simple
ls -la | grep ".c"

# Redirection
echo "hello" > fichier.txt
cat < fichier.txt

# Append
echo "world" >> fichier.txt

# Heredoc
cat << EOF
ligne 1
ligne 2
EOF

# Variables d'environnement
export MON_VAR=42
echo $MON_VAR

# Code de retour
ls fichier_inexistant
echo $?
```

---

## ⚙️ Fonctionnement interne

```
readline()
    │
    ▼
lexer()          → liste de t_tok (TOKEN_WORD, TOKEN_PIPE, TOKEN_REDIR_*, ...)
    │
    ▼
validate_syntax() → vérifie la cohérence des tokens
    │
    ▼
expand_tokens()  → substitue $VAR et $?
    │
    ▼
parse_pipeline() → ouvre les pipes/redirections, fork, execve
```

---

## 📚 Projet

Réalisé à **42** dans le cadre du projet `minishell` — niveau 3 du tronc commun.

> *Ce projet nous a appris à ne plus jamais sous-estimer un shell.*

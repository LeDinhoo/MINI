/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:00:11 by hdupuy            #+#    #+#             */
/*   Updated: 2023/07/11 13:14:23 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief Sépare une chaîne en un tableau de chaînes à l'aide d'un délimiteur
 *
 * @param s La chaîne à séparer
 * @param c Le caractère délimiteur
 * @return char** Un tableau de chaînes (sous-chaînes)
 */
char				**ft_split(const char *s, char c);

/**
 * @brief Convertit un entier en chaîne de caractères
 *
 * @param n L'entier à convertir
 * @return char* La chaîne résultante
 */
char				*ft_itoa(int n);

/**
 * @brief Trouve la première occurrence d'un caractère dans une chaîne
 *
 * @param str La chaîne à chercher
 * @param c Le caractère à trouver
 * @return char* Pointeur vers le caractère trouvé
 */
char				*ft_strchr(const char *str, int c);

/**
 * @brief Crée une copie d'une chaîne
 *
 * @param s1 La chaîne à copier
 * @return char* La nouvelle chaîne copiée
 */
char				*ft_strdup(const char *s1);

/**
 * @brief Joint deux chaînes en une seule
 *
 * @param s1 Première chaîne
 * @param s2 Deuxième chaîne
 * @return char* La nouvelle chaîne résultante
 */
char				*ft_strjoin(char *s1, char *s2);

/**
 * @brief Applique la fonction 'f' à chaque caractère
 * de la chaîne 's' passée en argument
 *
 * @param s La chaîne sur laquelle itérer
 * @param f La fonction à appliquer à chaque caractère
 * @return char* La chaîne modifiée
 */
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));

/**
* @brief Localise la première occurrence de la 
sous-chaîne 'needle' dans la chaîne 'haystack'
 *
 * @param haystack La chaîne principale
 * @param needle La sous-chaîne à localiser
 * @param len La longueur de la chaîne
 * @return char* Un pointeur sur le début de la sous-chaîne,
	ou NULL si la sous-chaîne n'est pas trouvée
 */
char				*ft_strnstr(char *haystack, char *needle, size_t len);

/**
 * @brief Trouve la dernière occurrence d'un caractère dans une chaîne
 *
 * @param s La chaîne à chercher
 * @param c Le caractère à trouver
 * @return char* Pointeur vers le caractère trouvé,
	ou NULL si le caractère n'est pas trouvé
 */
char				*ft_strrchr(const char *s, int c);

/**

	* @brief Enlève les caractères définis dans 'set'
	 du début et de la fin de la chaîne 's1'
 *
 * @param s1 La chaîne à trimmer
 * @param set L'ensemble de caractères à enlever
 * @return char* La nouvelle chaîne trimmée
 */
char				*ft_strtrim(char *s1, char *set);

/**

	* @brief Extrait une sous-chaîne de 's' à partir de 'start' et de longueur 'len'
 *
 * @param s La chaîne source
 * @param start Le point de départ de la sous-chaîne
 * @param len La longueur de la sous-chaîne
 * @return char* La nouvelle sous-chaîne
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Convertit une chaîne de caractères en entier
 *
 * @param str La chaîne à convertir
 * @return int L'entier résultant
 */
int					ft_atoi(const char *str);

/**
 * @brief Vérifie si un caractère est numérique
 *
 * @param c Le caractère à vérifier
 * @return int 1 si le caractère est numérique, sinon 0
 */
int					ft_isdigit(int c);
/**
 * @brief Compare les 'n' premiers octets de deux zones de mémoire
 *
 * @param s1 La première zone mémoire à comparer
 * @param s2 La deuxième zone mémoire à comparer
 * @param n Le nombre d'octets à comparer
 * @return int Un nombre négatif,
	zéro ou positif si 's1' est respectivement inférieur,
	égal ou supérieur à 's2'
 */
int					ft_memcmp(void *s1, void *s2, size_t n);

/**
 * @brief Compare les 'n' premiers caractères de deux chaînes
 *
 * @param s1 La première chaîne à comparer
 * @param s2 La deuxième chaîne à comparer
 * @param n Le nombre de caractères à comparer
 * @return int Un nombre négatif,
	zéro ou positif si 's1' est respectivement inférieur,
	égal ou supérieur à 's2'
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Convertit une chaîne de caractères en long long
 *
 * @param str La chaîne à convertir
 * @return long long Le long long résultant
 */
long long			ft_atol(const char *str);

/**

	* @brief Concatène deux chaînes en ajoutant jusqu'à 
	'dstsize' caractères de 'src' à la fin de 'dst'
 *
 * @param dst La chaîne destination
 * @param src La chaîne source
 * @param dstsize La taille maximale de la chaîne destination
 * @return size_t La longueur totale de la chaîne qu'on a tenté de créer
 */
size_t				ft_strlcat(char *dst, char *src, size_t dstsize);

/**
 * @brief Copie jusqu'à 'dstsize' caractères de la chaîne 'src' vers 'dst'
 *
 * @param dst La chaîne destination
 * @param src La chaîne source
 * @param dstsize La taille maximale de la chaîne destination
 * @return size_t La longueur de 'src'
 */
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
/**
 * @brief Calcule la longueur d'une chaîne
 *
 * @param s La chaîne à mesurer
 * @return size_t La longueur de la chaîne
 */
size_t				ft_strlen(const char *s);

/**
 * @brief Retourne l'indice de la première occurrence de 'c' dans 's', ou
	-1 si 'c' n'est pas trouvé
 *
 * @param s La chaîne à chercher
 * @param c Le caractère à trouver
 * @return ssize_t L'indice de la première occurrence de 'c', ou
	-1 si 'c' n'est pas trouvé
 */
ssize_t				ft_strichr(char *s, int c);

/**
 * @brief Alloue de la mémoire et l'initialise à zéro
 *
 * @param count Le nombre d'éléments à allouer
 * @param size La taille d'un élément
 * @return void* Un pointeur vers la mémoire allouée
 */
void				*ft_calloc(size_t count, size_t size);

/**

	* @brief Localise la première occurrence de 'c'
	dans les 'n' premiers octets de 's'
 *
 * @param s La zone mémoire à chercher
 * @param c Le caractère à trouver
 * @param n Le nombre d'octets à chercher
 * @return void* Un pointeur vers l'octet trouvé,
	ou NULL si 'c' n'est pas trouvé
 */
void				*ft_memchr(void *s, int c, size_t n);

/**
 * @brief Copie 'n' octets de 'src' vers 'dest'
 *
 * @param dest La destination de la copie
 * @param src La source de la copie
 * @param n Le nombre d'octets à copier
 * @return void* Un pointeur vers 'dest'
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copie 'n' octets de 'src' vers 'dest',
	en tenant compte du chevauchement
 *
 * @param dest La destination de la copie
 * @param src La source de la copie
 * @param n Le nombre d'octets à copier
 * @return void* Un pointeur vers 'dest'
 */
void				*ft_memmove(void *dest, void *src, size_t n);

/**
 * @brief Remplit les 'n' premiers octets de 's' avec le caractère 'c'
 *
 * @param s La zone mémoire à remplir
 * @param c Le caractère de remplissage
 * @param n Le nombre d'octets à remplir
 * @return void* Un pointeur vers 's'
 */
void				*ft_memset(void *s, int c, size_t n);

/**
 * @brief Met à zéro les 'n' premiers octets de 's'
 *
 * @param s La zone mémoire à mettre à zéro
 * @param n Le nombre d'octets à mettre à zéro
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief Ajoute l'élément 'new' à la fin de la liste 'lst'
 *
 * @param lst L'adresse du pointeur sur le premier lien de la liste
 * @param new L'adresse du pointeur sur le nouvel élément à ajouter à la liste
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Ajoute l'élément 'new' au début de la liste 'lst'
 *
 * @param lst L'adresse du pointeur sur le premier lien de la liste
 * @param new L'adresse du pointeur sur le nouvel élément à ajouter à la liste
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Ecrit le caractère 'c' sur le descripteur de fichier 'fd'
 *
 * @param c Le caractère à écrire
 * @param fd Le descripteur de fichier sur lequel écrire
 */
void				ft_putchar_fd(char c, int fd);

/**

	* @brief Ecrit la chaîne 's' suivie d'un retour à la 
	ligne sur le descripteur de fichier 'fd'
 *
 * @param s La chaîne à écrire
 * @param fd Le descripteur de fichier sur lequel écrire
 */
void				ft_putendl_fd(char *s, int fd);
/**
 * @brief Ecrit la chaîne 's' sur le descripteur de fichier 'fd'
 *
 * @param s La chaîne à écrire
 * @param fd Le descripteur de fichier sur lequel écrire
 */
void				ft_putstr_fd(char *s, int fd);

/**

	* @brief Applique la fonction 'f' 
	à chaque caractère de la chaîne 's' passée en argument,
	et passe son index en premier argument
 *
 * @param s La chaîne sur laquelle itérer
 * @param f La fonction à appliquer à chaque caractère
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Vérifie si un caractère est un espace blanc
 *
 * @param c Le caractère à vérifier
 * @return int 1 si le caractère est un espace blanc, sinon 0
 */
int					ft_isspace(int c);

/**
 * @brief Copie la chaîne 'source' vers 'destination'
 *
 * @param destination La chaîne de destination
 * @param source La chaîne source
 * @return char* Un pointeur vers la chaîne de destination
 */
char				*ft_strcpy(char *destination, const char *source);

/**
 * @brief Compare deux chaînes
 *
 * @param s1 La première chaîne à comparer
 * @param s2 La deuxième chaîne à comparer
 * @return int Un nombre négatif,
	zéro ou positif si 's1' est respectivement inférieur,
	égal ou supérieur à 's2'
 */
int					ft_strcmp(const char *s1, const char *s2);

#endif

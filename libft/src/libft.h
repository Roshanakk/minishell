/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:49:33 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/09 13:00:42 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <bsd/string.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
// void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_and_free(char *s1, char const *s2);
char	*ft_strdup(const char *s);
char	**ft_free_array(char	**str, size_t	l);
size_t	ft_cmpt(char const *s, char c);
size_t	ft_array_size(char **array);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_swap(char **a, char **b);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_strchr_plus_one(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_putendl_fd(char *s, int fd);
int		is_numeric(char *str);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strncpy(char *dest, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

#endif
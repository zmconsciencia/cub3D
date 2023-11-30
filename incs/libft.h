/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:54:28 by svalente          #+#    #+#             */
/*   Updated: 2023/11/30 13:10:38 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "cub3d.h"
# include <stdbool.h>

char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, int len);
char	**ft_split(char const *s, char *c);
char	*ft_strchr(const char *s, int c);
int		ft_isspace(char c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strrchr(const char *s, int c);
void	*ft_memset(void *s, int c, int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_atoi(const char *str);
int		print_map(char **map); // remove
char	*ft_strchr_chars(const char *s, char *c);

//get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
bool	ft_clean_buff(char *str);

#endif
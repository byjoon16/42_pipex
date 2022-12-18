/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:13:12 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/14 19:13:15 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_freeall(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		tab[j] = NULL;
		j--;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

char	*make_word(char **tab, char const *s, char c, int j)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) + (len + 1));
	if (!word)
		return (ft_freeall(tab, j));
	len = 0;
	while (s[len] != '\0' && s[len] != c)
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

char	**ft_split2(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			tab[j] = make_word(tab, &s[i], c, j);
			if (tab[j] == NULL)
				return (NULL);
			j++;
		}
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
	{
		free(tab);
		tab = NULL;
		return (NULL);
	}
	tab = ft_split2(tab, s, c);
	if (!tab)
		return (NULL);
	return (tab);
}

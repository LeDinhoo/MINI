/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:34:45 by clement           #+#    #+#             */
/*   Updated: 2023/09/19 17:47:34 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	*ft_lengh_array(void **array)
{
	size_t x;
	
	if(!array[x])
		return (0);
	x = 0;
	while(array[x])
		x++;
	return(x);
}

void	ft_free_array(void **array)
{
	int i;
	int j;

	if (array)
	{
		j = ft_lengh_array(array);
		i = 0;
		while(i < j)
			free(array[i++]);
		free(array);
	}
}

void	**ft_dup_array(char **array, bool free_array, bool dup_strings)
{
	char	**new_array;
	size_t	lengh_array;
	size_t	i;
	
	lengh_array = ft_lengh_array(array);
	new_array = ft_calloc(lengh_array + 1, sizeof(void *));
	if (!new_array)
		return(NULL);
	if (dup_strings)
	{
		i = 0;
		while(i < lengh_array)
		{
			new_array[i] = ft_strdup(array[i]);
			i++;
		}
	}
	else
		ft_memcpy(array, new_array, lengh_array * sizeof(void *));
	if (free_array)
		ft_free_array(array);
	return (new_array);
}
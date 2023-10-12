/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:54:03 by clement           #+#    #+#             */
/*   Updated: 2023/10/10 20:36:46 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	ft_lengh_array(char **array)
{
	size_t	x;

	if (!array)
		return (0);
	x = 0;
	while (array[x])
		x++;
	return (x);
}

void	ft_free_array(char **array)
{
	int	i;
	int	j;

	if (array)
	{
		j = ft_lengh_array(array);
		i = 0;
		while (i < j)
			free(array[i++]);
		free(array);
	}
}

/*void	**ft_dup_array(void **array, bool free_array, bool dup_strings)
{
	void	**new_array;
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
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bignum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:57:54 by scamargo          #+#    #+#             */
/*   Updated: 2018/01/13 17:45:26 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft.h"

static void	add_factors(char *n1, char *n2, int lens[2], t_array *char_arr)
{
	int carry;
	int fac1;
	int fac2;

	carry = 0;
	lens[0]--;
	lens[1]--;
	while (lens[0] >= 0 || lens[1] >= 0 || carry > 0)
	{
		fac1 = (lens[0] < 0) ? 0 : n1[lens[0]] - '0';
		fac2 = (lens[1] < 0) ? 0 : n2[lens[1]] - '0';
		fac1 += fac2 + carry;
		arr_insert(char_arr, (fac1 % 10) + '0');
		carry = fac1 / 10;
		lens[0]--;
		lens[1]--;
	}
}

static int	factors_are_negative(char **p_n1, int *p_l1, char **p_n2, int *p_l2)
{
	if ((*p_n1)[0] == '-' && (*p_n2)[0] == '-')
	{
		++(*p_n1);
		--(*p_l1);
		++(*p_n2);
		--(*p_l2);
		return (1);
	}
	return (0);
}

char		*add_bignum(char *num1, int len1, char *num2, int len2)
{
	char	*result;
	t_array *char_arr;
	int		factors_neg;
	int		lens[2];

	if (!(char_arr = init_bignum("", len1)))
		return (0);
	factors_neg = factors_are_negative(&num1, &len1, &num2, &len2);
	if (num1[0] == '-' | num2[0] == '-')
	{
		if (num1[0] == '-')
			subtract_bignum(num2, len2, ++num1, --len1);
		else
			subtract_bignum(num1, len1, ++num2, --len2);
	}
	lens[0] = len1;
	lens[1] = len2;
	add_factors(num1, num2, lens, char_arr);
	if (factors_neg)
		arr_insert(char_arr, '-');
	arr_insert(char_arr, '\0');
	ft_strrev(char_arr->str);
	result = char_arr->str;
	free(char_arr);
	return (result);
}

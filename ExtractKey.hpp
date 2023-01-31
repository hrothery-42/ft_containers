/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExtractKey.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 08:58:03 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 14:03:25 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTKEY_HPP
# define EXTRACTKEY_HPP 

# include "Utility.hpp"

template<class K>
K	extractKey(K key)
{
	return key;
};
template<class K, class V>
K	extractKey(ft::pair<K,V> par)
{
	return par.first;
};

template<class K>
void	rewriteData(K& d1, K& d2)
{
	d1 = d2;
}

template<class K, class V>
void	rewriteData(ft::pair<const K,V>& p1, ft::pair<const K,V>& p2)
{
	const_cast<K&>(p1.first) = p2.first;
	p1.second = p2.second;
};

template<class Var>
Var* 	isConstant(const Var * var)
{
	return const_cast<Var*>(var);
};

template<class Var>
Var *	isConstant(Var * var)
{
	return var;
};

#endif
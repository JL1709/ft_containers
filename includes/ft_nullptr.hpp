/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nullptr.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:44:12 by julian            #+#    #+#             */
/*   Updated: 2022/01/28 14:15:39 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NULLPTR_HPP
#define FT_NULLPTR_HPP

namespace ft
{
	struct nullptr_t
	{
		void *lx;
		struct nat {int for_bool;};
		
		nullptr_t() : lx(0) {}
		nullptr_t(int nat::*) : lx(0) {}
		
		operator int nat::*() const {return 0;}

		template<class T>
		operator T* () const {return 0;}

		template<class T, class U>
		operator T U::*() const {return 0;}

		friend bool operator==(nullptr_t, nullptr_t) {return true;}
		friend bool operator!=(nullptr_t, nullptr_t) {return false;}
	};

	nullptr_t get_nullptr_t() {return nullptr_t(0);}
	
}

#define ft_nullptr ft::get_nullptr_t()

#endif

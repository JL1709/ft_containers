/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:37 by jludt             #+#    #+#             */
/*   Updated: 2022/01/21 19:29:00 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "ft_vector.hpp"
#include <stack>

namespace ft
{
	template <class T, class Container = ft::vector<T> > 
	class stack
	{		
		protected:
			Container c;
		
		public:
		
/* MEMBER TYPES ------------------------------------------------------------- */

			typedef Container						container_type;
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			
/* MEMBER FUNCTIONS --------------------------------------------------------- */
	
			explicit stack(const Container& cont = Container()) : c(cont) {}
			~stack() {}
			stack& operator=(const stack& other) {return (c = other.c);}

	// Element access
			value_type& top() {c.back()};
			const value_type& top() const;
	
	// Capacity
			bool empty() const;
			size_type size() const {return c.size();};

	// Modifiers
			void push(const value_type& value) {c.push_back(value);}
			void pop();
	};

/* NON-MEMBER FUNCTION OVERLOADS --------------------------------------------- */


	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs);


	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);


	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);


	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs);


	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);

}


#endif
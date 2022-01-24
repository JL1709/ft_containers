/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:07:37 by jludt             #+#    #+#             */
/*   Updated: 2022/01/24 11:16:47 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "ft_vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > 
	class stack
	{		
		protected:
			Container c;
		
		public:
		
/* MEMBER TYPES ------------------------------------------------------------- */ // DONE

			typedef Container						container_type;
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			
/* MEMBER FUNCTIONS --------------------------------------------------------- */
	
			explicit stack(const Container& cont = Container()) : c(cont) {}
			~stack() {}
			stack& operator=(const stack& other) {c = other.c; return *this;}

	// Element access
			value_type& top() {return c.back();}
			const value_type& top() const {return c.back();}
	
	// Capacity
			bool empty() const {return c.empty();};
			size_type size() const {return c.size();}

	// Modifiers
			void push(const value_type& value) {c.push_back(value);}
			void pop() {return c.pop_back();}

	// friends for non member overloads
			template <class T1, class C1>
			friend bool operator==(const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

			template <class T1, class C1>
			friend bool operator<(const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
	
	};

/* NON-MEMBER FUNCTION OVERLOADS --------------------------------------------- */


	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.c == rhs.c);}


	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {{return !(lhs == rhs);}}


	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.c < rhs.c);}

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return !(rhs < lhs);}


	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (rhs < lhs);}


	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return !(lhs < rhs);}
}

#endif

/***************************************************************************
  tag: Peter Soetens  Mon Jan 19 14:11:19 CET 2004  StandardEventCompleter.hpp 

                        StandardEventCompleter.hpp -  description
                           -------------------
    begin                : Mon January 19 2004
    copyright            : (C) 2004 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be
 
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/ 
 
#ifndef STANDARDEVENTCOMPLETER_HPP
#define STANDARDEVENTCOMPLETER_HPP

#include "EventCompleterInterface.hpp"

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace ORO_CoreLib
{
	/**
	 * This is a wrapper class for holding a
	 * pointer to a function and calling that function
	 * on handleEvent().
	 * Do not use this class directly, but use the completer()
	 * function.
	 *
	 * @see completer
	 */
	class StandardEventCompleter
		: public EventCompleterInterface
		{
			typedef boost::function<void ( void )> fun_t;
			fun_t fun;
			public:
			StandardEventCompleter( fun_t f )
				: fun( f )
				{
				}

			void completeEvent( void )
			{
				fun( );
			}
		};
	

  /**
   * Factory method. 
   * Creates a new StandardEventCompleter object.
   *
   * @return A new StandardEventCompleter instance, which is
   *         owned by the caller.
   *
   * @note The reason for returning a new instance on the
   * heap (instead of stack) is because the lifetime of the
   * object must be longer than the current scope.
   */
  template<typename t>
  StandardEventCompleter* standcompleter( t fun )
  {
    return new StandardEventCompleter( fun );
  }

  /**
   * Factory method.
   * Creates a new EventCompleterInterface object which
   * will execute a given member function.
   *
   * @param f The member function to execute, with CallbackInterface
   * @param t The object holding the member function.
   * @return A new EventCompleterInterface instance, which is
   *         owned by the caller.
   *
   */
  template<typename T>
  EventCompleterInterface* completer( void (T::*f)( void ), T* t )
  {
    return standcompleter( boost::bind( f, t ) );
  }

}

#endif

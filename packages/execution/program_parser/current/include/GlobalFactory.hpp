/***************************************************************************
  tag: Peter Soetens  Mon Jan 19 14:11:25 CET 2004  GlobalFactory.hpp 

                        GlobalFactory.hpp -  description
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
 
#ifndef GLOBAL_FACTORY_HPP
#define GLOBAL_FACTORY_HPP

#include "GlobalCommandFactory.hpp"
#include "CommandFactoryInterface.hpp"

#include "GlobalDataSourceFactory.hpp"
#include "DataSourceFactoryInterface.hpp"


namespace ORO_Execution
{

    /**
     * @brief This factory is used by the Parser ( and sub-Parsers )
     * to retrieve existing commands and data structures.
     *
     * It merely stores the GlobalCommandFactory and GlobalDataSourceFactory
     * for a given application.
     */
    class GlobalFactory
    {
        GlobalCommandFactory commandFact;
        GlobalDataSourceFactory dataFact;

    public:
        const GlobalCommandFactory& commandFactory() const
        {
            return commandFact;
        }

        GlobalCommandFactory& commandFactory()
        {
            return commandFact;
        }

        GlobalDataSourceFactory& dataFactory()
        {
            return dataFact;
        }

        const GlobalDataSourceFactory& dataFactory() const
        {
            return dataFact;
        }

    };

}

#endif

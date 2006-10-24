/***************************************************************************
  tag: Peter Soetens  Tue Jul 20 15:13:14 CEST 2004  CommandInterface.cxx 

                        CommandInterface.cxx -  description
                           -------------------
    begin                : Tue July 20 2004
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
 
 
#ifdef ORO_PRAGMA_INTERFACE
#pragma implementation
#endif
#include "CommandInterface.hpp"

namespace RTT {
  CommandInterface::~CommandInterface() {
  }

    void CommandInterface::reset() {
    }

    bool CommandInterface::valid() const {
        return true;
    }

    //void CommandInterface::readArguments() {
    //}

  CommandInterface* CommandInterface::copy( std::map<const DataSourceBase*, DataSourceBase*>& alreadyCloned ) const {
    return clone();
  }
}
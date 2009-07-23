/***************************************************************************
  tag: FMTC  Tue Mar 11 21:49:21 CET 2008  ScriptingAccessI.cpp

                        ScriptingAccessI.cpp -  description
                           -------------------
    begin                : Tue March 11 2008
    copyright            : (C) 2008 FMTC
    email                : peter.soetens@fmtc.be

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU General Public                   *
 *   License as published by the Free Software Foundation;                 *
 *   version 2 of the License.                                             *
 *                                                                         *
 *   As a special exception, you may use this file as part of a free       *
 *   software library without restriction.  Specifically, if other files   *
 *   instantiate templates or use macros or inline functions from this     *
 *   file, or you compile this file and link it with other files to        *
 *   produce an executable, this file does not by itself cause the         *
 *   resulting executable to be covered by the GNU General Public          *
 *   License.  This exception does not however invalidate any other        *
 *   reasons why the executable file might be covered by the GNU General   *
 *   Public License.                                                       *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public             *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/


// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be/be_codegen.cpp:910

#include "ScriptingAccessI.h"
#include "OperationsI.h"
#include "ScriptingAccess.hpp"
#include "../scripting/ProgramLoader.hpp"
#include "../scripting/parse_exception.hpp"
#include <sstream>

using namespace std;
using namespace RTT;
using namespace RTT::Corba;


// Implementation skeleton constructor
Orocos_ScriptingAccess_i::Orocos_ScriptingAccess_i (RTT::ScriptingAccess* ee, PortableServer::POA_ptr the_poa)
    :mee(ee), mpoa( PortableServer::POA::_duplicate(the_poa))
{
}

// Implementation skeleton destructor
Orocos_ScriptingAccess_i::~Orocos_ScriptingAccess_i (void)
{
}

PortableServer::POA_ptr Orocos_ScriptingAccess_i::_default_POA()
{
    return PortableServer::POA::_duplicate(mpoa);
}

void Orocos_ScriptingAccess_i::loadPrograms (
    const char * code,
    const char * filename
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    ::RTT::Corba::ScriptingAccess::LoadException
  ))
{
    try {
        mee->loadPrograms( code, filename, true );
    }
    catch (program_load_exception &ple) {
        throw ::RTT::Corba::ScriptingAccess::LoadException( ple.what() );
    } catch(file_parse_exception &fpe) {
        throw ::RTT::Corba::ScriptingAccess::LoadException( fpe.what().c_str() );
    }
}

void Orocos_ScriptingAccess_i::unloadProgram (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    ::RTT::Corba::ScriptingAccess::LoadException
  ))
{
    try {
        mee->unloadProgram( name, true );
    }
    catch (program_unload_exception &ple) {
        throw ::RTT::Corba::ScriptingAccess::LoadException( ple.what() );
    }
}

::RTT::Corba::ScriptingAccess::ProgramNames * Orocos_ScriptingAccess_i::getPrograms (

  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    std::vector<std::string> vlist = mee->getPrograms();
    ::RTT::Corba::ScriptingAccess::ProgramNames_var result = new ::RTT::Corba::ScriptingAccess::ProgramNames();
    result->length( vlist.size() );
    for (unsigned int i=0; i != vlist.size(); ++i )
        result[i] = CORBA::string_dup( vlist[i].c_str() );
    return result._retn();
}

CORBA::Long Orocos_ScriptingAccess_i::getProgramLine (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return mee->getProgramLine( name );
}

CORBA::Boolean Orocos_ScriptingAccess_i::hasProgram (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return mee->hasProgram( name );
}

char * Orocos_ScriptingAccess_i::getProgramText (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return CORBA::string_dup( mee->getProgramText(name).c_str() );
}

char * Orocos_ScriptingAccess_i::getProgramStatus (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return CORBA::string_dup( mee->getProgramStatus(name).c_str() );
}

void Orocos_ScriptingAccess_i::loadStateMachines (
    const char * code,
    const char * filename
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    ::RTT::Corba::ScriptingAccess::LoadException
  ))
{
    try {
        mee->loadStateMachines( code, filename, true);
    }
    catch (program_load_exception &ple) {
        throw ::RTT::Corba::ScriptingAccess::LoadException( ple.what() );
    } catch(file_parse_exception &fpe) {
        throw ::RTT::Corba::ScriptingAccess::LoadException( fpe.what().c_str() );
    }
}

void Orocos_ScriptingAccess_i::unloadStateMachine (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    ::RTT::Corba::ScriptingAccess::LoadException
  ))
{
    try {
        mee->unloadStateMachine( name, true );
    }
    catch (program_unload_exception &ple) {
        throw ::RTT::Corba::ScriptingAccess::LoadException( ple.what() );
    }
}

::RTT::Corba::ScriptingAccess::StateMachineNames * Orocos_ScriptingAccess_i::getStateMachines (

  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  // Add your implementation here
    std::vector<std::string> vlist = mee->getStateMachines();
    ::RTT::Corba::ScriptingAccess::StateMachineNames_var result = new ::RTT::Corba::ScriptingAccess::StateMachineNames();
    result->length( vlist.size() );
    for (unsigned int i=0; i != vlist.size(); ++i )
        result[i] = CORBA::string_dup( vlist[i].c_str() );
    return result._retn();
}

CORBA::Boolean Orocos_ScriptingAccess_i::hasStateMachine (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return mee->hasStateMachine( name );
}

char * Orocos_ScriptingAccess_i::getStateMachineText (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return CORBA::string_dup( mee->getStateMachineText(name).c_str() );
}

char * Orocos_ScriptingAccess_i::getStateMachineStatus (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return CORBA::string_dup( mee->getStateMachineStatus(name).c_str() );
}

CORBA::Long Orocos_ScriptingAccess_i::getStateMachineLine (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return mee->getStateMachineLine( name );
}

char * Orocos_ScriptingAccess_i::getCurrentState (
    const char * name
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return CORBA::string_dup( mee->getCurrentState(name).c_str() );
}

CORBA::Long Orocos_ScriptingAccess_i::execute (
    const char * code
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
    return mee->execute( code );
}

::RTT::Corba::Command_ptr Orocos_ScriptingAccess_i::getCommand (
      CORBA::Long ticket
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    ))
{
    DispatchInterface::shared_ptr ret = mee->getCommand(ticket);
    if ( !ret )
        return Command::_nil();
    Orocos_Command_i* com = new Orocos_Command_i( ret, mpoa.in() );
    return com->_this();

}

/***************************************************************************
  tag: Peter Soetens  Mon May 10 19:10:29 CEST 2004  ZeroLatencyThread.cxx 

                        ZeroLatencyThread.cxx -  description
                           -------------------
    begin                : Mon May 10 2004
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

#include "corelib/ZeroLatencyThread.hpp"
#include "corelib/PreemptibleActivity.hpp"
#include "corelib/Logger.hpp"

#include "pkgconf/corelib_activities.h"

#ifdef OROSEM_CORELIB_ACTIVITIES_AUTOSTART
#include <os/StartStopManager.hpp>
namespace ORO_CoreLib
{
    namespace
    {
        int startZLTThread()
        {
            ZeroLatencyThread::Instance()->start();
            return true;
        }

        void stopZLTThread()
        {
            ZeroLatencyThread::Release();
        }

        ORO_OS::InitFunction ZLTInit( &startZLTThread );
        ORO_OS::CleanupFunction ZLTCleanup( &stopZLTThread );
    }
}
#endif


namespace ORO_CoreLib
{
    
    // The static class variables
    TimerThreadPtr ZeroLatencyThread::_instance;

    TimerThreadPtr ZeroLatencyThread::Instance()
    {
        if ( !_instance )
        {
            _instance.reset( new ZeroLatencyThread() );
        }

        return _instance;
    }

    bool ZeroLatencyThread::Release()
    {
        _instance.reset();
        return true;
    }


    ZeroLatencyThread::ZeroLatencyThread()
        : TimerThread(ORONUM_CORELIB_ACTIVITIES_ZLT_PRIORITY,
                        ORODAT_CORELIB_ACTIVITIES_ZLT_NAME, 
                        ORONUM_CORELIB_ACTIVITIES_ZLT_PERIOD)
    {
        makeHardRealtime();
        Logger::log() << Logger::Info << ORODAT_CORELIB_ACTIVITIES_ZLT_NAME <<" created with "<< ORONUM_CORELIB_ACTIVITIES_ZLT_PERIOD <<"s periodicity";
        Logger::log() << Logger::Info << " and priority " << ORONUM_CORELIB_ACTIVITIES_ZLT_PRIORITY << Logger::endl;
    }

    ZeroLatencyThread::~ZeroLatencyThread()
    {
        Logger::log() << Logger::Debug << ORODAT_CORELIB_ACTIVITIES_ZLT_NAME <<" destructor." << Logger::endl;
    }
}
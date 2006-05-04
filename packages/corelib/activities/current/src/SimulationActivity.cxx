/***************************************************************************
  tag: Peter Soetens  Tue Dec 21 22:43:07 CET 2004  SimulationActivity.cxx 

                        SimulationActivity.cxx -  description
                           -------------------
    begin                : Tue December 21 2004
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
 
 
#include "corelib/SimulationActivity.hpp"
#include "corelib/SimulationThread.hpp"

namespace ORO_CoreLib
{
    
    SimulationActivity::SimulationActivity(Seconds period, RunnableInterface* r )
        :PeriodicActivity(period,SimulationThread::Instance(), r)
    {
    }

    SimulationActivity::SimulationActivity(secs sec, nsecs nsec, RunnableInterface* r )
        :PeriodicActivity(sec, nsec,SimulationThread::Instance(), r)
    {
    }

    SimulationActivity::~SimulationActivity()
    {
        stop();
    }
}
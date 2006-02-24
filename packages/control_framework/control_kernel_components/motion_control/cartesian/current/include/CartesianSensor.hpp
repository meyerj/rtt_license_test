/***************************************************************************
  tag: Peter Soetens  Thu Apr 22 20:40:59 CEST 2004  CartesianSensor.hpp 

                        CartesianSensor.hpp -  description
                           -------------------
    begin                : Thu April 22 2004
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
 
 
#ifndef CARTESIAN_NS_SENSOR_HPP
#define CARTESIAN_NS_SENSOR_HPP

#include <corelib/Event.hpp>
#include <control_kernel/Simulator.hpp>
#include <control_kernel/KernelInterfaces.hpp>
#include <control_kernel/ReportingExtension.hpp>
#include <control_kernel/BaseComponents.hpp>
#include <control_kernel/ExtensionComposition.hpp>

#include <pkgconf/control_kernel.h>
#ifdef OROPKG_CONTROL_KERNEL_EXTENSIONS_EXECUTION
#include <control_kernel/ExecutionExtension.hpp>
#include "execution/TemplateDataSourceFactory.hpp"
#include "execution/TemplateCommandFactory.hpp"
#endif

#include "CartesianDataObjects.hpp"
#include <geometry/MotionProperties.hpp>

#ifdef ORO_PRAGMA_INTERFACE
#pragma interface
#endif

/**
 * @file CartesianSensor.hpp
 *
 * This file contains a sensor for
 * use in cartesian path planning. It reads
 * robot positions from a Simulator.
 */
    
namespace ORO_ControlKernel
{
    using namespace ORO_Geometry;
    using namespace ORO_CoreLib;

#ifdef OROPKG_CONTROL_KERNEL_EXTENSIONS_EXECUTION
    using namespace ORO_Execution;
#endif

    /**
     * @brief A Fake Cartesian Sensor measuring all data sent by the CartesianEffector.
     * @ingroup kcomps kcomp_sensor
     */
    class CartesianSensor
        : public Sensor< Writes<CartesianSensorInput>,
                         MakeFacet<ReportingExtension,
                                   KernelBaseFunction,
#ifdef OROPKG_CONTROL_KERNEL_EXTENSIONS_EXECUTION
                                   ExecutionExtension
#endif
                                   >::Result >
    {
        typedef Sensor< Writes<CartesianSensorInput>,
            MakeFacet<ReportingExtension,
                      KernelBaseFunction,
#ifdef OROPKG_CONTROL_KERNEL_EXTENSIONS_EXECUTION
                      ExecutionExtension
#endif
                      >::Result > Base;
    public:
            
        CartesianSensor(SimulatorInterface* _sim = 0) 
            : Base("CartesianSensor"),
              sensorError( "CartesianSensor::SensorError"),
              jpos("JointPositions",""), sim(_sim)
        {
            jpos.set().resize(6, 0.0);
        }
            
        virtual bool componentStartup()
        {
            if ( !Input->dObj()->Get("JointPositions", jpos_DObj ) )
                return false;
            pull();
            push();
            return true;
        }
            
        /**
         * @see KernelInterfaces.hpp class ModuleControlInterface
         */
        virtual void pull()      
        {
            /*
             * Fake physical sensor data.
             */
            if (sim != 0) {
                Double6D q6;
                q6 = sim->getJointPositions();
                q6.getVector( jpos.set() );
            }
        }

        /**
         * @see KernelInterfaces.hpp class ModuleControlInterface
         */
        virtual void push()      
        {
            jpos_DObj->Set( jpos.get() );
        }

            
        /**
         * @see KernelReportingExtension.hpp class ReportingComponent
         */
        virtual void exportReports(PropertyBag& bag)
        {
            bag.add(&jpos);
        }

            
    protected:
        Event<void(void)> sensorError;

        Property<ORO_KinDyn::JointPositions> jpos;
        DataObjectInterface<ORO_KinDyn::JointPositions>* jpos_DObj;

        SimulatorInterface* sim;
    };

}
#endif

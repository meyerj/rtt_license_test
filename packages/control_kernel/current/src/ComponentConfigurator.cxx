/***************************************************************************
  tag: Peter Soetens  Mon May 10 19:10:37 CEST 2004  ComponentConfigurator.cxx 

                        ComponentConfigurator.cxx -  description
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
#include "control_kernel/ComponentConfigurator.hpp"
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <corelib/marshalling/CPFDemarshaller.hpp>
#include <control_kernel/PropertyExtension.hpp>

using namespace std;
using namespace ORO_CoreLib;
using namespace ORO_ControlKernel;

bool ComponentConfigurator::configure(const std::string& filename, PropertyComponentInterface* target) const
{
    bool result = false;
    XMLCh* name = 0;
    cout << "Configuring " <<target->getName()<< endl;
    try
    {
        name =  XMLString::transcode( filename.c_str() );
        LocalFileInputSource fis( name );
        delete[] name;
        CPFDemarshaller<InputSource> demarshaller(fis);

        // store results in Components own bag if component exists.
        if ( demarshaller.deserialize( target->getLocalStore().value() ) )
        {
            // instruct component to update.
            if (!target->updateProperties( target->getLocalStore().value() ) )
                cerr << "Component "<<target->getName() << " dit not successfully update its properties !"<<endl;
            else
                result = true;
            // cleanup
            flattenPropertyBag( target->getLocalStore().value() );
            deleteProperties( target->getLocalStore().value() );
        }
        else
            {
                cerr << "Some error occured while parsing "<< filename.c_str() <<endl;
            }
    } catch (...)
    {
        delete[] name;
        cerr << "Could not find "<< filename << endl;
    }
    return result;
}


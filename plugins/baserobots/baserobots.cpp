// Copyright (C) 2006-2010 Carnegie Mellon University (rdiankov@cs.cmu.edu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "plugindefs.h"
#include "genericrobot.h"
#include "collisionmaprobot.h"
#include <rave/plugin.h>

static boost::shared_ptr<void> s_RegisteredReader;

InterfaceBasePtr CreateInterfaceValidated(InterfaceType type, const std::string& interfacename, std::istream& sinput, EnvironmentBasePtr penv)
{
    if( !s_RegisteredReader ) {
        /// as long as this pointer is valid, the reader will remain registered
        s_RegisteredReader = RaveRegisterXMLReader(PT_Robot,"collisionmap",CollisionMapRobot::CreateXMLReader);
    }
    
    switch(type) {
    case PT_Robot:
        if( interfacename == "genericrobot")
            return InterfaceBasePtr(new GenericRobot(penv));
        else if( interfacename == "collisionmaprobot")
            return InterfaceBasePtr(new CollisionMapRobot(penv));
        break;
    default:
        break;
    }

    return InterfaceBasePtr();
}

void GetPluginAttributesValidated(PLUGININFO& info)
{
    info.interfacenames[PT_Robot].push_back("GenericRobot");
    info.interfacenames[PT_Robot].push_back("CollisionMapRobot");
}

RAVE_PLUGIN_API void DestroyPlugin()
{
    s_RegisteredReader.reset(); // unregister the reader
}

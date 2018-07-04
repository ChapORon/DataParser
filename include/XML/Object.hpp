#ifndef GALAXY_XML_OBJECT_HPP
#define GALAXY_XML_OBJECT_HPP

#include "XML/Markup.hpp"

namespace dp::XML
{
    /**
     * Class that represent an object who can be converted to/from an Galaxy::XML::Markup
     */
    class Object
    {
    public:
        /**
         * Allow to edit the child class with an Galaxy::XML::Markup
         *
         * @param tag Markup to used to edit the class
         * @see Galaxy::XML::Object::getXML
         */
        virtual void setXML(const Markup &tag) = 0;

        /**
         * Allow to convert the child class to an Galaxy::XML::Markup
         *
         * @return A tag containing all the object information
         * @see Galaxy::XML::Object::setXML
         */
        virtual Markup getXML() const = 0;
    };
}

#endif

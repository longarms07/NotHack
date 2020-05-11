#pragma once

/*******************************************************************
 * Class for objects that are activated and deactivated at runtime;
 * this is primarily used to display/hide the hacking and WWW windows
 *******************************************************************/
class Registerable {
    public:
        virtual ~Registerable() { };

        virtual void activate() { };
        virtual void deactivate() { };
};
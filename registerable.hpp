#pragma once

class Registerable {
    public:
        virtual ~Registerable() { };

        virtual void activate() { };
        virtual void deactivate() { };
};
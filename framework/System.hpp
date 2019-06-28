#pragma once


class System
{
    public:
        System() = default;
        System(System &&) = default;
        System(const System &) = default;
        System &operator=(System &&) = default;
        System &operator=(const System &) = default;
        virtual ~System() = default;
        virtual void Update() = 0;
    private:
    
};

#pragma once

namespace Nebula
{
    class AtlasContainer : public AtlasElement
    {
    public:
        AtlasContainer();
        virtual ~AtlasContainer();
        void addChild(AtlasElement&);
        std::vector<AtlasElement*> children;

    protected:
        
    private:
        
    };
}

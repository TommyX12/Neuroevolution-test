#pragma once

namespace Nebula
{
    class Transform
    {
        public:

            float64 a, b, c, d, tx, ty, tz, red, green, blue, alpha;

            Transform();
            virtual ~Transform();

            Transform& combine_global(Transform &);
            Transform& combine_local(Transform &, Transform &);

        protected:

        private:
    };

    namespace TransformMode
    {
        const int GLOBAL = 0;
        const int LOCAL = 1;
    }
}

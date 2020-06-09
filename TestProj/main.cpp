#include "entt.hpp"


class Family {
    static std::size_t identifier() noexcept {
        static std::size_t value = 0;
        return value++;
    }

public:
    template<typename>
    static std::size_t type() noexcept {
        static const std::size_t value = identifier();
        return value;
    }
};

struct Position {
    float x;
    float y;
    float z;
};

struct Velocity {
    float vx;
    float vy;
    float vz;
};

int main() {
    // const auto id = Family::type<int>();
    // const auto id2 = Family::type<bool>();
    // const auto id3 = Family::type<float>();

    // printf("Type1: %zd\n", id);
    // printf("Type2: %zd\n", id2);
    // printf("Type3: %zd\n", id3);

    // printf("Type1: %zd\n", Family::type<int>());
    // printf("Type2: %zd\n", Family::type<bool>());
    // printf("Type3: %zd\n", Family::type<float>());
    entt::registry registry;
    std::uint64_t dt = 16;

    for (auto i=0; i < 10; i++) {
        auto entity = registry.create();
        registry.emplace<Position>(entity, 1.0f, 2.0f, 1.0f);
        registry.emplace<Velocity>(entity, 0.4f, 0.4f, 0.4f);
    }

    registry.view<Position, Velocity>().each([dt](auto &pos, auto &vel) {
        // gets all the components of the view at once ...

        printf(" X:%1.2f,  Y:%1.2f,  Z:%1.2f\n", pos.x, pos.y, pos.z);
        printf("VX:%1.2f, VY:%1.2f, VZ:%1.2f\n\n", vel.vx, vel.vy, vel.vz);

        // ...
    });

    return 0;
}
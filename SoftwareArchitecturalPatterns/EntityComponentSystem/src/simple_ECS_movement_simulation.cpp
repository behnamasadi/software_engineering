#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// Components
struct Position {
  float x, y;
};

struct Velocity {
  float dx, dy;
};

// Entity is just an integer
using Entity = unsigned int;

// Component Storage
template <typename T> class ComponentStorage {
public:
  void add(Entity entity, const T &component) {
    components[entity] = component;
  }

  void remove(Entity entity) { components.erase(entity); }

  T *get(Entity entity) {
    if (components.find(entity) != components.end()) {
      return &components[entity];
    }
    return nullptr;
  }

private:
  std::unordered_map<Entity, T> components;
};

// ECS Manager
class ECSManager {
public:
  Entity createEntity() { return nextEntity++; }

  template <typename T> void addComponent(Entity entity, const T &component) {
    getStorage<T>()->add(entity, component);
  }

  template <typename T> void removeComponent(Entity entity) {
    getStorage<T>()->remove(entity);
  }

  template <typename T> T *getComponent(Entity entity) {
    return getStorage<T>()->get(entity);
  }

  // Process entities that have both Position and Velocity
  void updateSystems() {
    for (Entity entity : entitiesWithComponents<Position, Velocity>()) {
      auto *pos = getComponent<Position>(entity);
      auto *vel = getComponent<Velocity>(entity);
      if (pos && vel) {
        pos->x += vel->dx;
        pos->y += vel->dy;
      }
    }
  }

private:
  Entity nextEntity = 0;

  template <typename T> ComponentStorage<T> *getStorage() {
    static ComponentStorage<T> storage;
    return &storage;
  }

  // Find entities with specific components
  template <typename... Components>
  std::vector<Entity> entitiesWithComponents() {
    std::vector<Entity> entities;
    for (Entity entity = 0; entity < nextEntity; ++entity) {
      if ((getComponent<Components>(entity) && ...)) {
        entities.push_back(entity);
      }
    }
    return entities;
  }
};

int main() {
  ECSManager ecs;

  // Create entities
  Entity e1 = ecs.createEntity();
  Entity e2 = ecs.createEntity();

  // Add components
  ecs.addComponent(e1, Position{0, 0});
  ecs.addComponent(e1, Velocity{1, 1});

  ecs.addComponent(e2, Position{10, 10});
  ecs.addComponent(e2, Velocity{-1, -1});

  // Simulate a few updates
  for (int i = 0; i < 5; ++i) {
    ecs.updateSystems();

    auto *pos1 = ecs.getComponent<Position>(e1);
    auto *pos2 = ecs.getComponent<Position>(e2);

    std::cout << "Entity 1 Position: (" << pos1->x << ", " << pos1->y << ")\n";
    std::cout << "Entity 2 Position: (" << pos2->x << ", " << pos2->y << ")\n";
  }

  return 0;
}

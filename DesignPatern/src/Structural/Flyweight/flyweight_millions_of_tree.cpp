#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

// Color and Texture (used in Flyweight objects)
class Color {};
class Texture {};

// Canvas for rendering trees
class Canvas {
public:
    void render(int x, int y, const std::string& treeType)
    {
        std::cout << "🌳 Drawing " << treeType << " at (" << x << ", " << y << ")\n";
    }
};

// Flyweight class: TreeType (Intrinsic State)
class TreeType
{
private:
    std::string name;
    std::shared_ptr<Color> color;
    std::shared_ptr<Texture> texture;

public:
    TreeType(std::string treeName, std::shared_ptr<Color> treeColor, std::shared_ptr<Texture> treeTexture)
        : name(std::move(treeName)), color(std::move(treeColor)), texture(std::move(treeTexture))
    {}

    void renderTree(Canvas& canvas, int x, int y) const
    {
        canvas.render(x, y, name);
    }
};

// Flyweight Factory
class TreeTypeFactory
{
private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes;

    std::string getKey(const std::string& name) const
    {
        return name;
    }

public:
    std::shared_ptr<TreeType> getTreeType(const std::string& name, std::shared_ptr<Color> color, std::shared_ptr<Texture> texture)
    {
        std::string key = getKey(name);
        auto it = treeTypes.find(key);

        if (it == treeTypes.end())
        {
            std::cout << "✅ Creating new TreeType: " << name << "\n";
            auto treeType = std::make_shared<TreeType>(name, std::move(color), std::move(texture));
            treeTypes[key] = treeType;
            return treeType;
        }
        else
        {
            std::cout << "♻️ Reusing existing TreeType: " << name << "\n";
            return it->second;
        }
    }

    void listTreeTypes() const
    {
        std::cout << "\n🌲 Available TreeTypes in Factory: \n";
        for (const auto& pair : treeTypes)
        {
            std::cout << "   - " << pair.first << "\n";
        }
    }
};

// Tree (Context Object) - Stores Extrinsic State
class Tree
{
private:
    int x, y;
    std::shared_ptr<TreeType> type;

public:
    Tree(int xPos, int yPos, std::shared_ptr<TreeType> treeType)
        : x(xPos), y(yPos), type(std::move(treeType))
    {}

    void draw(Canvas& canvas) const
    {
        type->renderTree(canvas, x, y);
    }
};

// Forest (Manages multiple trees)
class Forest
{
private:
    std::vector<std::shared_ptr<Tree>> trees;
    TreeTypeFactory treeFactory;

public:
    void addTree(int x, int y, const std::string& name)
    {
        auto color = std::make_shared<Color>();
        auto texture = std::make_shared<Texture>();
        auto treeType = treeFactory.getTreeType(name, color, texture);

        trees.push_back(std::make_shared<Tree>(x, y, treeType));
    }

    void renderForest(Canvas& canvas) const
    {
        std::cout << "\n🎨 Rendering the Forest...\n";
        for (const auto& tree : trees)
        {
            tree->draw(canvas);
        }
    }
};

int main()
{
    Canvas canvas;
    Forest forest;

    // Adding trees to the forest
    forest.addTree(10, 20, "Oak Tree");
    forest.addTree(30, 40, "Pine Tree");
    forest.addTree(15, 25, "Oak Tree"); // This should reuse the existing TreeType
    forest.addTree(50, 60, "Maple Tree");

    // Render all trees in the forest
    forest.renderForest(canvas);

    return 0;
}

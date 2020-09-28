// The flyweight class contains a portion of the state of a
// tree. These fields store values that are unique for each
// particular tree. For instance, you won't find here the tree
// coordinates. But the texture and colors shared between many
// trees are here. Since this data is usually BIG, you'd waste a
// lot of memory by keeping it in each tree object. Instead, we
// can extract texture, color and other repeating data into a
// separate object which lots of individual tree objects can
// reference.
#include <string>

class Color{};

class Texture{};

class Canvas{};

class TreeType
{
    std::string m_name;
    Color *m_color;
    Texture *m_texture;
public:
    TreeType(std::string name, Color *color,Texture* texture)
    {

    }

    void draw(Canvas *canvas, int x, int y)
    {
        // 1. Create a bitmap of a given type, color & texture.
        // 2. Draw the bitmap on the canvas at X and Y coords.
    }

};

/*
// Flyweight factory decides whether to re-use existing
// flyweight or to create a new object.
class TreeFactory
{
    static field treeTypes: collection of tree types
    static method getTreeType(name, color, texture) is
        type = treeTypes.find(name, color, texture)
        if (type == null)
            type = new TreeType(name, color, texture)
            treeTypes.add(type)
        return type
};


// The contextual object contains the extrinsic part of the tree
// state. An application can create billions of these since they
// are pretty small: just two integer coordinates and one
// reference field.
class Tree
{
    field x,y
    field type: TreeType
    constructor Tree(x, y, type) { ... }
    method draw(canvas) is
        type.draw(canvas, this.x, this.y)

};


// The Tree and the Forest classes are the flyweight's clients.
// You can merge them if you don't plan to develop the Tree
// class any further.
class Forest
{
        field trees: collection of Trees

        method plantTree(x, y, name, color, texture) is
            type = TreeFactory.getTreeType(name, color, texture)
            tree = new Tree(x, y, type)
            trees.add(tree)

        method draw(canvas) is
            foreach (tree in trees) do
                tree.draw(canvas)

};

*/

int main()
{

}

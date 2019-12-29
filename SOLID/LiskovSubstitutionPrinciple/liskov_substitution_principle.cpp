//https://www.tomdalling.com/blog/software-design/solid-class-design-the-liskov-substitution-principle/
/*

Functions that use pointers to base classes must be able to use objects of derived classes
without knowing it in other words:
“parent classes should be easily substituted with their child classes without blowing up the application”.

Let’s consider an Animal parent class:

public class Animal
{
public:
    void makeNoise()
    {
        cout<<"I am making noise"<<endl;
    }
}

Now let’s consider the Cat and Dog classes which extends Animal:

public:
    class Dog: public Animal
    {

    public:
    void makeNoise()
    {
        cout<<"bow wow"<<endl;
    }
}

class Cat: public Animal
{
    public void makeNoise()
    {
        cout<<"meow meow"<<endl;
    }
}

Now, wherever in our code we were using Animal class object we must be able to replace
it with the Dog or Cat without exploding our code.

if the following class is replace by Animal then our app will crash.

class DumbDog : public  Animal
{
    public:
    void makeNoise()
    {
        throw new RuntimeException("I can't make noise");
    }
}

*/


class Bird {
public:
    virtual void setLocation(double longitude, double latitude) = 0;
    virtual void setAltitude(double altitude) = 0;
    virtual void draw() = 0;
};

/*
If an override method does nothing or just throws an exception, then you're probably violating the LSP.
*/

class Penguin: public Bird
{
    void setAltitude(double altitude)
    {
        //altitude can't be set because penguins can't fly
        //this function does nothing
    }
};

/*

Solution 1: The wrong way to do it
void ArrangeBirdInPattern(Bird* aBird)
{
    Pengiun* aPenguin = dynamic_cast<Pengiun*>(aBird);
    if(aPenguin)
        ArrangeBirdOnGround(aPenguin);
    else
        ArrangeBirdInSky(aBird);
}


Solution 2: An OK way to do it

One not-so-great way of fixing the problem is to add a method to the Bird class named isFlightless.

void ArrangeBirdInPattern(Bird* aBird)
{
    if(aBird->isFlightless())
        ArrangeBirdOnGround(aBird);
    else
        ArrangeBirdInSky(aBird);
}

//Solution 3: Proper inheritance
class Bird {
public:
    virtual void draw() = 0;
    virtual void setLocation(double longitude, double latitude) = 0;
};

class FlightfulBird : public Bird {
public:
    virtual void setAltitude(double altitude) = 0;
};

*/


int main()
{
}

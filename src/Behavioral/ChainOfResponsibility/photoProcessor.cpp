#include <iostream>
#include <string>

class  Photo
{

};
class PhotoProcessor
{
public:
    PhotoProcessor * next;
    //std::string name;
    //PhotoProcessor(std::string name):name(name){}
    void setNext(PhotoProcessor * next)
    {
        this->next=next;
    }
    void process(Photo *photo)
    {
        processImplementation(photo);
        if(next!=nullptr)
            next->process(photo);
    }

    void virtual processImplementation(Photo *photo)= 0;

    PhotoProcessor():next(nullptr){}
    //~PhotoProcessor();
};

class redEye: public PhotoProcessor
{
public:
    void processImplementation(Photo *photo)
    {
        std::cout<<"correcting red eye" <<std::endl;
    }
    //redEye():PhotoProcessor(nullptr){}
    redEye()
    {
        this->next=nullptr;
    }
};

class scaling: public PhotoProcessor
{
public:
    int width, height;
    scaling(int width,int height):width(width), height(height)
    {
        this->next=nullptr;
    }

    void processImplementation(Photo *photo)
    {
        std::cout<<"scaling into " <<std::to_string(width) <<","<<std::to_string(height)  <<std::endl;
    }

};

class meanFilter: public PhotoProcessor
{
    double mean, var;
public:
    meanFilter(double mean, double var): mean(mean), var(var)
    {
        this->next=nullptr;
    }
    void processImplementation(Photo *photo)
    {
        std::cout<<"applying mean filter with mean " <<std::to_string(mean) <<", var "<<std::to_string(var)  <<std::endl;
    }

};

int main()
{
    Photo myPhoto;
    redEye redEye_processor;
    scaling scaling_processor(600,800) ;
    meanFilter meanFilter_processor(0,1);

    redEye_processor.setNext(&scaling_processor);
    scaling_processor.setNext(&meanFilter_processor);
    redEye_processor.process(&myPhoto);
}




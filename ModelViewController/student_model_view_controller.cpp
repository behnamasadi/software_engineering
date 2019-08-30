#include <string>
#include <iostream>

/*
https://www.tomdalling.com/blog/software-design/model-view-controller-explained/
https://www.tutorialspoint.com/design_pattern/mvc_pattern.htm


Model:
Model represents an object carrying data and does nothing else.
The model does NOT depend on the controller or the view.

View:
View represents the visualization of the data that model contains. The view displays the model data,
and sends user actions (e.g. button clicks) to the controller.

Controller:
Controller acts on both model and view. It controls the data flow into model object and updates the view
whenever data changes. It keeps view and model separate.


The model represents the data, and does nothing else. The model does NOT depend on the controller or the view.
MVC makes model classes and view classes reusable without modification.


*/


////////////////////////////////// Model //////////////////////////////////
class Student
{
private:
    std::string rollNo;
    std::string name;

public:
    std::string getRollNo()
    {
        return rollNo;
    }

    void setRollNo(std::string rollNo)
    {
        this->rollNo = rollNo;
    }

    std::string getName()
    {
        return name;
    }

    void setName(std::string name)
    {
        this->name = name;
    }
};
////////////////////////////////// View //////////////////////////////////

class StudentView
{
   public:
    void printStudentDetails(std::string studentName, std::string studentRollNo)
    {
      std::cout<<"Student: "<<std::endl;
      std::cout<<"Name: " << studentName<<std::endl;
      std::cout<<"Roll No: " << studentRollNo<<std::endl;
   }
};

////////////////////////////////// Controller //////////////////////////////////

class StudentController
{
private:
    Student model;
    StudentView view;
public:

    StudentController(Student model, StudentView view)
    {
        this->model = model;
        this->view = view;
    }

    void setStudentName(std::string name)
    {
        model.setName(name);
    }

    std::string getStudentName()
    {
        return model.getName();
    }

    void setStudentRollNo(std::string rollNo)
    {
        model.setRollNo(rollNo);
    }

    std::string getStudentRollNo()
    {
        return model.getRollNo();
    }

    void updateView()
    {
        view.printStudentDetails(model.getName(), model.getRollNo());
    }
};

Student retriveStudentFromDatabase()
{

    Student student;
    student.setName("Robert");
    student.setRollNo("10");
    return student;
}

int main()
{
    //fetch student record based on his roll no from the database
    Student model  = retriveStudentFromDatabase();

    //Create a view : to write student details on console
    StudentView view;

    StudentController controller(model, view);

    controller.updateView();

    //update model data
    controller.setStudentName("John");

    controller.updateView();
}


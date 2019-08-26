/*
public delegate void MessageReceivedEventHandler(string message, string from);

public class Mediator
{
    public event MessageReceivedEventHandler MessageReceived;

    public void Send(string message, string from)
    {
        if (MessageReceived != null)
        {
            Console.WriteLine("Sending '{0}' from {1}", message, from);
            MessageReceived(message, from);
        }
    }
}

public class Person
{
    private Mediator _mediator;

    public string Name { get; set; }

    public Person(Mediator mediator, string name)
    {
        Name = name;
        _mediator = mediator;
        _mediator.MessageReceived += new MessageReceivedEventHandler(Receive);
    }

    private void Receive(string message, string from)
    {
        if (from != Name)
            Console.WriteLine("{0} received '{1}' from {2}", Name, message, from);
    }

    public void Send(string message)
    {
        _mediator.Send(message, Name);
    }
}
*/

int main()
{

}
